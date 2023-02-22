#include <Wire.h>

int sensorPin = A0;   // select the input pin for the potentiometer
int sensorPin2 = A1;   // select the input pin for the potentiometer
int sensorPin3 = A2;

int ledPin = 13;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor
const float slope = (0.00571429);
const float yIntercept = 3.1429;
float convertedReading;
const float top = 80; // * 1000s resistance conversions
const float bottom = 13; // * 1000s resistance conversions

void setup() {
  Serial.begin(115200); //number of bits per second
  while (!Serial);
  Wire.begin(); // join i2c bus (address optional for writer)
}

void loop() {

  float reading = analogRead(sensorPin);
  reading = reading*slope-yIntercept;
  reading = constrain(reading, -1, 1);


  float reading2 = analogRead(sensorPin2);
  reading2 = reading2*slope-yIntercept;
  reading2 = constrain(reading2,-1, 1);

  float reading3 = analogRead(sensorPin3);
  reading3 = reading3*(2.0 / 1023.0) - 1;

   

  sendingData(convertResistance(0), convertResistance(1), reading3);


  Serial.print(convertResistance(0));
  Serial.print(",");
  Serial.println(convertResistance(1));

  delay(100);                // waits for the servo to get there
}

void sendingData(float value1, float value2, float value3) {
  Wire.beginTransmission(8);

  char sendValue1[7];
  dtostrf(value1, 7, 6, sendValue1);
  Wire.write(sendValue1);
  Wire.write("c");

  char sendValue2[7];
  dtostrf(value2, 7, 6, sendValue2);
  Wire.write(sendValue2);
  Wire.write("c");

  char sendValue3[7];
  dtostrf(value3, 7, 6, sendValue3);
  Wire.write(sendValue3);

  Wire.endTransmission();  

  
}

float convertResistance(int port) {
  float slope = 0;
  float resistorValue = getResistance(port);
  slope = (2 / (top - bottom)) ;
  return slope * (resistorValue / 1000) + 1 - (slope * top) ;
}

float getResistance(int port) {

  float resistance = 0;
  // Constants trelated to the circuit, set resistor and analog read pin
  const float setResistor[] = {47001.0, 46750.0};
  const int portPin[] = {A0, A1};
  // Start collecting   
  float reading = analogRead(portPin[port]);
  resistance = (1024.0/reading) - 1.0; // Find the relative value of the potentiometer
  resistance = resistance * setResistor[port]; // Find the actual value
  // (Convert resistance to a value between -1 and +1)
  return resistance;
}
