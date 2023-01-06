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
  - LED_R : 33 -- Led test du bon fonctionnement
  - LED_G : 25 -- Led test du bon fonctionnement


2- LES FICHIERS
-
- Station_Météo : Demande à des fréquences régulières la restitution des données des modules
- Girouette : Renvoie la direction du vent entre 0 et ?? ( 0 = Nord, 1 = Nord Nord Ouest, ...)
- Anémomètre : Renvoie la vitesse du vent en km/h (float)
- pluviomètre : Renvoie 



