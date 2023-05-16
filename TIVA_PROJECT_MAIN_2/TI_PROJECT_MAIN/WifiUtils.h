

#ifndef __CC3200R1M1RGC__

#include <Print.h>
#include <energia.h>
#include <stdio.h>

// Do not include SPI for CC3200 LaunchPad
#include <SPI.h>
#endif
#include <WiFi.h>

class WifiUtils
{
public:
    bool initializeWifi(char *ssidd, char *passphrase);

    int getConfigObject();
    void poolWifiStatus();
    void testingCode();
    bool postSensorsData(uint16_t finalBPM,int bodyTemp,float roomTemp,float roomHumidity);

private:
    void printWifiStatus();
};
