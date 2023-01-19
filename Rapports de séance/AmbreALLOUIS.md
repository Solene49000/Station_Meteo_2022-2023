Rapport de séance
==

Présentation du projet
-

Séance du 01/09/2022
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

Séance du 02/09/2022
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

Séance du 09/09/2022
-

- On a recompilé le code permettant de faire alterner la led verte et la led rouge
- Pluie : détection par 1 front montant par routine + détection dès que la pluie tombe
- Vent changement : plusieurs fronts montant et descendants créés donc soit création d’un filtre et ou détection par rebond
- Pour la girouette : retourne 16 valeurs en fonction de la direction du vent. Les élèves précédents ont utilisé un générateur de tension. Chaque sortie est associée à une tension particulière. Le problème de ce fonctionnement est lié à la tension fournit par la batterie qui oscille entre 3,1 et 3,6 V. cet intervalle cause la proximité des tensions entre chaque sortie et fausse les résultats.
- M Peter nous a donc conseillé d’utiliser un générateur de courant car celui-ci n’est pas influencé par la différence de tension.

Séance du 15/09/2022
-

- Pluviometre, utilisation de la commande attachInterrupt() utilisation de la fonctionnalité FALLING permettant la dettection des fronts descendants
- cette fonction permet d'incrémenter une variable et de retourner chaque changement d'état
- le pluviometre est relie au port GIO 32, pour le fonctionnement initiale du pluviomêtre il reçoit V+. Pour notre cas, il est allimenté par VCC, donc pour obtenir la tension initiale, on pinMODE MEASURE à l'état 1 cette variable nous permet d'imposer le passage au niveau des transistor et ainsi de distribuer la bonne tension. Le transistor étant passant, le condo permet d'éviter l'é=effet de rebond. De plus lorsque la carte est débranchée puis rebranchée, le compteur  est incrémenté de 2.

anemo : installation de la librairie esp32 timerInterrupt

Séance du 03/10/2022
-

Codage de la partie Anémomètre :
- Recherche de bibliothèques timer associées à l'ESP32, nous ajoutons donc la bibliothèque ESP32TimerInterrupt
- Sans l'utilisation de cette bibliothèque, nous arrivons à afficher le nombre de tours de l'anémomètre et la vitesse du vent. en fin de séance nous nous sommes rendu compte que le calcul n'est pas correcte.
- Pour la réalisation de ce programme nous utilisaons la fonction delay. Le problème de cette fonction est que le programme est bloqué lors de sont activation. Donc cette fonction n'est pas compatible avec les autres codes.
- Le codage de l'anemomètre est en cours avec l'utilisation de la nouvelle librairie

Séance du 13/10/2022
-

- Utilisation de la bibliothèque ESP32TimerInterrupt :
  Cette bibliothèque nous permet de creer une fonction permettant l'interruption d'un programme à un moment donné dans une ISR. Pour notre cas, celle ci nous permet de relever la vitesse du vent. Pour notre cas d'essai, nous avons decidé de récupérer la vitesse toutes les 30 secondes.
  Pour la réalisation de cette fonction, nous avons utilisé les commandes suivantes :
    - My_timer = timerBegin(0, 80, true); --> Cette commande initialise la variable My_timer avec un numéro de timer, une valeur de prescaler et le mode compteur (true) 
    - timerAttachInterrupt(My_timer, &onTimer, true); --> Ici on fait appel à la fonction onTimer avec les paramètres de la variable My_timer
    - timerAlarmWrite(My_timer, tempsTimer*1000000, true); --> Maintenant, nous deffinissons le temps entre chaque interuption. Cette valeur est en microsecondes. Pour faciliter les calculs qui suivent, nous avons décidé de créer une variable comprenant le temps d'attente en secondes. Pour avoir le temps en microsecondes, nous multiplions cette variable avec la puissance associée (10^6).
    - timerAlarmEnable(My_timer); --> Activation de l'interruption
--> Nous avons fait le choix d'utiliser une librairie afin de clarifier et simplifier notre code lorsque toutes les parties seront réunies.
- Pour calculer la vitesse du vent, nous avons utilise=é le calcul suivant : vitesseVent = (PI * RAYON * 2 * tourAnemo)/tempsTimer*3.6 ;
  Nous multiplions la circonférence de l'anemomètre par le nombre de tours et le divisons par le temps en secondes. Le résultat obtenu est en m/s, nos le multiplions donc par 3.6 pour avoir ce résultat en km/h. 
- Le code de l'anémomètre est maintenant opérationnel et complet.

Séance du 28/10/2022
-

- installation de la librairie TSL2591 library
- installation de la librairie bluedot BME280 TSL2591
- Librairies BME hors de Arduino, recherche et téléchargement des dossiers nécéssaires

Séance du 18/11/2022
-

- Réalisation du code capteur de lumière

Séance du 25/11/2022
-

- Récupération du code de l'équipe de l'année dernière
- Installation de la librairie Adafruit
- Le code de l'année passé ne fonctionne pas, les valeurs globales : temperature, pression et humidite restent à 0. 

Séance du 01/12/2022
-

- Réalisation du code capteur de lumière et capteur de pression, humidité et température
- Installation des librairies :
  - Adafruit
  - ESP32 Time Interrupt
- Création du répertoire bibliothèques. Ce repertoire contient, un fichier texte avec la liste de toutes les bibliothèques installées et les fonctions qui les utilisent et les répertoires ".zip" à inclurent dans arduino.

Séance du 09/12/2022
-

- Finalisation du code capteur de lumière et capteur de pression, humidité et température
- La fonction interrupt / timer de l'ESP32, retourne des erreurs et empêche la bonne lecture des résultats.
  Le problème provient de la tension renvoyée par le système, elle est trop élevée.
  Au final, on a choisi de ne pas faire appel à cette fonction parce que pour le code final, on va récupérer toutes les données en mêmes temps. Pour cela, cette fonction ne nous sera pas utile.
- Mise en commun des codes et réalisation d'un main récupérant toutes les données à un interval de temps donné.


Séance du 20/12/2022
-

- Travail sur le système de récupération des données avec une trame LoRa
- LoRa : est un protocol réseau. Elle permet la modulation d'ondes radio et une transmission radio longue portée à bas débit. Cette technologie est la plus adaptée à notre système parce qu'on doit communiquer peu d'informations et peu souvent. Notre système est positionner à l'extérieur et doit communiquer avec une application située plus loin.
- Lors de cette séance, j'ai mal compris une de nos discussion. J'ai travaillé sur une interface web qui receptionne la trame LoRa. Cependant, l'application que nous devons rejoindre est déjà existante. Au final, j'ai perdu le temps d'une séance pour le projet.  

Séance du 09/01/2023
-

- Travail en binome sur la trame LoRa.
- Le code fourni n'est pas compilable, séance de débuggage.
- On relève un problème de fréquence pour la transmission.
- L'initialisation de la fréquance n'est pas fonctionnelle.
- La définition de type pour certaines fonctions était mal effectuée et provoquait des erreur : changement du type build en void.
