#include "BMP.h"
#include "GPS.h"
#include "LSM.h"

uint32_t timer = millis();

void setup(){
  Serial.begin(115200);

  setBMP();
  setLSM();
  setGPS();
}

void loop(){

  getBMP();
  getLSM();
  getGPS();

  if (millis() - timer > 2000) { // 2s
    timer = millis(); // reset the timer

  }
  // =========================== BMP ================================================
  Serial.println();
}