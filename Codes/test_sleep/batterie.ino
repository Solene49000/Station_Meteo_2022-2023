//PROJET STATION METEO
//AMBRE ALLOUIS - SOLENE GUILLAUME
//ANNEE 2022-2023

// Méthode permettant l'affichage de la tension de la batterie ************************ //
void Batterie() {
  int sensorValue = analogRead(BATTERIE); 
  Serial.print("Batterie : ");
  Serial.println(sensorValue);
  ds.donnees_batterie = static_cast<double>(sensorValue);
}
