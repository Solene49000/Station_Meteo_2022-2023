// *** get_macAdress ************
   esp_efuse_mac_get_default(dw.macSTA);
//esp_efuse_read_mac(di.macSTA); deprecated
   Serial.println("== mac STA ======");
   Serial.printf("%02X:%02X:%02X:%02X:%02X:%02X",
                 dw.macSTA[0], dw.macSTA[1], dw.macSTA[2], dw.macSTA[3],
dw.macSTA[4], dw.macSTA[5]);
   Serial.println("");
