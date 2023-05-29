void Anemo(){
  Serial.print("Nombre de 1/2 tour : " ) ;
  Serial.println(tourAnemo) ;
  //3.6 pour passer de m/s en km/h
  vitesseVent = ((PI*RAYON*2*tourAnemo)/period_A)*3.6*1000 ;
  Serial.print("Vitesse du vent : (km/h) ") ;
  Serial.println(String(vitesseVent, 2)) ;
  tourAnemo = 0 ;
}
void comptageAnemo()
{
  tourAnemo ++ ;
}
