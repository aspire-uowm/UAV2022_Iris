#include "BMP.h"
#include "GPS.h"
#include "LSM.h"

uint32_t timer = millis();

void setup(){
  Serial.begin(115200);

  // ===================== BMP388 =================================
  // hardware I2C mode, can pass in address & alt Wire
  
}

void loop(){

  
  if (millis() - timer > 2000) { // 2s
    timer = millis(); // reset the timer

  }
  // =========================== BMP ================================================
  Serial.println();
}