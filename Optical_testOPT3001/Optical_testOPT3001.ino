#include "Wire.h"

#define slaveAdr 0x44

#define RESULT_REG 0x00
#define CONFIG_REG 0x01
#define LOWLIMIT_REG 0x02
#define HIGHLIMIT_REG 0x03
#define MANUFACTUREID_REG 0x7E
#define DEVICEID_REG 0x7F

#define DEFAULT_CONFIG 0b1100110000010000 // 800ms
#define DEFAULT_CONFIG_100 0b1100010000010000 // 100ms

uint16_t writeByte = DEFAULT_CONFIG_100;

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
Wire.begin();

    /* Begin Tranmission at address of device on bus */
  Wire.beginTransmission(slaveAdr);
  /* Send Pointer Register Byte */

  Wire.write(CONFIG_REG);

  /* Read*/
  Wire.write((unsigned char)(writeByte>>8));
  Wire.write((unsigned char)(writeByte&0x00FF));

  /* Sends Stop */
  Wire.endTransmission();

}


void loop() {
  // put your main code here, to run repeatedly: 
  uint8_t lsb;
  uint8_t msb;
  uint16_t result;

  /* Begin Transmission at address of device on bus */
  Wire.beginTransmission(slaveAdr);

  /* Send Pointer to register you want to read */
  Wire.write(0x00);

  /* Sends Stop */
  Wire.endTransmission(true);

  /* Requests 2 bytes from Slave */
  Wire.requestFrom(slaveAdr, 2);

  /* Wait Until 2 Bytes are Ready*/
  //while(Wire.available() < 2) {

  /* Read*/
  msb = Wire.read();
  lsb = Wire.read();
  result = (msb << 8) | lsb;
  
  Serial.println(result,BIN);
  delay(500);
}
