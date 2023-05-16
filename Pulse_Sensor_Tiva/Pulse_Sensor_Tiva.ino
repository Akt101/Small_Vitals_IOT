#define LONEG 11 //Defining pin for LO- pin
#define LOPOS 12 //Defining pin for LO+ pin
#define OUT 29 //Defining pin for OUTPUT pin
#define ARRAYLEN 10
#define MUX 30

uint32_t beat_old,beat_new = 0;
uint16_t _Threshold = 2350;
unsigned long beatmillis[ARRAYLEN];

uint16_t calculateBPM ();
void initializing();
 
void setup() {
// initialize the serial communication:
  Serial.begin(9600);
  pinMode(LONEG, INPUT); // Setup for leads off detection LO +
  pinMode(LOPOS, INPUT); // Setup for leads off detection LO -
  pinMode(OUT, INPUT);
  pinMode(MUX, OUTPUT);
  digitalWrite(MUX,LOW);
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
}

void initializing(){ 
  unsigned long _time1 = 10000;
  unsigned long previousmillis = 0;
  unsigned long currentmillis = 0;
  const short interval = 600;//To bypass the dichrotic noise
  short firstbeat = true; 
  uint16_t _i = 0;
    
  _time1 += millis();
  
  while(_i<ARRAYLEN){
    currentmillis = millis();     
//    Serial.println("Going Inside While");
    
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

uint16_t calculateBPM () 
{ unsigned long tempBPM, _j = 0;
  uint16_t result = 0;
  
  while(_j < (ARRAYLEN - 1)){  
    tempBPM += (beatmillis[_j + 1] - beatmillis[_j]);
  _j++;
    }
  //Serial.println(tempBPM);  
  result = 60000/(tempBPM/ARRAYLEN - 1);  
  return result; 
  }
