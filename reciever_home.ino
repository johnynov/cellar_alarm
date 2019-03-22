/*
Author - (c) Jan Wieczorek : 22/03/3019
Subject - Cellar alarm - home reciever
Description - This is project for IoT cellar alarm reciver located at home.
    This device would operated within the same Blynk project as transmitter (cellar_alarm.ino).
*/

#include <ESP8266WiFi.h>
#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

//Blynk credentials

char auth[] = ""; //Blynk authentiacition token.

RH_ASK driver; //initilization of 433Mhz Driver.

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
      const char msg = (char*)buf;
      Serial.println(msg);
      if (msg == "motion_detected") {
          Blynk.notify("Motion detected in callar while alarm were on.");
      }
      else if (msg == "") {
           Blynk.notify("");
      }
      else if (msg == "") {
           Blynk.notify("");
      }
    }
}
