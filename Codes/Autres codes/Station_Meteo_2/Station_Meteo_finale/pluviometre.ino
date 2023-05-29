//PROJET STATION METEO
//AMBRE ALLOUIS - SOLENE GUILLAUME
//ANNEE 2022-2023

//#include "donnees.h"
//#include "definition.h"

void comptage(){
compt ++ ;
}

float calcul_quantite_eau (){
  quantiteEau = 0.2794*compt;
  ds.donnees_pluviometre = static_cast<double>(quantiteEau);
  return quantiteEau;
}
