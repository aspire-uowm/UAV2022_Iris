#include <NewPing.h>

#include "BMP.h"
#include "GPS.h"
#include "LSM.h"

#define TRIGGER_PIN  47  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     49  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

#define AIR_PRESS A5

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

uint32_t timer = millis();

long duration, distance;

void setup() {
    Serial.begin(115200);

    setBMP();
    setLSM();
    //setGPS();
}

void loop() {

    
    // read data from the GPS in the 'main loop'
    char c = GPS.read();
    // if you want to debug, this is a good time to do it!
    if (GPSECHO)
        if (c) Serial.print(c);
    // if a sentence is received, we can check the checksum, parse it...
    if (GPS.newNMEAreceived()) {
        // a tricky thing here is if we print the NMEA sentence, or data
        // we end up not listening and catching other sentences!
        // so be very wary if using OUTPUT_ALLDATA and trying to print out data
        Serial.print(GPS.lastNMEA()); // this also sets the newNMEAreceived() flag to false
        if (!GPS.parse(GPS.lastNMEA())) // this also sets the newNMEAreceived() flag to false
            return; // we can fail to parse a sentence in which case we should just wait for another
    }


    if (millis() - timer > 200) {
        timer = millis();           // reset timer
        // ================ BMP ============
        for (int i = 0; i < 2; i++) {
            if (!bmp[i].performReading())
                Serial.println("Failed to perform reading from BMP: " + String(i) + " :(");
        }

        Serial.print("Temperature Diff: " + 
            String((float)bmp[0].temperature - (float)bmp[1].temperature) 
        + '\n');
        Serial.print("Pressure Diff: " + 
            String((float)bmp[0].pressure / 100.0 - (float)bmp[1].pressure / 100.0) 
        + '\n');
        Serial.print("Altitude Diff: " + 
            String(bmp[0].readAltitude(SEALEVELPRESSURE_HPA) - bmp[1].readAltitude(SEALEVELPRESSURE_HPA)) 
        + "\n\n");
        
        // ========= LSM ==================
        lsm[0].read(); /* ask it to read in the data */

        sensors_event_t a1, m1, g1, temp1; /* Get a new sensor event */

        lsm[0].getEvent(&a1, &m1, &g1, &temp1);

        lsm[1].read(); /* ask it to read in the data */

        sensors_event_t a2, m2, g2, temp2; /* Get a new sensor event */

        lsm[1].getEvent(&a2, &m2, &g2, &temp2);


        String acc = "ACC diff-> x: " + String(a1.acceleration.x - a2.acceleration.x)
                    + ", y: " + String(a1.acceleration.y - a2.acceleration.y)
                    + ", z: " + String(a1.acceleration.z - a2.acceleration.z) + '\n'
        ; Serial.print(acc);

        String mag = "MAG diff-> x: " + String(m1.magnetic.x - m2.magnetic.x)
                    + ", y: " + String(m1.magnetic.y - m2.magnetic.y)
                    + ", z: " + String(m1.magnetic.z - m2.magnetic.z) + '\n'
        ; Serial.print(mag);

        String gyr = "GYRO diff-> x: " + String(g1.gyro.x - g2.gyro.x)
                    + ", y: " + String(g1.gyro.y - g2.gyro.y)
                    + ", z: " + String(g1.gyro.z - g2.gyro.z) + "\n\n"
        ; Serial.print(gyr);

        // ============= GPS =============================
        Serial.print("\nTime: ");
        
        if (GPS.hour < 10) Serial.print('0');
        Serial.print(GPS.hour, DEC); Serial.print(':');
        
        if (GPS.minute < 10) Serial.print('0');
        Serial.print(GPS.minute, DEC); Serial.print(':');
        
        if (GPS.seconds < 10) Serial.print('0');
        Serial.print(GPS.seconds, DEC); Serial.print('.');
        
        if (GPS.milliseconds < 10) Serial.print("00");
        else if (GPS.milliseconds > 9 && GPS.milliseconds < 100) Serial.print("0");
        
        Serial.println(GPS.milliseconds);
        
        Serial.print("Date: ");
        Serial.print(GPS.day, DEC); Serial.print('/');
        Serial.print(GPS.month, DEC); Serial.print("/20");
        Serial.println(GPS.year, DEC);
        
        Serial.print("Fix: "); Serial.print((int)GPS.fix);
        Serial.print(" quality: "); Serial.println((int)GPS.fixquality);

        if (GPS.fix) {
            Serial.print("Location: ");
            Serial.print(GPS.latitude, 4); Serial.print(GPS.lat);Serial.print(", ");
            Serial.print(GPS.longitude, 4); Serial.println(GPS.lon);
            
            Serial.print("Speed (knots): "); Serial.println(GPS.speed);
            
            Serial.print("Angle: "); Serial.println(GPS.angle);
            
            Serial.print("Altitude: "); Serial.println(GPS.altitude);
            
            Serial.print("Satellites: "); Serial.println((int)GPS.satellites);
            
            Serial.print("Antenna status: "); Serial.println((int)GPS.antenna);
        }

        // Send ping, get distance in cm and print result (0 = outside set distance range)
        Serial.print("Ping: " + String(sonar.ping_cm()) + "cm\n");

        // Get Air pressure value
        int diffAirPress = analogRead(AIR_PRESS);
        Serial.print("Diff Air Pressure: " + String(diffAirPress) + "\n\n");
    }
}