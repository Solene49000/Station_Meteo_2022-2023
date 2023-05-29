#include <ESP32TimerInterrupt.h>
#include <ESP32TimerInterrupt.hpp>

#define ANEMOMETRE 27
#define MEASURE 13
#define LED_R 33
#define RAYON 0.07 // rayon de l'anemometre de 7 cm
#define B1000000 64
#define B110 6

float vitesseVent;
int tourAnemo=0 ;
unsigned long startTime_A;  
unsigned long currentTime_A;
const unsigned long period_A = 10000;

void comptageAnemo();
void Anemo();

void setup() {
  Serial.begin(115200);
  Serial.println("test");
  pinMode(LED_R, OUTPUT);
  pinMode (ANEMOMETRE, INPUT);
  pinMode(MEASURE, OUTPUT);
  digitalWrite(MEASURE, HIGH);
  attachInterrupt(ANEMOMETRE,comptageAnemo,FALLING) ; 
}
 
void loop()
{
  currentTime_A = millis();
  if (currentTime_A - startTime_A >= period_A)//test whether the period has elapsed
  { 
    Anemo();
    startTime_A = currentTime_A ;
  }
}

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
