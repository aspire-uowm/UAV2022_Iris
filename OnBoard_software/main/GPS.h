#include <Adafruit_GPS.h>

// Connect to the GPS on the hardware port
Adafruit_GPS GPS(&Serial1);

// Set GPSECHO to 'false' to turn off echoing the GPS data to the Serial console
// Set to 'true' if you want to debug and listen to the raw GPS sentences
#define GPSECHO false

void setGPS();
float* getGPSValues();