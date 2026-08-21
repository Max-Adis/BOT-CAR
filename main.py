"""
ESP32 - Robot + Bras + Navigation Autonome
Interface Web + Fix Vibration Servo
Point d'accès : BOT-CAR / MotDePasseSolide
"""

from machine import Pin, PWM
import time
import network
import socket

# ─────────────────────────────────────────
#  BROCHES
# ─────────────────────────────────────────
FR1 = Pin(27, Pin.OUT); FR0 = Pin(23, Pin.OUT)
BR1 = Pin(33, Pin.OUT); BR0 = Pin(32, Pin.OUT)
FL1 = Pin(18, Pin.OUT); FL0 = Pin(19, Pin.OUT)
BL1 = Pin(26, Pin.OUT); BL0 = Pin(25, Pin.OUT)

bras  = PWM(Pin(21), freq=50)
pince = PWM(Pin(22), freq=50)

TRIG = Pin(13, Pin.OUT)
ECHO = Pin(12, Pin.IN)

# ─────────────────────────────────────────
#  ÉTAT GLOBAL
# ─────────────────────────────────────────
current_bras  = 0
current_pince = 100
auto_mode     = False

# transition_state : 0=rien  1=rotation droite 4s (→auto)  2=rotation gauche 4s (→manuel)
# nav_state        : 0=avancer/mesurer  1=reculer  2=virer droite
transition_state = 0
transition_timer = 0
nav_state        = 0
nav_timer        = 0

# ─────────────────────────────────────────
#  MOTEURS
# ─────────────────────────────────────────
def stop():
    for p in (FR1, FR0, FL1, FL0, BR1, BR0, BL1, BL0):
        p.value(0)

def avancer():
    FR1.value(1); FR0.value(0); FL1.value(1); FL0.value(0)
    BR1.value(1); BR0.value(0); BL1.value(1); BL0.value(0)

def reculer():
    FR1.value(0); FR0.value(1); FL1.value(0); FL0.value(1)
    BR1.value(0); BR0.value(1); BL1.value(0); BL0.value(1)

def droite():
    FR1.value(0); FR0.value(1); FL1.value(1); FL0.value(0)
    BR1.value(0); BR0.value(1); BL1.value(1); BL0.value(0)

def gauche():
    FR1.value(1); FR0.value(0); FL1.value(0); FL0.value(1)
    BR1.value(1); BR0.value(0); BL1.value(0); BL0.value(1)

# ─────────────────────────────────────────
#  SERVOS  —  FIX VIBRATION : duty(0) après chaque mouvement
#  Le servo tient la position mécaniquement sans signal.
#  Plus de bruit EMI des moteurs DC sur le PWM → plus de vibration.
# ─────────────────────────────────────────
def angle_to_duty(angle):
    return int(26 + (angle / 180) * (128 - 26))

def move_servo(pwm, target_angle, current_angle, step=2, delay=0.015):
    """Déplace progressivement le servo puis COUPE le signal PWM."""
    target_angle  = max(0, min(180, target_angle))
    current_angle = max(0, min(180, current_angle))
    if target_angle == current_angle:
        pwm.duty(0)
        return target_angle
    step_dir = step if target_angle > current_angle else -step
    ang = current_angle
    while True:
        ang += step_dir
        if step_dir > 0 and ang >= target_angle: ang = target_angle
        if step_dir < 0 and ang <= target_angle: ang = target_angle
        pwm.duty(angle_to_duty(ang))
        time.sleep(delay)
        if ang == target_angle:
            break
    time.sleep(0.08)   # laisser le servo atteindre la position
    pwm.duty(0)        # ← COUPER → plus de vibration sous bruit moteur
    return target_angle

def _bras_angle(val):
    """Convertit la plage utilisateur [-50, 30] en degrés servo [0, 180]."""
    return int((val + 50) * 180 / 80)

def _pince_angle(val):
    """Convertit la plage utilisateur [60, 140] en degrés servo [0, 180]."""
    return int((val - 60) * 180 / 80)

def set_bras_position(target):
    global current_bras
    target = max(-50, min(30, target))
    move_servo(bras, _bras_angle(target), _bras_angle(current_bras), step=2, delay=0.02)
    current_bras = target

def set_pince_position(target):
    global current_pince
    target = max(90, min(125, target))
    move_servo(pince, _pince_angle(target), _pince_angle(current_pince), step=3, delay=0.02)
    current_pince = target

def bras_monter():    set_bras_position(current_bras - 10)
def bras_descendre(): set_bras_position(current_bras + 10)
def pince_ouvrir():   set_pince_position(90)
def pince_fermer():   set_pince_position(125)

def init_servos():
    global current_bras, current_pince
    current_bras = 0; current_pince = 100
    set_bras_position(-10)
    set_pince_position(100)

# ─────────────────────────────────────────
#  CAPTEUR ULTRASON HC-SR04
# ─────────────────────────────────────────
DIST_SECU = 200  # mm

def mesure_distance():
    TRIG.value(1); time.sleep_us(10); TRIG.value(0)
    t = time.ticks_us()
    while ECHO.value() == 0:
        if time.ticks_diff(time.ticks_us(), t) > 30000: return 9999
    debut = time.ticks_us()
    t = time.ticks_us()
    while ECHO.value() == 1:
        if time.ticks_diff(time.ticks_us(), t) > 30000: return 9999
    fin = time.ticks_us()
    return (time.ticks_diff(fin, debut) * 343) // 2000

# ─────────────────────────────────────────
#  SÉQUENCES D'ACTIVATION / DÉSACTIVATION
# ─────────────────────────────────────────
def activate_auto():
    """Manuel → Auto : monter bras, puis tourner droite 4s, puis naviguer."""
    global auto_mode, transition_state, transition_timer, nav_state
    print(">> ACTIVATION MODE AUTO")
    set_bras_position(-50)      # 1. Bras complètement en haut (bloquant ~2s)
    stop()
    droite()                    # 2. Lancer rotation droite
    transition_state = 1
    transition_timer = time.ticks_ms()
    nav_state = 0
    auto_mode = True

def deactivate_auto():
    """Auto → Manuel : stop, bras reste en haut, tourner gauche 4s."""
    global auto_mode, transition_state, transition_timer
    print(">> DÉSACTIVATION MODE AUTO")
    stop()
    # current_bras est déjà à -50, on ne le touche pas
    gauche()                    # Tourner gauche 4s
    transition_state = 2
    transition_timer = time.ticks_ms()
    auto_mode = False

# ─────────────────────────────────────────
#  NAVIGATION AUTONOME (non-bloquante)
# ─────────────────────────────────────────
def update_nav():
    global nav_state, nav_timer
    now = time.ticks_ms()

    if nav_state == 0:
        d = mesure_distance()
        if d >= DIST_SECU:
            avancer()
        else:
            print("Obstacle", d, "mm")
            stop()
            time.sleep_ms(100)
            reculer()
            nav_state = 1
            nav_timer = now

    elif nav_state == 1:        # Recul 500 ms
        if time.ticks_diff(now, nav_timer) >= 500:
            droite()
            nav_state = 2
            nav_timer = now

    elif nav_state == 2:        # Virage droite 1800 ms
        if time.ticks_diff(now, nav_timer) >= 1800:
            stop()
            nav_state = 0

# ─────────────────────────────────────────
#  WI-FI ACCESS POINT
# ─────────────────────────────────────────
ap = network.WLAN(network.AP_IF)
ap.active(True)
ap.config(essid='BOT-CAR', password='MotDePasseSolide',
          authmode=network.AUTH_WPA2_PSK)
print("=== DÉMARRAGE ===")
print("IP :", ap.ifconfig()[0])

# ─────────────────────────────────────────
#  CHARGEMENT HTML
# ─────────────────────────────────────────
HTML_CONTENT = ""
try:
    with open('/index.html', 'r') as f:
        HTML_CONTENT = f.read()
    print("index.html OK —", len(HTML_CONTENT), "octets")
except OSError:
    print("ERREUR : index.html introuvable !")
    HTML_CONTENT = "<h1>Erreur : index.html manquant</h1>"

# ─────────────────────────────────────────
#  HELPERS HTTP
# ─────────────────────────────────────────
def send_html(conn):
    conn.send('HTTP/1.1 200 OK\nContent-Type: text/html\nConnection: close\n\n')
    conn.sendall(HTML_CONTENT)

def send_ok(conn):
    conn.send('HTTP/1.1 200 OK\nConnection: close\n\nOK')

def send_status(conn):
    """Renvoie : 'auto,busy' | 'auto,ready' | 'manual,busy' | 'manual,ready'"""
    mode  = 'auto'  if auto_mode        else 'manual'
    trans = 'busy'  if transition_state else 'ready'
    conn.send(
        'HTTP/1.1 200 OK\nContent-Type: text/plain\n'
        'Access-Control-Allow-Origin: *\nConnection: close\n\n'
        + mode + ',' + trans
    )

# ─────────────────────────────────────────
#  DÉMARRAGE
# ─────────────────────────────────────────
stop()
init_servos()
print("=== BOT-CAR PRÊT — http://192.168.4.1 ===\n")

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
s.bind(('', 80))
s.listen(3)
s.settimeout(0.05)   # 50 ms → boucle quasi non-bloquante

# ─────────────────────────────────────────
#  BOUCLE PRINCIPALE
# ─────────────────────────────────────────
while True:

    # ── 1. Gestion des transitions (rotation 4s) ──────────────────
    if transition_state != 0:
        if time.ticks_diff(time.ticks_ms(), transition_timer) >= 4000:
            stop()
            transition_state = 0
            if auto_mode:
                print(">> Navigation démarrée")
            else:
                print(">> Retour manuel")

    # ── 2. Navigation autonome ────────────────────────────────────
    if auto_mode and transition_state == 0:
        update_nav()

    # ── 3. Serveur HTTP ───────────────────────────────────────────
    try:
        conn, addr = s.accept()
        req = conn.recv(1024).decode()
        if not req:
            conn.close()
            continue

        path = req.split('\n')[0].split(' ')[1]

        # Commandes manuelles bloquées si auto_mode OU transition active
        locked = auto_mode or (transition_state != 0)

        do_activate   = False
        do_deactivate = False

        if path == '/' or path == '/index.html':
            send_html(conn)
        elif path == '/status':
            send_status(conn)
        elif path == '/toggle_auto':
            do_activate   = not auto_mode
            do_deactivate = auto_mode
            send_ok(conn)
        elif locked:
            send_ok(conn)               # Ignorer silencieusement
        elif path == '/forward':        avancer();       send_ok(conn)
        elif path == '/backward':       reculer();       send_ok(conn)
        elif path == '/left':           gauche();        send_ok(conn)
        elif path == '/right':          droite();        send_ok(conn)
        elif path == '/stop':           stop();          send_ok(conn)
        elif path == '/bras_up':        bras_monter();   send_ok(conn)
        elif path == '/bras_down':      bras_descendre();send_ok(conn)
        elif path == '/pince_open':     pince_ouvrir();  send_ok(conn)
        elif path == '/pince_close':    pince_fermer();  send_ok(conn)
        else:
            conn.send('HTTP/1.1 404 Not Found\n\n')

        conn.close()

        # ⚠️ Exécuté APRÈS fermeture connexion
        # (évite le timeout client pendant le mouvement du bras)
        if do_activate:   activate_auto()
        if do_deactivate: deactivate_auto()

    except OSError:
        pass
    except Exception as e:
        print("ERR serveur:", e)
