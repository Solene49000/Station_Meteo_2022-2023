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

#include "donnees.h"
#include "esp_lora.h"
#include "WiFi.h"

//VARIABLES GLOBALES
#define RAYON 0.07 /*Rayon de l'anemometre de 7 cm*/
#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  25        /* Time ESP32 will go to sleep (in seconds) A multiplier par 60 pour 15 minutes */



//PINNING DE L'ESP
#define MEASURE 13
#define LED_R 33
#define LED_G 25
#define ANEMOMETRE 27
#define PLUVIOMETRE 32
#define GIROUETTE 36

RTC_DATA_ATTR int bootCount;
Adafruit_BME280 bme;
Adafruit_TSL2591 tsl = Adafruit_TSL2591(2591);

//void calculateValues_BME_TSL();
//void printValuesSerial();

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

/*Method to print the reason by which ESP32has been awaken from sleep*/
void print_wakeup_reason(){
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch(wakeup_reason)
  {
    case ESP_SLEEP_WAKEUP_EXT0 : Serial.println("Wakeup caused by external signal using RTC_IO"); break;
    case ESP_SLEEP_WAKEUP_EXT1 : Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
    case ESP_SLEEP_WAKEUP_TIMER : Serial.println("Wakeup caused by timer"); break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD : Serial.println("Wakeup caused by touchpad"); break;
    case ESP_SLEEP_WAKEUP_ULP : Serial.println("Wakeup caused by ULP program"); break;
    default : Serial.printf("Wakeup was not caused by deep sleep: %d\n",wakeup_reason); break;
  }
}

void setup(){
  //Serial monitor port
  Serial.begin(115200);
  //Take some time to open up the Serial Monitor
  delay(1000); 
  //Increment boot number and print it every reboot
  ++bootCount;
  Serial.println("Boot number: " + String(bootCount));
  //Print the wakeup reason for ESP32
  print_wakeup_reason();
  //We set our ESP32 to wake up every 25 seconds and when it rains
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  esp_sleep_enable_ext0_wakeup((gpio_num_t)PLUVIOMETRE,0);
  Serial.println("Setup ESP32 to sleep for every " + String(TIME_TO_SLEEP) +
  " Seconds"+"or when it rains");
  //Supply ON
  pinMode(MEASURE, OUTPUT);
  digitalWrite(MEASURE, HIGH);
  //Pin definition
  pinMode (LED_R, OUTPUT);
  pinMode (LED_G, OUTPUT);
  pinMode (ANEMOMETRE, INPUT);
  pinMode (PLUVIOMETRE, INPUT_PULLUP);
  pinMode (GIROUETTE, INPUT);
  //bme.begin(0x76);
  //tsl.begin(0x76);
  //tsl.setGain(TSL2591_GAIN_MED); 
  //tsl.setTiming(TSL2591_INTEGRATIONTIME_300MS);
  // LoRa
  //SPI.begin(SCK, MISO, MOSI);
  //LoRa.setPins(SS, RST, DI0);

  Serial.println("Going to sleep now");
  delay(1000);
  Serial.flush(); 
  esp_deep_sleep_start();
  Serial.println("This will never be printed");
}

void loop(){
  //This is not going to be called
}
