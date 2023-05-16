int sensorValue = 100;
int sensorPin = 29;
const double resolution = 0.0008056640625;
#define MUX 30

void setup() {
  Serial.begin(9600);
  pinMode(sensorPin,INPUT);
  pinMode(MUX, OUTPUT);
  digitalWrite(MUX,HIGH);
}

void loop() {
  sensorValue = analogRead(sensorPin);
  double calcVoltage = sensorValue*resolution;
  int calcTemp = (calcVoltage - 0.5)/0.01;
  //Serial.println(sensorValue);
  Serial.println(calcTemp);
}
