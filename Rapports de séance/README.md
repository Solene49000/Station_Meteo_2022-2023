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
- Station_Météo.ino : Demande à des fréquences régulières la restitution des données des modules
- Girouette.ino : Renvoie la direction du vent entre 0 et 15 ( 0 = Nord, 1 = Nord Nord Ouest, ...)
- Anémomètre.ino : Renvoie la vitesse du vent jusquà 250 km/h (float)
- Pluviomètre.ino : Renvoie la quantité d'eau tombée en 10s
- LuxHumTemp.ino : 
  - Renvoie la luminosité en lux
  - Renvoie l'humidité en pourcentage
  - Renvoie la température en degrés
- ESP_LoRa_internal.ino : 
  - Appelle 3 fonctions
    - build_trame : écrit une trame avec les données brutes de nos mesures
    - debug_trame : reformate la trame en binaire
    - lora_send_trame : envoie la trame vers l'antenne

3 - LES DETAILS

- Une trame LoRa est envoyée toutes les 15 minutes
- Structure trame :   I|macAdresse|pluviometre|anemometre|girouette|donneestsl|donneesbme|checkbytes

