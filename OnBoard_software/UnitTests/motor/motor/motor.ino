#include <Servo.h>

Servo ESC;

int potVal = 0;

void setup() {
  ESC.attach(9,1000,2000);

}

void loop() {
  potVal = analogRead(A0);
  Serial.print("%d \n", potVal);
  potVal = map(potVal, 0, 1023, 0, 180);
  ESC.write(potVal);
}
