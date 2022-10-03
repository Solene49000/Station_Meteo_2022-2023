#include <ESP32TimerInterrupt.h>
#include <ESP32TimerInterrupt.hpp>

float vitesseVent = 0;
int anemometre=27 ; 
int tourAnemo=0 ;
int instant =0;
int tempsAnemo =1;
int debutTempsAnemo =0;
#define MEASURE 13

void setup()
{
pinMode(MEASURE, OUTPUT);
digitalWrite(MEASURE, HIGH);
Serial.begin(115200) ;
attachInterrupt(anemometre,comptageAnemo,FALLING) ; 
}
void loop()
{
  Serial.println("Nombre de 1/2 tour : " ) ;
  Serial.println(tourAnemo) ;
  cycleAnemometre() ;
  delay(1000);
}
void comptageAnemo()
{
  tourAnemo ++ ;
}

void cycleAnemometre(){
  instant = millis();
  debutTempsAnemo = instant;
  vitesseVent = tourAnemo*2.4;
  Serial.println("Vitesse du vent : (km/h)") ;
  Serial.println(String(vitesseVent, 2)) ;
  //return vitesseVent;
}
