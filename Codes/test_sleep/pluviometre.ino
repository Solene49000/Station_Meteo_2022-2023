//PROJET STATION METEO
//AMBRE ALLOUIS - SOLENE GUILLAUME
//ANNEE 2022-2023

#define QUANTITE_EAU_PAR_BASCULE 0.2794 //en mm

float Pluviometre (int nb_bacules){
  float quantite_eau;
  quantite_eau = QUANTITE_EAU_PAR_BASCULE * nb_bacules;
  Serial.print("Quantité d'eau : ");
  Serial.print(quantite_eau);
  Serial.println(" mm/m²");
  ds.donnees_pluviometre = static_cast<double>(quantite_eau);
  return 0;
}
