//PROJET STATION METEO
//AMBRE ALLOUIS - SOLENE GUILLAUME
//ANNEE 2022-2023

void CalculateValues_BME_TSL(){
  temperature = bme.readTemperature();
  pression = bme.readPressure() / 100;
  humidite = bme.readHumidity();
  luminosite = tsl.getLuminosity(TSL2591_VISIBLE);
}

void PrintValuesSerial(){
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

  
  ds.donnees_pression = static_cast<double>(pression);
  ds.donnees_humidite = static_cast<double>(humidite);
  ds.donnees_luminosite = static_cast<double>(luminosite);
  ds.donnees_temperature = static_cast<double>(temperature);
}
