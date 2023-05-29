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
#include <ESP32TimerInterrupt.h>
#include <ESP32TimerInterrupt.hpp>

//PINNING DE L'ESP
#define MEASURE 13
#define LED_R 33
#define LED_G 25
#define ANEMOMETRE 27
#define PLUVIOMETRE 32
#define GIROUETTE 36

Adafruit_BME280 bme;
Adafruit_TSL2591 tsl = Adafruit_TSL2591(2591);

//void calculateValues_BME_TSL();
//void printValuesSerial();

//VARIABLES GLOBALES
#define RAYON 0.07 // rayon de l'anemometre de 7 cm
//#define B1000000 64
//#define B110 6
int compt=0 ;
float quantiteEau = 0;
unsigned long startTime_P;  
unsigned long currentTime_P;
const unsigned long period_P = 10000;

float temperature = 0.0;
float pression = 0.0;
float humidite = 0.0;
float luminosite = 0.0;
float vitesseVent;

int tourAnemo=0 ;
unsigned long startTime_A;  
unsigned long currentTime_A;
unsigned long delayTime;
const unsigned long period_A = 10000;

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
  //Luxmetre
  bme.begin(0x76);
  tsl.begin(0x76);
  tsl.setGain(TSL2591_GAIN_MED); 
  tsl.setTiming(TSL2591_INTEGRATIONTIME_300MS);
  //Interrupts
  attachInterrupt(PLUVIOMETRE,comptage,FALLING);
  attachInterrupt(ANEMOMETRE,comptageAnemo,FALLING) ; 
  //Variable definition
  startTime_P = millis();
  
}

void loop() {
  
  digitalWrite(LED_G, HIGH);
  delay(100);
  digitalWrite(LED_G, LOW);
  delay(100);
  girouette();
  //Toutes les secondes
  currentTime_P = millis();
  if (currentTime_P - startTime_P >= period_P)//test whether the period has elapsed
  {
    //Pluviomètre
    Serial.println("Quantité d'eau (mm): ");
    Serial.println(calcul_quantite_eau());
    //LuxHumTemp
    calculateValues_BME_TSL();
    printValuesSerial();
    //Anemometre
    Anemo();
    //Remise à 0 du compteur temporel
    startTime_P = currentTime_P;
  }
}
