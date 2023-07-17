#include <Servo.h>
//SERVOS
// Numbering - Position - Model
// 1 - Aileron left - SG92R
// 2 - Flap left - FS5106M
// 3 - Flap right - FS5106M
// 4 - Aileron right - SG92R
// 5 - Elevetor - SG92R
// 6 - Rudder - SG92R
// 7 - Front Hatch - SG92R
// 8 - Back Hatch -  SG92R


Servo myservo1; 
Servo myservo2; 
Servo myservo3; 
Servo myservo4; 
Servo myservo5; 
Servo myservo6; 
Servo myservo7; 
Servo myservo8; 

const byte CH1 = 21; // CH1 - Roll
const byte CH2 = 20; // CH2 - Pitch
const byte CH3 = 19; // CH3 - Thrust
const byte CH4 = 18; // CH4 - Yaw
const byte CH5 = 17; // CH5- VRA,Pot- Flap
const byte CH6 = 16; // CH6 - SWC- 0, FTS - 1,NONE - 2,HATCH

 long CH4_PWM_new = 0;
 long CH1_PWM_new = 0;

int val2;
int val2_1;
int val4;
int val8;

// leds
const int ledPin = 10;


void setup() {
  myservo1.attach(2);  
  myservo2.attach(3);
  myservo3.attach(4);
  myservo4.attach(5);
  myservo5.attach(6);
  myservo6.attach(7);
  myservo7.attach(8);
  myservo8.attach(9); 
  
  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);
  pinMode(CH3, INPUT);
  pinMode(CH4, INPUT);
  pinMode(CH5, INPUT);
  pinMode(CH6, INPUT);

  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
 Serial.begin(9600);
 
}

void loop() {

 //leds flashing




// put your main code here, to run repeatedly:
digitalWrite(ledPin, HIGH);
delay(50);
digitalWrite(ledPin, LOW);
delay(10);

 // Servos

  long CH1_PWM = GetPWM(CH1);
  long CH2_PWM = GetPWM(CH2);
  long CH3_PWM = GetPWM(CH3);
  long CH4_PWM = GetPWM(CH4);
  long CH5_PWM = GetPWM(CH5); // pot - Flaps, Hatch
  long CH6_PWM = GetPWM(CH6); //switch C



if(CH4_PWM_new > CH4_PWM + 10 || CH4_PWM_new < CH4_PWM - 10){
CH4_PWM_new = CH4_PWM;
} else{
CH4_PWM_new = CH4_PWM_new;
}

if(CH1_PWM_new > CH1_PWM + 25 || CH1_PWM_new < CH1_PWM - 25){
CH1_PWM_new = CH1_PWM;
} else{
CH1_PWM_new = CH1_PWM_new;
}

 //Serial.println("CH2"+String(CH2_PWM));

  // Roll - Ailerons
  val2 = map(CH1_PWM_new, 499, 1005, 15, 110);     // scale it to use it with the servo (value between 0 and )
  val2_1 =map(CH1_PWM_new, 499, 1005, 100, 50);
  // Pitch - Elevetor
  val4 = map(CH2_PWM, 499, 1005, 60, 95); 
    
  //Yaw - Rudder
  val8 = map(CH4_PWM_new, 499, 1005, 0, 60); 

  if (CH5_PWM < 510){
    //Serial.print("Hatch Open:");
    myservo7.write(90);                  // sets the servo position 90
    myservo8.write(90);                  // sets the servo position 90
  
  }else{
    //Serial.print("Hatch Close:");
    myservo7.write(0);                  // sets the servo position 0
    myservo8.write(0);                  // sets the servo position 0
  }
// Ailerons
  myservo1.write(val2); 
  Serial.println(val2);                 // sets the servo position according to the scaled value
  myservo4.write(val2_1);                  // sets the servo position according to the scaled value 
//Flaps  
if(CH5_PWM < 700){
  myservo2.write(95);                  // sets the servo position according to the scaled value
  myservo3.write(60); 
}else if (CH5_PWM > 700 && CH5_PWM <850){
  myservo2.write(70);                  // sets the servo position according to the scaled value
  myservo3.write(70); 
}else if(CH5_PWM > 850){
  myservo2.write(60);                  // sets the servo position according to the scaled value
  myservo3.write(95); 
} 
//Elevator
  myservo5.write(val4);                  // sets the servo position according to the scaled value
//Rudder
  myservo6.write(val8);                  // sets the servo position according to the scaled value
                            // waits for the servo to get there
}

long GetPWM(byte pin)
{
  unsigned long highTime = pulseIn(pin, HIGH, 50000UL);  // 50 millisecond timeout
  unsigned long lowTime = pulseIn(pin, LOW, 50000UL);  // 50 millisecond timeout

  // pulseIn() returns zero on timeout
  if (highTime == 0 || lowTime == 0)
    return digitalRead(pin) ? 100 : 0;  // HIGH == 100%,  LOW = 0%

  return (10000 * highTime) / (highTime + lowTime);  // highTime as percentage of total cycle time
}