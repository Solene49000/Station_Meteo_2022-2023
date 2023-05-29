#include "definition.h"
#include "WiFi.h"

struct data_trame{

 char type;
 uint8_t mac[6];
 double temperature;
 double pressure;
 double humidity;
 double luminosite;
 double pluviometrie;
 double vitesseVent;
 double orientationVent;
 double tensionBattery;
 int checkbytes = 0;

}ds;

/*void setup_donnees() {
  if(!ccs.begin(0x5B)){
    Serial.println("Failed to start sensor! Please check your wiring.");
    while(1);
  }
  */
  
uint8_t read_mac(uint8_t *mac){//Permet de récuperer l'adresse mac
  esp_efuse_read_mac(mac);
}

uint8_t build_trame(uint8_t *payload){ //permet de fabriquer la trame

  ds.type = 'M';
  read_mac(ds.mac);
  ds.temperature;
  ds.pressure;
  ds.humidity;
  ds.luminosite;
  ds.pluviometrie;
  ds.vitesseVent;
  ds.orientationVent;
  ds.tensionBattery;
  ds.checkbytes;

  Serial.printf("Trame before cast : %X | %X:%X:%X:%X:%X:%X | %f | %f | %f | %f| %f | %f | %f | %f | %d\n",ds.type,ds.mac[0],ds.mac[1],ds.mac[2],ds.mac[3],ds.mac[4],ds.mac[5],ds.mac[6],ds.temperature,ds.pressure,ds.humidity,ds.luminosite,ds.pluviometrie,ds.vitesseVent,ds.orientationVent,ds.tensionBattery,ds.checkbytes);
  
  payload[0] = uint8_t(ds.checkbytes);

  for (int i = 1; i<7; i++){
    payload[i] = uint8_t(ds.mac[i-1]);
  }

  payload[7]= uint16_t(ds.temperature);
  payload[8]= uint16_t(ds.pressure);
  payload[9]= uint8_t(ds.humidity);
  payload[10]= uint32_t(ds.luminosite);
  payload[11]= uint16_t(ds.pluviometrie);
  payload[12]= uint8_t(ds.vitesseVent);
  payload[13]= uint8_t(ds.orientationVent);
  payload[14]= uint16_t(ds.tensionBattery);
  payload[15]= uint8_t(ds.checkbytes);

  

  
}
