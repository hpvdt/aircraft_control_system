/*
  Arduino Starter Kit example
  Project 5 - Servo Mood Indicator

  This sketch is written to accompany Project 5 in the Arduino Starter Kit

  Parts required:
  - servo motor
  - 10 kilohm potentiometer
  - two 100 uF electrolytic capacitors

  created 13 Sep 2012
  by Scott Fitzgerald

  https://store.arduino.cc/genuino-starter-kit

  This example code is part of the public domain.
*/

// include the Servo library
#include <Servo.h>

Servo myServo;  // create a servo object
Servo servoTwo;

float const potPin = A0;  // analog pin used to connect the potentiometer
float potVal;             // variable to read the value from the analog pin
float angle [3] = {0};              // variable to hold the angle for the servo motor
float input [3] = {0};
float matrix [1][3] = {{179, 0, 0}};
float percent = 0;

void setup() {
  myServo.attach(9);   // attaches the servo on pin 9 to the servo object
  servoTwo.attach((7));
  Serial.begin(9600);  // open a serial connection to your computer
}

void loop() {
  potVal = analogRead(potPin);  // read the value of the potentiometer
  // print out the value to the Serial Monitor
  Serial.print("potVal: ");
  Serial.print(potVal);
  
  percent = potVal / 1023.0 ;

 for (int i = 0; i < 1; i++) {
   int sum = 0;
   for (int j = 0; j < 3; j ++) {
     sum += matrix[i][j] * percent;
   }
   angle[i]= sum;
 }



  // scale the numbers from the pot
  //angle2 = map(potVal, 0, 1023, 0, 179);

  // print out the angle for the servo motor


  Serial.print("angle 0: ");
  Serial.println(angle[0]);
  
  

  // set the servo position
  myServo.write(angle[0]);
///

  // wait for the servo to get there
  delay(15);
}
