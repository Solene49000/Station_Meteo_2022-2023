//PROJET STATION METEO
//AMBRE ALLOUIS - SOLENE GUILLAUME
//ANNEE 2022-2023

// *** LIBRARIES ************************ //
#include <Adafruit_BusIO_Register.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_I2CRegister.h>
#include <Adafruit_SPIDevice.h>
#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_TSL2591.h"
#include <ESP32TimerInterrupt.h>
#include <ESP32TimerInterrupt.hpp>

#include "donnees.h"
#include "esp_lora.h"
#include "WiFi.h"

// *** VARIABLES GLOBALES ************************ //
#define RAYON 0.07 /*Rayon de l'anemometre de 7 cm*/
#define uS_TO_S_FACTOR 1000000  /* A multiplier pour passer de micro-seconde à seconde */
#define CONVERT_MINUTE 1       /* A multiplié pour avoir le temps en minutes */
#define TIME_TO_SLEEP  15        /* Temps sleep en micro-secondes pour l'ESP32 */

// *** PINNING DE L'ESP ************************ //
#define MEASURE 13
#define LED_R 33
#define LED_G 25
#define ANEMOMETRE 27
#define PLUVIOMETRE 32
#define GIROUETTE 36
#define BATTERIE 35

RTC_DATA_ATTR int bootCount;
RTC_DATA_ATTR Adafruit_BME280 bme;
RTC_DATA_ATTR Adafruit_TSL2591 tsl = Adafruit_TSL2591(2591);

RTC_DATA_ATTR int compt=0 ;
RTC_DATA_ATTR float quantiteEau = 0;
RTC_DATA_ATTR const unsigned long period_P = 10000;

RTC_DATA_ATTR unsigned long temps_interrupt;
RTC_DATA_ATTR time_t lastTimeDataSent;
RTC_DATA_ATTR time_t timePassed = time(NULL);
RTC_DATA_ATTR time_t time_now = time(NULL);
RTC_DATA_ATTR int nb_bascules = 0;

RTC_DATA_ATTR float temperature = 0.0;
RTC_DATA_ATTR float pression = 0.0;
RTC_DATA_ATTR float humidite = 0.0;
RTC_DATA_ATTR float luminosite = 0.0;
RTC_DATA_ATTR float vitesseVent;

RTC_DATA_ATTR int tourAnemo=0 ;
RTC_DATA_ATTR const unsigned long period_A = 10000;

// *** Méthode prenant en compte les diféérents types de réveil ************** //
void wakeup_case(){
  esp_sleep_wakeup_cause_t wakeup_reason;
  wakeup_reason = esp_sleep_get_wakeup_cause();
  switch(wakeup_reason)
  {
    case ESP_SLEEP_WAKEUP_EXT0 : 
      Serial.println("Réveil causé par un signal exterrieur utilisant : RTC_IO");
      nb_bascules++;
      Serial.println("Nombre de bascules : ");
      Serial.println(nb_bascules);
      time_now = time(NULL);
      timePassed = time_now-lastTimeDataSent;
      if ( time_t(temps_interrupt) > timePassed )
        temps_interrupt -= timePassed * uS_TO_S_FACTOR;
        Serial.print("Temps actuel : ");
        Serial.println(time_now);
        Serial.print("Temps écoulé : ");
        Serial.println(timePassed);
        Serial.print(" Temps restant timer : "); 
        Serial.println(temps_interrupt);
    break;
    case ESP_SLEEP_WAKEUP_TIMER :
      lastTimeDataSent = time(NULL);
      temps_interrupt = TIME_TO_SLEEP * uS_TO_S_FACTOR;
      Serial.println("Réveil causé par le timer"); 
      Serial.print("Nombre de bascules au bout de ");
      Serial.print(TIME_TO_SLEEP * uS_TO_S_FACTOR);
      Serial.print("s : "); 
      Serial.println(nb_bascules);
      nb_bascules = 0;

      bme.begin(0x76);
      tsl.begin(0x76);
      tsl.setGain(TSL2591_GAIN_MED); 
      tsl.setTiming(TSL2591_INTEGRATIONTIME_300MS);
//  // LoRa
//  SPI.begin(SCK, MISO, MOSI);
//  LoRa.setPins(SS, RST, DI0);

      lecture_donnee();
    break;
    default : 
      Serial.print("Réveil causé par le deep sleep: ");
      Serial.println(wakeup_reason); 
    break;
  }
}

void setup(){
  Serial.begin(115200);
  
  delay(1000); // Attendre pour l'ouverture du Serial Monitor
  
  ++bootCount;
  Serial.print("Boot number: ");
  Serial.println(String(bootCount));
  temps_interrupt = TIME_TO_SLEEP * uS_TO_S_FACTOR * CONVERT_MINUTE;
  // Affichage de la cause du réveil
  wakeup_case();
  
  // Réveil de l'ESP32 toutes les 15 minutes
  esp_sleep_enable_timer_wakeup(temps_interrupt);
  esp_sleep_enable_ext0_wakeup((gpio_num_t)PLUVIOMETRE,0);
  Serial.print("Reveil de l'ESP32 toutes les ");
  Serial.print(String(TIME_TO_SLEEP));
  Serial.println(" secondes ou quand il pleut.");
  // *** SUPPLY ON ************************************ //
  pinMode(MEASURE, OUTPUT);
  digitalWrite(MEASURE, HIGH);
  // *** PIN DEFINITION ******************************* //
  pinMode (LED_R, OUTPUT);
  pinMode (LED_G, OUTPUT);
  pinMode (ANEMOMETRE, INPUT);
  pinMode (PLUVIOMETRE, INPUT_PULLUP);
  pinMode (GIROUETTE, INPUT);

  //if (wakeup_reason == ESP_SLEEP_WAKEUP_TIMER){
   // bme.begin(0x76);
//  tsl.begin(0x76);
//  tsl.setGain(TSL2591_GAIN_MED); 
//  tsl.setTiming(TSL2591_INTEGRATIONTIME_300MS);
//  // LoRa
//  SPI.begin(SCK, MISO, MOSI);
//  LoRa.setPins(SS, RST, DI0);
  //}

  Serial.println("Going to sleep now");
  delay(1000);
  Serial.flush(); 
  esp_deep_sleep_start();
  //setup();
  //Serial.println("This will never be printed");
}

void lecture_donnee() {
  //delay(60000);
  digitalWrite(LED_G, HIGH);
  delay(100);
  digitalWrite(LED_G, LOW);
  delay(100);
  Girouette();
  Pluviometre(nb_bascules);
  //LuxHumTemp
  CalculateValues_BME_TSL();
  PrintValuesSerial();
  // Problèmeeeeeeeeuh
  Anemometre();
  Batterie();
  //LoRa
  //LoRa_Envoi();
}

void loop(){
  //Nothing
}
