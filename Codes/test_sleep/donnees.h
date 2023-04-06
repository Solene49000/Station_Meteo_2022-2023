#include <LoRa.h>
#include <iostream>
#include <cstdint>

using namespace std;

struct data_trame{
 char type;
 uint8_t mac[6];
 double donnees_pluviometre;
 double donnees_anemometre;
 double donnees_girouette;
 double donnees_pression;
 double donnees_humidite;
 double donnees_luminosite;
 double donnees_temperature;
 double donnees_batterie;
 int checkbytes;
}ds;
  
 void read_mac(uint8_t* mac){//Permet de récuperer l'adresse mac
   uint8_t baseMac[6];

   // Get MAC address for WiFi station
   esp_read_mac(mac, ESP_MAC_WIFI_STA);

   char baseMacChr[18] = {0};
   sprintf(baseMacChr, "%02X:%02X:%02X:%02X:%02X:%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

   String macAddress = String(baseMacChr);

   Serial.print("Adresse Mac :: ");
   Serial.println(baseMacChr);
}

void build_trame(uint8_t *payload){ //permet de fabriquer la trame
  ds.type = 'I';
  read_mac(ds.mac);
  Serial.printf("Trame before cast : type | adresse mac | pluviometre | anemometre | girouette | pression (16bit) |humidite | luminosite | temperature | batterie | checkbytes\n");
  Serial.printf("Trame before cast : %c | %X:%X:%X:%X:%X:%X | %f | %f | %f | %f| %f | %f | %f | %f | %d\n",ds.type,ds.mac[0],ds.mac[1],ds.mac[2],ds.mac[3],ds.mac[4],ds.mac[5],ds.mac[6],ds.donnees_pluviometre,ds.donnees_anemometre,ds.donnees_girouette,ds.donnees_pression,ds.donnees_humidite,ds.donnees_luminosite,ds.donnees_temperature,ds.donnees_batterie,ds.checkbytes);
  
  payload[0] = uint8_t(ds.checkbytes);
  for (int i = 1; i<7; i++){
    payload[i] = uint8_t(ds.mac[i-1]);
  }
  payload[7]= uint8_t(ds.donnees_pluviometre);
  payload[8]= uint8_t(ds.donnees_anemometre);
  payload[9]= uint8_t(ds.donnees_girouette);
  // On a la pression sous 16 bits, on coupe la donnée en deux données de 8 bits
  uint8_t Premier_octet_pression = (int)ds.donnees_pression >> 8;
  uint8_t Dernier_octet_pression = (int)ds.donnees_pression & 0xff;
  payload[10]= uint8_t(Premier_octet_pression);
  payload[11]= uint8_t(Dernier_octet_pression);
  payload[12]= uint8_t(ds.donnees_humidite);
  payload[13] = uint8_t(ds.donnees_luminosite);
  payload[14]= uint8_t(ds.donnees_temperature);
  payload[15]= uint8_t(ds.donnees_batterie);
  payload[16]=uint8_t(ds.checkbytes);
}
