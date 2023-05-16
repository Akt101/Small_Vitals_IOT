//#define LONEG 8 //Defining pin for LO- pin
//#define LOPOS 30 //Defining pin for LO+ pin
#define OUT 29 //Defining pin for OUTPUT pin
#define MUX 30

void setup() {
// initialize the serial communication:
Serial.begin(9600);
//pinMode(LONEG, INPUT); // Setup for leads off detection LO +
//pinMode(LOPOS, INPUT);// Setup for leads off detection LO -
pinMode(OUT, INPUT);
pinMode(MUX, OUTPUT);
digitalWrite(MUX,LOW);
}

void loop() {
Serial.println(analogRead(OUT));
}
