#define LONEG 11 //Defining pin for LO- pin
#define LOPOS 12 //Defining pin for LO+ pin
#define OUT 29 //Defining pin for OUTPUT pin
#define ARRAYLEN 10
#define MUX 30

#include "AD8232_ECG2BPM.h"

uint32_t beat_old,beat_new = 0;
uint16_t _Threshold = 2380;
unsigned long beatmillis[ARRAYLEN];

//uint16_t calculateBPM ();
//void initializing();
 
/*void setup() {
// initialize the serial communication:
Serial.begin(9600);
pinMode(LONEG, INPUT); // Setup for leads off detection LO +
pinMode(LOPOS, INPUT); // Setup for leads off detection LO -
pinMode(OUT, INPUT);
}

void loop() {
uint16_t BPM = 0;

//Serial.println(analogRead(OUT));
initializing();
//Serial.println("Initializing Ended");
for(int i = 0; i < ARRAYLEN; i++)
  Serial.println(beatmillis[i]);    
BPM = calculateBPM();
Serial.print("BPM = ");
Serial.println(BPM);
}*/


uint16_t BPMACTION()
{ 
  unsigned long previousmillis = 0;
  unsigned long currentmillis = 0;
  const int interval = 8000;
  short BPMflag = true;
  pinMode(MUX, OUTPUT);
  digitalWrite(MUX,LOW);
//  delay(8000);//for mux transition
  while(BPMflag == true){
    currentmillis = millis();
    if(currentmillis - previousmillis > interval){
      uint16_t BPM = 0;
  
      pinMode(LONEG, INPUT); // Setup for leads off detection LO +
      pinMode(LOPOS, INPUT); // Setup for leads off detection LO -
      pinMode(OUT, INPUT);
//      Serial.println("Entering Initialization");    
      initializing();
//      Serial.println("Ended Initialization");    
//      for(int i = 0; i < ARRAYLEN; i++)
//      Serial.println(beatmillis[i]);   
      calculateBPM(&BPM);
      BPMflag = false;
      previousmillis = currentmillis;
      return BPM;
      }
    }
  }

  
void initializing(){ 
  unsigned long _time1 = 10000;
  unsigned long previousmillis = 0;
  unsigned long currentmillis = 0;
  const short interval = 600;//To bypass the dichrotic noise
  short firstbeat = true; 
  uint16_t _i = 0;
    
  _time1 += millis();
//  Serial.println("Before While");  
  while(_i<ARRAYLEN){
    currentmillis = millis();     
//    Serial.println("Going Inside While");
//    Serial.println(analogRead(OUT));
    
    if(!(digitalRead(LONEG))&&(!digitalRead(LOPOS))&&(analogRead(OUT) > _Threshold)&&(firstbeat)){
//      Serial.println("<<<<<<<<<Beat One>>>>>>>>>");
      beatmillis[_i]= millis();
      _i++;
      firstbeat = false;
      previousmillis = currentmillis;
      }

    if(!(digitalRead(LONEG))&&(!digitalRead(LOPOS))&&(analogRead(OUT) > _Threshold)&&(!firstbeat)){
      if((currentmillis - previousmillis) > interval){
//        Serial.println("<<<<<<<<<Beat Later>>>>>>>>>");
        beatmillis[_i]= millis();
        _i++;
        previousmillis = currentmillis;
        }
      }        
    } 
    return;    
  }

void calculateBPM (uint16_t *addBPM) 
{ 
  unsigned long tempBPM, _j = 0;
  uint16_t result = 0;
//  unsigned long previousmillis = 0;
//  unsigned long currentmillis = 0;
//  const short interval = 10;//To bypass the dichrotic noise
//  short BPMflag = true;
  while(_j < (ARRAYLEN - 1)){  
    tempBPM += (beatmillis[_j + 1] - beatmillis[_j]);
  _j++;
    }
//  Serial.println(tempBPM);  
  result = 60000/(tempBPM/ARRAYLEN - 1);  
//  Serial.print("the result calculated is"); 
//  Serial.println(result);
//  delay(10);
//   while(BPMflag == true){
//    currentmillis = millis();
//    if(currentmillis - previousmillis > interval){
      delay(10);
      *addBPM = result;
//      BPMflag = false;
//      previousmillis = currentmillis;
//      }
//    }
//  return result;
  return; 
  }
