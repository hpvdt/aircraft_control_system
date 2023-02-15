#include <Servo.h>
#include <Wire.h>


Servo myservo;  // create servo object to control a servo
float readings;

void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // function that executes whenever data is received from writer
  Serial.begin(115200); //number of bits per second
  myservo.attach(A3);  // attaches the servo on pin 9 to the servo object 
}

void loop() {

  myservo.write(readings);                  // sets the servo position according to the scaled value
  delay(100);
}

void receiveEvent() {
  Serial.println("Received ");
  readings = Wire.read();
  Serial.println(readings); //Printing single character 1 byte or ( 8 bits )
}

float convertToServo(float reading) {
  return ((reading / 100 - 1) * 90  + 90);
}