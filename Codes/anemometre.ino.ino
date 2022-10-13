#include <ESP32TimerInterrupt.h>
#include <ESP32TimerInterrupt.hpp>

#define ANEMOMETRE 27
#define MEASURE 13
#define LED_R 33
#define RAYON 0,07 // rayon de l'anemometre de 7 cm

float vitesseVent = 0;
int tourAnemo=0 ;
int tempsTimer = 10 ;

hw_timer_t *My_timer = NULL;

void IRAM_ATTR onTimer(){
  Serial.println("-------------------------------------------------------------------") ;
  Serial.print("Nombre de 1/2 tour : " ) ;
  Serial.println(tourAnemo) ;
  //3.6 pour passer de m/s en km/h
  vitesseVent = (PI * RAYON * 2 * tourAnemo)/tempsTimer*3.6 ;
  Serial.print("Vitesse du vent : (km/h)") ;
  Serial.println(String(vitesseVent, 2)) ;
  Serial.println("-------------------------------------------------------------------") ;
  tourAnemo = 0 ;
}

void setup() {
 
  Serial.begin(115200);
  pinMode(LED_R, OUTPUT);
  pinMode (ANEMOMETRE, INPUT);
  pinMode(MEASURE, OUTPUT);
  digitalWrite(MEASURE, HIGH);

  My_timer = timerBegin(0, 80, true);
  timerAttachInterrupt(My_timer, &onTimer, true);
  timerAlarmWrite(My_timer, tempsTimer*1000000, true); // microsecondes
  timerAlarmEnable(My_timer);
  
  attachInterrupt(ANEMOMETRE,comptageAnemo,FALLING) ;
}

void loop()
{  
}

void comptageAnemo()
{
  tourAnemo ++ ;
}
