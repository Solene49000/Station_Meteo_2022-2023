Version finale du code pour le fonctionnement du module meteo
-

Fichiers C
--

- **test_sleep.ino** : Demande à des fréquences régulières la restitution des données des modules et envoie la trame LoRa
- **Girouette.ino** : Renvoie la direction du vent entre 0 et 15 ( 0 = Nord, 1 = Nord Nord Ouest, ...)
- **Anemometre.ino** : Renvoie la vitesse du vent jusquà 250 km/h (float)
- **Pluviometre.ino** : Renvoie la quantité d'eau tombée en 10s
- **LuxHumTemp.ino** :
  - Renvoie la luminosité en lux
  - Renvoie l'humidité en pourcentage
  - Renvoie la température en degrés
- **ESP_LoRa_internal.ino** :
  Appelle 3 fonctions
  - build_trame : écrit une trame avec les données brutes de nos mesures
  - debug_trame : reformate la trame en binaire
  - lora_send_trame : envoie la trame vers l'antenne
- **Batterie.ino** : Renvoie la tension de la batterie

Fichiers d'en-tete
--
- **LoRa.h**
