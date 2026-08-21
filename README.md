# BOT CAR

**BOT CAR** est un robot mobile intelligent équipé d'un bras robotique à trois articulations, conçu pour la collecte, le transport et la gestion d'objets ou de déchets. Piloté via une interface web fluide et un microcontrôleur ESP32, il intègre un système de détection d'obstacles et fonctionne de manière autonome ou manuelle en réseau local sans nécessiter de connexion Internet.

![Photo du BOT CAR](BOT%20CAR.jpg)

## Fichiers et Ressources du Projet

- **Code source principal (ESP32) :** [`main.py`](main.py)
- **Interface Web de contrôle :** [`index.html.html`](index.html.html)
- **Ressources de montage :** [Dossier `ZYC0208`](ZYC0208/) *(Ce dossier contient les ressources et éléments pour l'assemblage mécanique du châssis et du bras)*
- **Documentation détaillée :** [`DOCUMENTATION TECHNIQUE BOT CAR_104017.pdf`](DOCUMENTATION%20TECHNIQUE%20BOT%20CAR_104017.pdf)

## Problématique & Objectifs
Dans certains environnements (salles de classe, maisons, entreprises), la gestion des déchets ou le déplacement de petits objets peut être contraignant. **BOT CAR** propose une solution robotisée offrant une manipulation mobile pilotée à distance, supprimant ainsi les déplacements physiques de l'utilisateur.

**Objectifs principaux :**
- Concevoir un robot mobile autonome ou contrôlable à distance.
- Permettre la manipulation d’objets via un bras robotique.
- Offrir une interface de contrôle simple, inspirée du design des manettes, via une page web.
- Fonctionner de manière autonome sur réseau local (ESP32 en mode Point d'Accès).

## Architecture et Matériel Utilisé
Le système repose sur un ESP32 générant un point d’accès Wi-Fi (IP: `192.168.4.1`).

**Composants :**
- Carte microcontrôleur ESP32 & Module d’extension
- Moteurs DC 5V pour le déplacement des 4 roues
- Servomoteurs pour le bras robotique (3 degrés de liberté : rotation, montée/descente, ouverture/fermeture pince)
- Capteur ultrason (HC-SR04) pour la détection d’obstacles
- Batteries Lithium pour une alimentation robuste (remplaçant le système à piles initial)
- Châssis 4 roues et pièces mécaniques d’assemblage

## Programmation & Interface
- **Langage :** MicroPython (développé sous Thonny)
- **Fonctionnalités du code :** Contrôle des moteurs DC, gestion des servos (avec fonction anti-vibration qui coupe le signal PWM à l'arrêt), capteur à ultrason, point d'accès Wi-Fi et serveur HTTP non-bloquant.
- **Interface Web :** Un frontend élégant "Neumorphisme" inspiré des manettes de jeu, avec joystick virtuel et boutons d'action (A, B, X, Y), supportant le multi-touch sur mobile et les raccourcis clavier sur PC.

## Utilisation
1. Mettre sous tension le robot.
2. Se connecter au réseau Wi-Fi de l'ESP32 :
   - **Nom du réseau :** `BOT-CAR`
   - **Mot de passe :** `MotDePasseSolide`
3. Ouvrir un navigateur et accéder à `http://192.168.4.1`.
4. Contrôler le robot en temps réel !

## Perspectives
L'intégration de batteries lithium a résolu les défis d'alimentation initiaux liés à la charge du bras et des moteurs. À l'avenir, le projet ambitionne d'équiper le robot d'une **caméra embarquée** pour le pilotage hors de vue et d'une **Intelligence Artificielle de détection d'objets** pour rendre le ramassage totalement autonome.

---
**Réalisé par Maxadis** | [Dépôt GitHub BOT-CAR](https://github.com/Max-Adis/BOT-CAR/)
