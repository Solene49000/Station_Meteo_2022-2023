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


void loop() {
  build_trame(payload);
  lora_send_trame(payload);
}
