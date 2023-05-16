#include "HDC2010.h"

float Temp,Hum = 0;

/*void setup() {
  Serial.begin(9600);
  Wire.setModule(1);
  Wire.begin();
  
  Write(HDCADD, CONFIG, 0x50);//Writing to Config Register
  Write(HDCADD, MEASURNMENT_CONFIG, 0x01);//Writing to measurnment config Register
}


void loop() {  
  float Temp,Hum = 0;
    
  Write(HDCADD, 0x0F, 0x01);//Writing to measurnment config Register
  delay(1000);
  Temp = Read(HDCADD, TEMP_LOW, 2);
  Hum =Read(HDCADD, HUM_LOW, 2);
  
                                   
  CalculateRoomParams(&Temp, &Hum);
  Serial.print("Temp(C) =");
  Serial.println(Temp);
  Serial.print("Hum(%RH) =");
  Serial.println(Hum);
}*/


float TEMPACTION(){
  //float Temp,Hum = 0;
  
  // Serial.begin(9600);
  // Wire.setModule(1);
  // Wire.begin();
  
  Write(HDCADD, CONFIG, 0x50);//Writing to Config Register
  Write(HDCADD, MEASURNMENT_CONFIG, 0x01);//Writing to measurnment config Register
  
  //Write(HDCADD, 0x0F, 0x01);//Writing to measurnment config Register
  delay(1000);
  Temp = Read(HDCADD, TEMP_LOW, 2);
                                   
  // Serial.print("Temp(C) =");
  // Serial.println(Temp);
  CalculateTemp();
  return Temp;
  }
  

  float HUMACTION(){
  //float Temp,Hum = 0;
  
  Write(HDCADD, CONFIG, 0x50);//Writing to Config Register
  Write(HDCADD, MEASURNMENT_CONFIG, 0x01);//Writing to measurnment config Register
  
  delay(1000);
  Hum = Read(HDCADD, HUM_LOW, 2);
                                    
  // Serial.print("Hum(%RH) =");
  // Serial.println(Hum);
  CalculateHum();
  return Hum;
  }


void Write(int devaddr, int regaddr, int regvals){
  Wire.beginTransmission(devaddr);//Setting the Configurations Register
  Wire.write(regaddr);//Sending Register Address
  Wire.write(regvals);//Sending Register Values
  Wire.endTransmission();
  return;
  }


float Read(int devaddr, int regaddr, int nob){//Number of regs you want to read from at a time
  uint16_t regval;
  regval = 0;
  int i = 1;
  
  Wire.beginTransmission(devaddr);//Reading the temperature values
  Wire.write(regaddr);//Register address of TempLSB
  Wire.endTransmission(true);

  Wire.requestFrom(devaddr, nob);//Requesting data from device of address devaddr, and number of bytes requested nob

  while(Wire.available())//Check if values are available to be read
  {
    regval = Wire.read();//Pointer on regiser increments automatically
      while(i < nob){
        regval |= Wire.read() << 8;
        i++;  
      }
  }   
  return regval;
}


void CalculateTemp(){
  Temp = ((Temp/pow(2,16)) * 165)-40; 
  return;
  }


void CalculateHum(){
  Hum = (Hum/pow(2,16))* 100; 
  return;
  } 
    
