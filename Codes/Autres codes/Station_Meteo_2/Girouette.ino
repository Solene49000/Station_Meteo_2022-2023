//PROJET STATION METEO
//AMBRE ALLOUIS - SOLENE GUILLAUME
//ANNEE 2022-2023

//#include "donnees.h"
//#include "definition.h"

void girouette() {
  
  int sensorValue = analogRead(GIROUETTE);
  int directionVent;
  if (sensorValue > 3216 && sensorValue <= 3600 )
  {
    directionVent = 12; // Ouest
  }
  if (sensorValue > 2869 && sensorValue <= 3216)
  {
    directionVent = 14; // Nord Ouest
  }
  if (sensorValue > 2646 && sensorValue <= 2869)
  {
    directionVent = 13; // Nord Ouest Ouest
  }
  if (sensorValue > 2417 && sensorValue <= 2646)
  {
    directionVent = 0; // Nord
  }
  if (sensorValue > 2121 && sensorValue <= 2417)
  {
    directionVent = 15; // Nord Nord Ouest
  }
  if (sensorValue > 1934 && sensorValue <= 2121)
  {
    directionVent = 10; // Sud Ouest
  }
  if (sensorValue > 1645 && sensorValue <= 1934)
  {
    directionVent = 11; // Sud Ouest Ouest
  }
  if (sensorValue > 1312 && sensorValue <= 1645)
  {
    directionVent = 2; // Nord Est
  }
  if (sensorValue > 1008 && sensorValue <= 1312)
  {
    directionVent = 1; // Nord Nord Est
  }
  if (sensorValue > 725 && sensorValue <= 1008)
  {
    directionVent = 8; // Sud
  }
  if (sensorValue > 543 && sensorValue <= 725)
  {
    directionVent = 9; // Sud Sud Ouest
  }
  if (sensorValue > 338 && sensorValue <= 543)
  {
    directionVent = 6; // Sud Est
  }
  if (sensorValue > 184 && sensorValue <= 338)
  {
    directionVent = 7; // Sud Sud Est
  }
  if (sensorValue > 111 && sensorValue <= 184)
  {
    directionVent = 4; // Est
  }
  if (sensorValue > 64 && sensorValue <= 111)
  {
    directionVent = 3; // Nord Est Est
  }
  if (sensorValue > 1 && sensorValue <= 64)
  {
    directionVent = 5; // Sud Est Est
  }
  ds.donnees_girouette = static_cast<double>(directionVent);

}
