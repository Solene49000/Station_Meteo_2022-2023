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
- Anémomètre : Renvoie la vitesse du vent jusquà 250 km/h (float)
- Pluviomètre : Renvoie la quantité d'eau tombée en 10s


struct datas_w { // 255 <=> error
  uint8_t macSTA[6];
  float   temp      = 225;        // -50 to +80 °C
  uint8_t hygro     = 255;        //  0 to 100%
  float   atm       = 0;          // 300 - 1100 hPa
  uint8_t wind_s    = 255;         // km/h
  uint8_t wind_d    = 255;         // step 2° - divided by 2 (0-180 =>0-360)
  float   rain      = 0;
  uint16_t lum      = 0;           // 40000 lux
  float    v_bat      = 255;        // 0 to 16 V, sent in 1/10 de V
  uint8_t  charg_bat  = 255;    // 0 to 100%
} dw;
