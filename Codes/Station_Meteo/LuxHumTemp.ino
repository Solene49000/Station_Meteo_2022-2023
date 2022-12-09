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
