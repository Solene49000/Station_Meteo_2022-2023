//PROJET STATION METEO
//AMBRE ALLOUIS - SOLENE GUILLAUME
//ANNEE 2022-2023

void Anemometre(){
  //3.6 pour passer de m/s en km/h
  vitesseVent = ((PI*RAYON*2*tourAnemo)/period_A)*3.6*1000 ;
  Serial.print("Vitesse du vent : ") ;
  Serial.print(String(vitesseVent, 2)) ;
  Serial.print(" km/h\n") ;
  ds.donnees_anemometre = static_cast<double>(vitesseVent);
  tourAnemo = 0 ;
}
void comptageAnemo()
{
  tourAnemo ++ ;
}
