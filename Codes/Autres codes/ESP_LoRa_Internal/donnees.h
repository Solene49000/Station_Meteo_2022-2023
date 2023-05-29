#include <LoRa.h>

#include "definition.h"
#include "WiFi.h"



struct data_trame{

 char type;
 uint8_t mac[6];
 double pluviometre;
 double anemometre;
 double girouette;
 double donneestsl;
 double donneesbme;
 double tensionbattery;
 int checkbytes;

}ds;


/*void setup_donnees() {
  if(!ccs.begin(0x5B)){
    Serial.println("Failed to start sensor! Please check your wiring.");
    while(1);
  }
  */
  
 void read_mac(uint8_t* mac){//Permet de récuperer l'adresse mac

   uint8_t baseMac[6];

   // Get MAC address for WiFi station
   esp_read_mac(mac, ESP_MAC_WIFI_STA);

   char baseMacChr[18] = {0};
   sprintf(baseMacChr, "%02X:%02X:%02X:%02X:%02X:%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

   String macAddress = String(baseMacChr);

   Serial.print("MAC Address :: ");
   Serial.println(baseMacChr);

  //Serial.printf("mac : %02X:%02X:%02X:%02X:%02X:%02X \n",mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
}

void build_trame(uint8_t *payload){ //permet de fabriquer la trame

  ds.type = 'I';
  read_mac(ds.mac);
  ds.pluviometre = static_cast<double>(1);
  ds.anemometre = static_cast<double>(7.00);
  ds.girouette = static_cast<double>(3.00);
  ds.donneestsl = static_cast<double>(4.00);
  ds.donneesbme = static_cast<double>(5.00);
  ds.tensionbattery = static_cast<double>(6.00);
  ds.checkbytes = 0;

  Serial.printf("Trame before cast : %c | %X:%X:%X:%X:%X:%X | %f | %f | %f | %f| %f | %f | %d\n",ds.type,ds.mac[0],ds.mac[1],ds.mac[2],ds.mac[3],ds.mac[4],ds.mac[5],ds.mac[6],ds.pluviometre,ds.anemometre,ds.girouette,ds.donneestsl,ds.donneesbme,ds.tensionbattery,ds.checkbytes);
  
  payload[0] = uint8_t(ds.checkbytes);
  for (int i = 1; i<7; i++){
    payload[i] = uint8_t(ds.mac[i-1]);
  }
  
  payload[7]= uint8_t(ds.pluviometre);
  payload[8]= uint8_t(ds.anemometre);
  payload[9]= uint8_t(ds.girouette);
  payload[10]= uint8_t(ds.donneestsl);
  payload[11]= uint8_t(ds.donneesbme);
  payload[12] = uint8_t(ds.tensionbattery);
  payload[13]=uint8_t(ds.checkbytes);

}
