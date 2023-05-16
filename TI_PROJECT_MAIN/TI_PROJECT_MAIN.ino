#include "Main.h"

#define MUX 30  
//uint16_t finalBPM = 0;
  
void setup() {
  Serial.begin(9600);
  Wire.begin();
}

void loop() {

   Serial.print("BodyTemp = ");
  Serial.println(LMTACTION());
  
  //  finalBPM=  BPMACTION();
  Serial.print("BPM =");
  Serial.println(BPMACTION());
  
//  Serial.print("RoomTemp = ");
//  Serial.println(TEMPACTION());
//
//  Serial.print("RoomHum = ");
//  Serial.println(HUMACTION());
  

//  HWREG(NVIC_APINT) = NVIC_APINT_VECTKEY | NVIC_APINT_SYSRESETREQ;
}
