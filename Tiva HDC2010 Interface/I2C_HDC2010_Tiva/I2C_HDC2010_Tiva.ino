// Wire Master Reader
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Reads data from an I2C/TWI slave device
// Refer to the "Wire Slave Sender" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>

void setup()
{
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(115200);  // start serial for output
  
  pinMode(40,OUTPUT);//Green Light On
  digitalWrite(40,HIGH);
  
  //pinMode(23,INPUT);//HDC2010 Read DRDY

  //pinMode(6,OUTPUT);
  //digitalWrite(6,HIGH);
}

void loop()
{
  Wire.requestFrom(1000000, 2);    // request 6 bytes from slave device #3

  while(Wire.available())    // slave may send less than requested
  { 
    //int c = Wire.read(); // receive a byte as character
    Serial.println(Wire.read());         // print the character
  }

  delay(500);
}
