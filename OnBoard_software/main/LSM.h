#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>  // not used in this demo but required!
#include <Adafruit_LSM9DS1.h>

Adafruit_LSM9DS1 lsm[2] = {Adafruit_LSM9DS1(), Adafruit_LSM9DS1()};

void setLSM(int i){
  
  while (!lsm[i].begin()) Serial.println("Not Yet");
  Serial.println("Found LSM9DS1 9DOF");
  
  // Set the accelerometer range
  lsm[i].setupAccel(lsm[i].LSM9DS1_ACCELRANGE_2G);
  //lsm[i].setupAccel(lsm[i].LSM9DS1_ACCELRANGE_4G);
  //lsm[i].setupAccel(lsm[i].LSM9DS1_ACCELRANGE_8G);
  //lsm[i].setupAccel(lsm[i].LSM9DS1_ACCELRANGE_16G);
  
  // Set the magnetometer sensitivity
  lsm[i].setupMag(lsm[i].LSM9DS1_MAGGAIN_4GAUSS);
  //lsm[i].setupMag(lsm[i].LSM9DS1_MAGGAIN_8GAUSS);
  //lsm[i].setupMag(lsm[i].LSM9DS1_MAGGAIN_12GAUSS);
  //lsm[i].setupMag(lsm[i].LSM9DS1_MAGGAIN_16GAUSS);

  // Setup the gyroscope
  lsm[i].setupGyro(lsm[i].LSM9DS1_GYROSCALE_245DPS);
  //lsm[i].setupGyro(lsm[i].LSM9DS1_GYROSCALE_500DPS);
  //lsm[i].setupGyro(lsm[i].LSM9DS1_GYROSCALE_2000DPS);
}