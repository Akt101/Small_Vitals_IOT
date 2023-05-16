#include "LMT90_Temperature.h"

#define MUX 30


int sensorPin = 29;
int sensorValue = 100;
const double resolution =  0.0008056640625;

/*void setup() {
  Serial.begin(9600);
  pinMode(sensorPin,INPUT);
}

void loop() {
  sensorValue = analogRead(sensorPin);
  double calcVoltage = sensorValue*resolution;
  int calcTemp = (calcVoltage - 0.5)/0.01;
}*/

int LMTACTION(){
  // Serial.begin(9600);
  pinMode(MUX, OUTPUT);
  digitalWrite(MUX,HIGH);
  delay (8000);//for mux transition
//  pinMode(sensorPin,INPUT);

  sensorValue = analogRead(sensorPin);
  double calcVoltage = sensorValue*resolution;
  int calcTemp = (calcVoltage - 0.5)/0.01;
  //Serial.println(sensorValue);
  
  return calcTemp;
  }
