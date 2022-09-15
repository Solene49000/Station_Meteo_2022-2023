Rapport de séance
==

Présentation du projet
-

Séance du 01/09
-

- Mise en place du projet Station Météo 2022-2023 :
  - Création du projet sur github
  - Ajout de dossiers : Rapports de séance et Docs
  - Ajout dans le dossier Docs de la documantation sur notre projet
  - Ajout des rapports de Solène Guillaume et Ambre Allouis dans Rapports de séance
  - Prise en main du langage Markdown
- Matériel à disposition :
  - Anémomètre : Vitesse du vent
  - Capteur de direction du vent
  - Pluviomètre : Compte le nombre de bascule
  - Capteur de lumière
  - Capteur de température, d'hydrométrie, de pression atmosphérique
  - Abris météo

Séance du 02/09
-

- Récupération du schéma de la carte et du tableau.
- Lecture des rapports de l'année précédente
- Lecture des codes récupérés de l'année précédente : Les codes fournis ne sont pas bons, il manque la version finale.
- Installation et configuration d'Arduino :
  - Installation des librairies ESP32 et LoRa.
  - Analyse et compilation du code fourni
  - Choix du Port COM3
  - Outils : Carte ESP32 Dev
  - Création d'un code permettant de faire clignoter les deux led (LED_R et LED_G) pour vérifier l'accès à la carte.  

Séance du 09/09
-

- On a recompilé le code permettant de faire alterner la led verte et la led rouge
- Pluie : détection par 1 front montant par routine + détection dès que la pluie tombe
- Vent changement : plusieurs fronts montant et descendants créés donc soit création d’un filtre et ou détection par rebond
- Pour la girouette : retourne 16 valeurs en fonction de la direction du vent. Les élèves précédents ont utilisé un générateur de tension. Chaque sortie est associée à une tension particulière. Le problème de ce fonctionnement est lié à la tension fournit par la batterie qui oscille entre 3,1 et 3,6 V. cet intervalle cause la proximité des tensions entre chaque sortie et fausse les résultats.
- M Peter nous a donc conseillé d’utiliser un générateur de courant car celui-ci n’est pas influencé par la différence de tension.

Séance du 15/09
-

- Pluviometre, utilisation de la commande attachInterrupt() utilisation de la fonctionnalité FALLING permettant la dettection des fronts descendants
- cette fonction permet d'incrémenter une variable et de retourner chaque changement d'état
- le pluviometre est relie au port GIO 32, pour le fonctionnement initiale du pluviomêtre il reçoit V+. Pour notre cas, il est allimenté par VCC, donc pour obtenir la tension initiale, on pinMODE MEASURE à l'état 1 cette variable nous permet d'imposer le passage au niveau des transistor et ainsi de distribuer la bonne tension. Le transistor étant passant, le condo permet d'éviter l'é=effet de rebond. De plus lorsque la carte est débranchée puis rebranchée, le compteur  est incrémenté de 2.

anemo : installation de la librairie esp32 timerInterrupt
