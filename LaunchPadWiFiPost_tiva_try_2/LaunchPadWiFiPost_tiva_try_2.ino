#include <aJSON.h>
#include "SPI.h"
#include "WiFi.h"

#define ENERGIA_PLATFORM
#include "M2XStreamClient.h"

char ssid[] = "LaunchPAD"; //  your network SSID (name)
char pass[] = "gg@gg123";    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;

char deviceId[] = "<device id>"; // Device you want to push to
char streamName[] = "<stream name>"; // Stream you want to push to
char m2xKey[] = "<M2X access key>"; // Your M2X access key


const int temperaturePin = A0;

WiFiClient client;
M2XStreamClient m2xClient(&client, m2xKey);

void printFloat(float value, int places);

float temp;

void setup() {

    Serial.begin(9600);

    // attempt to connect to Wifi network:
    Serial.print("Attempting to connect to Network named: ");
    // print the network name (SSID);
    Serial.println(ssid); 
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    WiFi.begin(ssid, pass);
    while ( WiFi.status() != WL_CONNECTED) {
      // print dots while we wait to connect
      Serial.print(".");
      delay(300);
    }
  
    Serial.println("\nYou're connected to the network");
    Serial.println("Waiting for an ip address");
  
    while (WiFi.localIP() == INADDR_NONE) {
      // print dots while we wait for an ip addresss
      Serial.print(".");
      delay(300);
    }

    Serial.println("\nIP Address obtained");
  
    // you're connected now, so print out the status  
    printWifiStatus();
}

void loop() {

  float voltage, degreesC, degreesF;

  voltage = getVoltage(temperaturePin);
  degreesC = (voltage - 0.5) * 100.0;
  degreesF = degreesC * (9.0 / 5.0) + 32.0;

  Serial.print("voltage: ");
  Serial.print(voltage);
  Serial.print("  deg C: ");
  Serial.print(degreesC);
  Serial.print("  deg F: ");
  Serial.println(degreesF);

  int response = m2xClient.updateStreamValue(deviceId, streamName, degreesC);
  Serial.print("M2X client response code: ");
  Serial.println(response);

  if (response == -1)
    while (1)
      ;

  delay(5000);
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}

float getVoltage(int pin) { 
  return (analogRead(pin) * 0.004882814 * 0.5); // normalize the voltage from LM35
}
