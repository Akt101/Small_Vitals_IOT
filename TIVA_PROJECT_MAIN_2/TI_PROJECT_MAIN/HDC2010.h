#include <energia.h>
#include <Wire.h>

#define HDCADD 0x40

#define TEMP_LOW 0x00
#define TEMP_HIGH 0x01
#define HUM_LOW 0x02
#define HUM_HIGH 0x03
#define CONFIG 0x0E
#define MEASURNMENT_CONFIG 0x0F

void Write(int devaddr, int regaddr, int regvals);
float Read(int devaddr, int regaddr, int nob);
void CalculateTemp();
void CalculateHum();
float TEMPACTION();
float HUMACTION();
