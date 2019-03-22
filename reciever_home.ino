/*
Author - (c) Jan Wieczorek : 22/03/3019
Subject - Cellar alarm - home reciever
Description - This is project for cellar alarm controlled by bluetooth.
    User can disarm
*/

#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

RH_ASK driver;

void setup()
{
    Serial.begin(115200);	// For debugging purposes.
    if (!driver.init())
         Serial.println("init failed");
}

void loop()
{
    uint8_t buf[12];
    uint8_t buflen = sizeof(buf);
    if (driver.recv(buf, &buflen)) // Non-blocking
    {
      int i;
      // Message with a good checksum received, dump it.
      Serial.print("Message: ");
      Serial.println((char*)buf);
    }
}
