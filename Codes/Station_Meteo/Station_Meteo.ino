//PROJET STATION METEO
//AMBRE ALLOUIS - SOLENE GUILLAUME
//ANNEE 2022-2023


//LIBRARIES
#include <Adafruit_BusIO_Register.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_I2CRegister.h>
#include <Adafruit_SPIDevice.h>
#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_TSL2591.h"

//PINNING DE L'ESP
#define MEASURE 13
#define LED_R 33
#define LED_G 25
#define ANEMOMETRE 27
#define PLUVIOMETRE 32
#define GIROUETTE 36

//VARIABLES GLOBALES
int compt=0 ;
float quantiteEau = 0;
unsigned long startTime;  
unsigned long currentTime;
const unsigned long period = 1000;

void setup() {
  //Supply ON
  pinMode(MEASURE, OUTPUT);
  digitalWrite(MEASURE, HIGH);
  //Serial monitor port
  Serial.begin(9600);
  //Pin definition
  pinMode (LED_R, OUTPUT);
  pinMode (LED_G, OUTPUT);
  pinMode (ANEMOMETRE, INPUT);
  pinMode (PLUVIOMETRE, INPUT);
  pinMode (GIROUETTE, INPUT);  
  //Interrupts
  attachInterrupt(PLUVIOMETRE,comptage,FALLING);
  //Variable definition
  startTime = millis();
  
}

void loop() {
  
  digitalWrite(LED_G, HIGH);
  delay(100);
  digitalWrite(LED_G, LOW);
  delay(100);
  girouette();
  currentTime = millis();
  if (currentTime - startTime >= period)//test whether the period has elapsed
  {
    Serial.println("Nombre de basculeeeeees : ") ;
    Serial.println(compt) ;
    delay(1000);
    Serial.println("Quantité d'eau (mm): ");
    Serial.println(calcul_quantite_eau());
    startTime = currentTime;
  }
}
