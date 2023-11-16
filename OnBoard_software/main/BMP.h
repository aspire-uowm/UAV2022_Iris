#include "WString.h"
#include "HardwareSerial.h"
#include "Adafruit_BMP3XX.h"

#define SEALEVELPRESSURE_HPA (1013.25)  // To be changed

Adafruit_BMP3XX bmp[1] = { Adafruit_BMP3XX()/*, Adafruit_BMP3XX()*/ };

void setBMP() {
    for (int i = 0; i < 1; i++) {

        if (bmp[i].begin_I2C()) Serial.print("Found BMP: " + String(i));
        else { Serial.print("BMP not found \n"); setBMP();}

        // Set up oversampling and filter initialization
        bmp[i].setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
        bmp[i].setPressureOversampling(BMP3_OVERSAMPLING_4X);
        bmp[i].setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
        bmp[i].setOutputDataRate(BMP3_ODR_50_HZ);
    }
}