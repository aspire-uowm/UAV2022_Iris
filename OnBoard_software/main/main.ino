#include "BMP.h"
#include "GPS.h"
#include "LSM.h"

uint32_t timer = millis();

void setup(){
  Serial.begin(115200);

  //setBMP();
  setLSM(0); setLSM(1);
  //setGPS();
}

void loop(){

  // ================ BMP ============
  //if(!bmp.performReading())
  //  Serial.println("Failed to perform reading :(")
  //;

  //(float)bmp.temperature;
  //(float)bmp.pressure/100.0;
  //bmp.readAltitude(SEALEVELPRESSURE_HPA);


  // ========= LSM ==================
  lsm[0].read();  /* ask it to read in the data */ 

  sensors_event_t a1, m1, g1, temp1; /* Get a new sensor event */ 

  lsm[0].getEvent(&a1, &m1, &g1, &temp1); 

  lsm[1].read();  /* ask it to read in the data */ 

  sensors_event_t a2, m2, g2, temp2; /* Get a new sensor event */ 

  lsm[1].getEvent(&a2, &m2, &g2, &temp2); 


  String acc =  
    "ACC diff-> x: " + String(a1.acceleration.x - a2.acceleration.x) + 
    ", y: "+ String(a1.acceleration.y - a2.acceleration.y) +
    ", z: "+ String(a1.acceleration.z - a2.acceleration.z)
  ;//Serial.println(acc);
  
  String mag = 
    "MAG diff-> x: "+ String(m1.magnetic.x - m2.magnetic.x) + 
    ", y: "+ String(m1.magnetic.y - m2.magnetic.y) +
    ", z: "+ String(m1.magnetic.z - m2.magnetic.z)
  ;//Serial.println(mag);

  String gyr = 
    "GYRO diff-> x: "+ String(g1.gyro.x - g2.gyro.x) +
    ", y: "+ String(g1.gyro.y - g2.gyro.y) +
    ", z: "+ String(g1.gyro.z - g2.gyro.z)
  ;//Serial.println(gyr);

  String all = 
  "Gyro one-> x: " + String(m1.magnetic.x) +
  ", y: " + String(m1.magnetic.y) +
  ", z: " + String(m1.magnetic.z)
  ; Serial.print(all);
  // ============= GPS =============================
  //char c = GPS.read();

  //if (GPSECHO) if (c) Serial.print(c); // debug
  
  //if (GPS.newNMEAreceived()) {
  //  if (!GPS.parse(GPS.lastNMEA())) return 0; // sets the newNMEAreceived() flag to false
  //}

  //Serial.print("Fix: "); Serial.print((int)GPS.fix);
  //Serial.print(" quality: "); Serial.println((int)GPS.fixquality);
  
  /* if (GPS.fix) {
    GPS.latitude,    GPS.longitude,    GPS.altitude,
    GPS.angle,       GPS.speed, // in knots
    (float)GPS.satellites,  (float)GPS.antenna
  }*/

  //if (millis() - timer > 2000) { // 2s
  //  timer = millis(); // reset the timer

  //}
  Serial.println();
  delay(15);
}