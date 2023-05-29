#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_TSL2591.h"

#define LED_R 33
#define MEASURE 13

Adafruit_BME280 bme;
Adafruit_TSL2591 tsl = Adafruit_TSL2591(2591);

void calculateValues_BME_TSL();
void printValuesSerial();

float temperature = 0.0;
float pression = 0.0;
float humidite = 0.0;
float luminosite = 0.0;   
unsigned long delayTime;

void setup() {
  pinMode(LED_R, OUTPUT);
  pinMode(MEASURE, OUTPUT);
  digitalWrite(MEASURE, HIGH);
  Serial.begin(9600);
  bme.begin(0x76);
  tsl.begin(0x76);
  tsl.setGain(TSL2591_GAIN_MED); 
  tsl.setTiming(TSL2591_INTEGRATIONTIME_300MS);
}

void loop() {
  digitalWrite(LED_R, HIGH);
  calculateValues_BME_TSL();
  printValuesSerial();
  delay(2000); 
}

void calculateValues_BME_TSL(){
  temperature = bme.readTemperature();
  pression = bme.readPressure() / 100;
  humidite = bme.readHumidity();
  luminosite = tsl.getLuminosity(TSL2591_VISIBLE);
}

void printValuesSerial(){
  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println(" *C");
  
  Serial.print("Pression = ");
  Serial.print(pression);
  Serial.println(" hPa");

  Serial.print("Humidité = ");
  Serial.print(humidite);
  Serial.println(" %");
  
  Serial.print(F("Luminosité = "));
  Serial.print(luminosite, DEC);
  Serial.println(" lux");
}
