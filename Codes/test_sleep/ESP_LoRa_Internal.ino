//#include "definition.h"
//#include "donnees.h"
//#include "esp_lora.h"

// *** Trame ************************ //
uint8_t payload[PAYLOAD_LEN];

void LoRa_Envoi() {
  build_trame(payload);
  Serial.printf("Trame after cast : %c | %X:%X:%X:%X:%X:%X | %d | %d | %d | %d %d | %d | %d | %d | %d \n",payload[0],payload[1],payload[2],payload[3],payload[4],payload[5],payload[6], payload[7],payload[8],payload[9],payload[10],payload[11],payload[12],payload[13], payload[14],payload[15],payload[16]);
  lora_send_trame(payload);
}
