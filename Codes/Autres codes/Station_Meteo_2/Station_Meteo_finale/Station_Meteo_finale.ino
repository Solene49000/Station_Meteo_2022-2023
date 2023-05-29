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

//#include "definition.h"
#include "donnees.h"
#include "esp_lora.h"
#include "WiFi.h"

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
#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  15        /* Time ESP32 will go to sleep (in seconds) A multiplier par 60 pour 15 minutes */

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

RTC_DATA_ATTR int nb_wakeup = 0;

void print_wakeup_reason(){
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch(wakeup_reason)
  {
    case ESP_SLEEP_WAKEUP_EXT0 : Serial.println("Wakeup caused by pluviometre"); break;
    case ESP_SLEEP_WAKEUP_TIMER : Serial.println("Wakeup caused by timer"); break;
    default : Serial.printf("Wakeup was not caused by deep sleep: %d\n",wakeup_reason); break;
  }
}

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
  // LoRa
  SPI.begin(SCK, MISO, MOSI);
  LoRa.setPins(SS, RST, DI0);
  //Interrupts
  attachInterrupt(PLUVIOMETRE,comptage,FALLING);
  attachInterrupt(ANEMOMETRE,comptageAnemo,FALLING) ; 
  //Variable definition
  startTime_P = millis();
  lecture_donnee();
  //wakeup
  //Increment boot number and print it every reboot
  ++nb_wakeup;
  Serial.println("Boot number: " + String(nb_wakeup));
  //Print the wakeup reason for ESP32
  print_wakeup_reason();

  /*  First we configure the wake up source  We set our ESP32 to wake up every 5 seconds  We set our ESP32 to wake up every rain interruption  */
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  Serial.println("Setup ESP32 to sleep for every " + String(TIME_TO_SLEEP) +
  " Seconds");
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_32, 1);
  
  Serial.println("Going to sleep now");
  
  delay(1000);
  Serial.flush(); 
  esp_deep_sleep_start();
  Serial.println("This will never be printed");
  
}

void lecture_donnee() {
  digitalWrite(LED_G, HIGH);
  delay(100);
  digitalWrite(LED_G, LOW);
  delay(100);
  girouette();
  //Toutes les secondes
  currentTime_P = millis();
  if (currentTime_P - startTime_P >= period_P)//test whether the period has elapsed
  { 
    Serial.print("\n-------------------------------------\n");
    //Pluviomètre
    Serial.print("Quantité d'eau : ");
    Serial.print(calcul_quantite_eau());
    Serial.print(" mm \n");
    //LuxHumTemp
    calculateValues_BME_TSL();
    printValuesSerial();
    //Anemometre
    Anemo();
    //LoRa
    LoRa_Envoi();
    //Remise à 0 du compteur temporel
    startTime_P = currentTime_P;
  }
}

void loop(){
  //rien
}
