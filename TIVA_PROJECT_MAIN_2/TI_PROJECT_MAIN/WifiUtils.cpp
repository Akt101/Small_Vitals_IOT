
#ifndef __CC3200R1M1RGC__
// Do not include SPI for CC3200 LaunchPad
#include <SPI.h>
#endif
#include <WiFi.h>

#include "WifiUtils.h"
#include <energia.h>

#include "aJSON.h"

void WifiUtils::testingCode()
{
  Serial.println("hellow");
  return;
}

bool WifiUtils::initializeWifi(char *ssidd, char *passphrase)
{
  int status = WL_IDLE_STATUS;

  pinMode(GREEN_LED, OUTPUT); //Green when connected to WiFi
  pinMode(RED_LED, OUTPUT);   // Red when not connected and searching

  // attempt to connect to Wifi network:
  Serial.print("Attempting to connect to Network named: ");
  // print the network name (SSID);
  Serial.println(ssidd);
  // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
  WiFi.begin(ssidd, passphrase);
  while (WiFi.status() != WL_CONNECTED)
  {
    // print dots while we wait to connect
    digitalWrite(RED_LED, HIGH);
    Serial.print(".");
    Serial.print("Not Connected Now!!");
    delay(300);
    digitalWrite(RED_LED, LOW);
    delay(100);
  }

  digitalWrite(GREEN_LED, HIGH);
  delay(300);
  digitalWrite(GREEN_LED, LOW);

  Serial.println("\nYou're connected to the network");
  Serial.println("Waiting for an ip address");

  while (WiFi.localIP() == INADDR_NONE)
  {
    // print dots while we wait for an ip addresss

    Serial.print(".");
    delay(300);
  }

  Serial.println("\nIP Address obtained");

  // you're connected now, so print out the status
  printWifiStatus();
  return true;
}

void WifiUtils::poolWifiStatus()
{

  while (WiFi.status() != WL_CONNECTED)
  {
    // print dots while we wait to connect
    digitalWrite(RED_LED, HIGH);
    Serial.print(".");
    Serial.print("Not Connected Now!!");
    delay(300);
    digitalWrite(RED_LED, LOW);
    delay(100);
  }
}

int WifiUtils::getConfigObject()
{

  //writing a get request code

  WiFiClient client;

  char server[] = "13.235.68.160";
  String response;
  int threshold;
  if (client.connect(server, 4000))
  {
    Serial.println("connected to server");
    client.println("GET /getThreshold HTTP/1.1");
    client.println("Host:13.235.68.160:4000");
    client.println("User-Agent: TivaCC3200/1.1");
    client.println();
    client.println();
  }

  if (client.connected())
  {

    response = client.readStringUntil('>');
    //Serial.println(response);
  }
  response = response.substring(135, 150);
  threshold = response.toInt();

    Serial.println(response);

  if (client.connected())
  {
    Serial.println("Request One Completed");
    client.stop();
  }

  return threshold;

  
}

bool WifiUtils::postSensorsData(uint16_t finalBPM, int bodyTemp, float roomTemp, float roomHumidity)
{

  String postData;
  String postVariable = "temp=";

  pinMode(BLUE_LED, OUTPUT); //Blue when posting to server

  WiFiClient client;

  char server[] = "13.235.68.160";
  String response;

  Serial.println("posting sensor data to server");
  aJsonObject *root = aJson.createObject();
  if (root != NULL)
  {
    Serial.print("Blank Object Created");
  }
  else
  {
    Serial.print("Object Creation Failed");
  }

  aJson.addItemToObject(root, "finalBPM", aJson.createItem(finalBPM));
  aJson.addItemToObject(root, "bodyTemp", aJson.createItem(bodyTemp));
  aJson.addItemToObject(root, "roomTemp", aJson.createItem(roomTemp));
  aJson.addItemToObject(root, "roomHumidity", aJson.createItem(roomHumidity));

  char *string = aJson.print(root);
  if (string != NULL)
  {
//    Serial.println(string);
    postData += string;
  }
  else
  {
    Serial.print("Output String Error");
  }

  if (client.connect(server, 4000))
  {
    
    Serial.println("Posting data Now..");
    digitalWrite(BLUE_LED, HIGH);
    delay(100);
    client.println("POST /sensorData HTTP/1.1");
    client.println("Host: 13.235.68.160:4000");
    client.println("Content-Type: application/json");
    client.print("Content-Length: ");
    client.println(postData.length());
    client.println();
    client.print(postData);
     digitalWrite(BLUE_LED, LOW);
  }

  if (client.connected())
  {
    Serial.println("Request Two Completed");
    client.stop();
  }

  return true;
}

void WifiUtils::printWifiStatus()
{
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:

  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  // print where to go in a browser:
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
}
