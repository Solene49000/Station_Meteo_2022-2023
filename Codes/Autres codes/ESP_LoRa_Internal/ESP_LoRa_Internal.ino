#include "definition.h"
#include "donnees.h"
#include "esp_lora.h"

//Trame
uint8_t payload[PAYLOAD_LEN];

void setup() {

  pinMode(MEASURE, OUTPUT);
  digitalWrite(MEASURE,HIGH);

  SPI.begin(SCK, MISO, MOSI);
  LoRa.setPins(SS, RST, DI0);
  
  Serial.begin(9600);
}

void debug_trame(uint8_t *payload){ //Fonction de debug de la trame
  
  //Trame forme : I|macAdresse|pluvioanemometre|anemometre|girouette|donneestsl|donneesbme|checkbytes
  build_trame(payload);
  uint16_t pluviometre = payload[7];
  uint16_t anemometre = payload[8];
  uint16_t girouette = payload[9];
  uint16_t donneestsl = payload[10];
  uint16_t donneesbme = payload[11];
  uint16_t tensionbattery = payload[12];
  uint16_t checkbytes = payload[13];

  
 Serial.printf("Trame after cast : %c | %X:%X:%X:%X:%X:%X | %d | %d | %d | %d | %d | %d \n",payload[0],payload[1],payload[2],payload[3],payload[4],payload[5],payload[6],pluviometre,anemometre,girouette,donneestsl,donneesbme,tensionbattery);
  
}

void loop() {
  build_trame(payload);
  debug_trame(payload);
  lora_send_trame(payload);
}
