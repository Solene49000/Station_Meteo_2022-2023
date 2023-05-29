int pluviometre=32 ;
int compt=0 ;
float quantiteEau = 0;
#define MEASURE 13

void setup()
{
pinMode(MEASURE, OUTPUT);
digitalWrite(MEASURE, HIGH);
Serial.begin(115200) ;
attachInterrupt(pluviometre,comptage,FALLING) ;
}
void loop()
{
Serial.println("Nombre de bascules : ") ;
Serial.println(compt) ;
delay(1000) ;
Serial.println("Quantité d'eau (mm): ");
Serial.println(calcul_quantite_eau());
}

void comptage(){
compt ++ ;
}

float calcul_quantite_eau (){
  quantiteEau = 0.2794*compt;
  return quantiteEau;
}
