struct datas_w { // 255 <=> error
  uint8_t macSTA[6];
  float   temp      = 225;        // -50 to +80 °C
  uint8_t hygro     = 255;        //  0 to 100%
  float   atm       = 0;          // 300 - 1100 hPa
  uint8_t wind_s    = 255;         // km/h
  uint8_t wind_d    = 255;         // step 2° - divided by 2 (0-180 =>0-360)
  float   rain      = 0;
  uint16_t lum      = 0;           // 40000 lux
  float    v_bat      = 255;        // 0 to 16 V, sent in 1/10 de V
  uint8_t  charg_bat  = 255;    // 0 to 100%
} dw;
