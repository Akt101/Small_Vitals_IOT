#include "Main.h"

uint16_t finalBPM = 0;
int bodyTemp = 0;
float roomTemp = 0.0;
float roomHumidity = 0.0;


int thresh = 0;
WifiUtils wifiUtil;

void setup()
{
  Serial.begin(9600);
  Serial.println("Heyyy");
  //Wire.setModule(1);
  Wire.begin();

  if (wifiUtil.initializeWifi("tivahotspot", "tivahotspot"))
  {
    Serial.println("<<Proceeding to get data from the server>>");
    thresh = wifiUtil.getConfigObject();
    Serial.println(thresh);
    
  }
}

void loop()
{
//  wifiUtil.testingCode();

  wifiUtil.poolWifiStatus();
// 
  roomTemp = TEMPACTION();
  Serial.print("RoomTemp = ");
  Serial.println(roomTemp);
  
//  delay(1000);

  roomHumidity = HUMACTION();
  Serial.print("RoomHum = ");
  Serial.println(roomHumidity);
  
  bodyTemp = LMTACTION();
  Serial.print("BodyTemp = ");
  Serial.println(bodyTemp);

  finalBPM = BPMACTION(thresh);
  Serial.print("BPM =");
  Serial.println(finalBPM);

  wifiUtil.postSensorsData(finalBPM,bodyTemp,roomTemp,roomHumidity);
}
