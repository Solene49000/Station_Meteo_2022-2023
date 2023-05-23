INTRODUCTION
-
Dans le cadre du projet de la ruche connectée, nous continuons le développement de la station météo.
Celle ci permet  la mesure de données météorologiques telles que :
- La quantité de pluie tombée (1 front montant par basculement du pluviomètre)
- La vitesse du vent (1 front montant par tour d'anémomètre)
- La direction du vent (Tension différente par direction)
- La luminosité (I2C)
- La température (I2C)
- L'humidité (I2C)

Le code final est situé dans le repertoire : Codes/Dernière Version/test_sleep

1 - LES PORTS
-

- Les ports LoRa
  - SCK : 18 -- Horloge SPI
  - MISO : 19 -- Master In Slave Out SPI
  - MOSI : 23 -- Master Out Slave In SPI
  - SS : 5 -- Select Slave = NSS SPI
  - RST : 14 -- Reset
  - DI0 : 26 -- Données
  
- Les ports de modules
  - ANEMOMETRE : 27 -- Récupère données anémomètre
  - PLUVIOMETRE : 32 -- Récupère données pluviomètre
  - GIROUETTE : 36 -- Récupère données girouette

- Autres ports
  - MEASURE : 13 -- Mettre à high pour fournir une tension aux modules
  - LED_R : 33 -- Led rouge de test du bon fonctionnement
  - LED_G : 25 -- Led verte de test du bon fonctionnement


2- LES FICHIERS
-
- test_sleep.ino : Demande à des fréquences régulières la restitution des données des modules et envoie la trame LoRa
- Girouette.ino : Renvoie la direction du vent entre 0 et 15 ( 0 = Nord, 1 = Nord Nord Ouest, ...)
- Anemometre.ino : Renvoie la vitesse du vent jusquà 250 km/h (float)
- Pluviometre.ino : Renvoie la quantité d'eau tombée en 10s
- LuxHumTemp.ino : 
  - Renvoie la luminosité en lux
  - Renvoie l'humidité en pourcentage
  - Renvoie la température en degrés
- ESP_LoRa_internal.ino : 
  - Appelle 3 fonctions
    - build_trame : écrit une trame avec les données brutes de nos mesures
    - debug_trame : reformate la trame en binaire
    - lora_send_trame : envoie la trame vers l'antenne
- Batterie.ino : Renvoie la tension de la batterie
 
3 - LES DETAILS
-
- Une trame LoRa est envoyée toutes les 15 minutes
- Structure trame :   I|macAdresse|pluviomètre|anémomètre|girouette|partie_1_pression|partie_2_pression|humidité|luminosité|température|batterie|checkbytes

4 - LE SET UP
-
- Télécharger Arduino IDE
- Télécharger toutes les librairies affichées dans le fichier concerné
- Paramétrer Arduino IDE pour accepter la carte ESP32 Dev Module
- Copier le code issu de github : ouvrir le terminal de commande, allez dans votre répertoire du projet et entrez la fonction suivante "git copy https://github.com/Solene49000/Station_Meteo_2022-2023/tree/main/Codes"
- Dans documents, ouvrir le fichier "Station_meteo.ino". Tous les fichiers du dossier s'ouvrent dans Arduino
- Préparer le set up :
  - Brancher le pluviomètre au connecteur P
  - Brancher l'anémomètre et la girouette au connecteur G
  - Brancher le câble USB à la carte Arduino et à votre PC
- Compiler puis téléverser le code ( La compilation peut s'avérer très longue car Arduino n'est pas vraiment adapté à Windows et nous avons un certain nombre de fichiers)
