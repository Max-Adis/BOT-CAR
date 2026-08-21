<div align="center">
  <img src="BOT%20CAR.jpg" alt="BOT CAR Hero Image" width="100%" style="border-radius: 10px;">
  <br/>
  <h1>🚀 BOT CAR</h1>
  <p>
    <strong>Robot mobile autonome et manipulateur basé sur ESP32</strong>
  </p>
  <p>
    <a href="https://github.com/Max-Adis/BOT-CAR/"><img src="https://img.shields.io/badge/Language-MicroPython-0078D4.svg?style=flat-square" alt="Language"></a>
    <a href="https://github.com/Max-Adis/BOT-CAR/"><img src="https://img.shields.io/badge/Platform-ESP32-E83524.svg?style=flat-square" alt="Platform"></a>
    <a href="https://github.com/Max-Adis/BOT-CAR/"><img src="https://img.shields.io/badge/Status-Active-success.svg?style=flat-square" alt="Status"></a>
  </p>
</div>

<br/>

## 📖 À propos du Projet

**BOT CAR** est une solution robotisée conçue pour la collecte, le transport et la gestion d'objets ou de petits déchets dans divers environnements (salles de classe, laboratoires, maisons). Ce projet open-source démontre comment associer un châssis mobile, un bras robotique à 3 degrés de liberté et une interface de contrôle sans fil embarquée.

L'objectif principal est de supprimer les déplacements physiques de l'utilisateur grâce à une téléopération fluide ou via un mode de navigation autonome basé sur la détection d'obstacles.

---

## ✨ Fonctionnalités Principales

- 🕹️ **Contrôle Intuitif :** Interface web responsive au design moderne, hébergée localement sur l'ESP32.
- 🦾 **Bras Articulé :** Manipulation d'objets légère avec un bras robotique (rotation, élévation, pince).
- 🧠 **Mode Autonome :** Navigation autonome avec esquive d'obstacles via un capteur à ultrasons.
- 📡 **Réseau Indépendant :** L'ESP32 agit comme un Point d'Accès (Access Point) Wi-Fi. Aucune connexion Internet externe n'est requise.
- 🔋 **Alimentation Fiable :** Système propulsé par des batteries Lithium garantissant un courant de décharge suffisant pour les 4 moteurs et les servomoteurs.

---

## 🛠️ Architecture Matérielle

Le système s'articule autour des composants matériels suivants :

* **Cerveau :** Microcontrôleur ESP32 + Module d'extension.
* **Propulsion :** Châssis 4 roues motrices équipées de moteurs DC 5V.
* **Manipulation :** Servomoteurs contrôlant le bras (fonction anti-vibration intégrée au code).
* **Détection :** Capteur ultrason `HC-SR04` (portée de sécurité réglée à 20 cm).
* **Énergie :** 2x Batteries Lithium haute capacité.

---

## 💻 Interface Web

L'interface de contrôle a été conçue pour être aussi ergonomique qu'une manette de jeu classique. Elle intègre un joystick de déplacement virtuel et des boutons d'actions contextuels.

<div align="center">
  <img src="Interface%20wev.png" alt="Interface de contrôle Web" width="80%" style="border-radius: 10px; border: 1px solid #e2e8f0; box-shadow: 0 4px 6px rgba(0,0,0,0.1);">
</div>

---

## 🚀 Guide d'Utilisation (Démarrage Rapide)

Suivez ces étapes pour prendre le contrôle du robot :

1. **Mise sous tension :** Allumez le robot via son interrupteur physique.
2. **Connexion Wi-Fi :** 
   - Depuis un smartphone ou un ordinateur, recherchez le réseau sans fil.
   - **SSID :** `BOT-CAR`
   - **Mot de passe :** `MotDePasseSolide`
3. **Accès au panneau de contrôle :**
   - Ouvrez votre navigateur web favori.
   - Rendez-vous à l'adresse IP locale : `http://192.168.4.1`
4. **Pilotage :** Vous êtes connecté au serveur HTTP non-bloquant de l'ESP32. Pilotez le robot en temps réel !

---

## 📁 Arborescence du Dépôt

```text
📦 BOT-CAR
 ┣ 📂 ZYC0208/         # Ressources de montage mécanique et tutoriels
 ┣ 📂 index/           # Code source du site vitrine de présentation
 ┣ 📜 main.py          # Script principal MicroPython exécuté sur l'ESP32
 ┣ 📜 index.html.html  # Code HTML/CSS/JS de l'interface de contrôle embarquée
 ┣ 📜 DOCUMENTATION TECHNIQUE BOT CAR_104017.pdf  # Manuel technique détaillé
 ┣ 🖼️ BOT CAR.jpg      # Image du robot
 ┗ 🖼️ Interface wev.png# Capture de l'interface de contrôle
```

---

## 🔮 Roadmap et Perspectives

Le projet est en évolution continue. Voici les prochaines étapes de développement envisagées :

- [ ] **Vision Embarquée :** Intégration d'une caméra pour permettre un pilotage "hors de vue" (FPV).
- [ ] **Intelligence Artificielle :** Déploiement d'un modèle de détection d'objets (Computer Vision) pour rendre la collecte des déchets 100% autonome.
- [ ] **Télémétrie Avancée :** Retour d'information sur la tension de la batterie en temps réel sur l'interface Web.

---

<div align="center">
  <b>Développé et Maintenu par <a href="https://github.com/Max-Adis">Maxadis</a></b><br>
  <i>Projet de robotique éducative et utilitaire - Avril 2026</i>
</div>
