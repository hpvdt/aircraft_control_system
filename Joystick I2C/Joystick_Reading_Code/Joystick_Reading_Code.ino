#include <Servo.h>
#include <Wire.h>


Servo myservo;  // create servo object to control a servo
float readings[3];

void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // function that executes whenever data is received from writer
  Serial.begin(115200); //number of bits per second
  myservo.attach(A3);  // attaches the servo on pin 9 to the servo object 
}

void loop() {
  // myservo.write(0);
  // Serial.println(readings[0]);
  myservo.write(convertToServo(readings[2]));                  // sets the servo position according to the scaled value
  delay(100);
}

void receiveEvent() {
  
  String data0 = "";
  String data1 = "";
  String data2 = "";

  int dataWire = 1;
  while( Wire.available()){
    char dataChar = (char) Wire.read();
    if (dataChar != (char) 'c') {
      // Serial.print("Adding ");
      // Serial.println(dataChar);
      if (dataWire == 1) {
        data0 += dataChar;
        // Serial.println("updated data0");

      }
      else if (dataWire == 2) {
        data1 += dataChar;
        // Serial.println("updated data1");

      }
      else { //Data wire = 2
        data2 += dataChar;
        // Serial.println("updated data2");
      }
    }
    else {
      dataWire += 1;
      // Serial.println("increased Wire");
      // Serial.println(data0);
      // Serial.println(data1);

    }
  }


  readings[0] = data0.toFloat();
  readings[1] = data1.toFloat();
  readings[2] = data2.toFloat();
 
}

float convertToServo(float reading) {
  // Serial.println((reading / 100 - 1) * 90  + 90);
  return (reading * 90 + 89);
}
