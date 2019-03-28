/*
Author - (c) Jan Wieczorek : 21/03/3019
Subject - Cellar alarm - transmitter
Description - This is project for cellar alarm controlled by bluetooth.
    User can disarm
*/

//include libraries
#include <ESP8266WiFi.h>
#include <RH_ASK.h> //433Mhz transmition module library
#include <SPI.h> // neded to compile

// Declare and define variables
#define BUZZERPIN D1 // output buzzer pin
#define REED D2 // input reed pin
#define REDLED D3 // output red led pin`
#define GREENLED D4 // output green led pin
#define MOTIONSENSOR D5 // input pin for motion sensor
#define SOUNDSENSOR D6 //input pin for sound sensor
#define LIGHTSENSOR D7 //input pin for light sensor
#define RELAY D8 //output for 230V realy
#define 433TRANS D9 //output pin for 433Mhz transmitter
#define A0


/*
// SPI flash integrated
GPIO 6 (SCK/CLK)
GPIO 7 (SDO/SD0)
GPIO 8 (SDI/SD1)
GPIO 9 (SHD/SD2)
GPIO 10 (SWP/SD3)
GPIO 11 (CSC/CMD)

// Input only pins
#define 34
#define 35
#define 36
#define 37
#define 38
#define 39
// Capative touch pins

*/

int StatSwitch = 0;
int motion_detected = 0; //by default, no motion detected
int alarm_armed = 0; //by default alarm not armed

//Blynk credentials
char auth[] = "";


BLYNK_WRITE(V1)
{
  alarm_armed = param.asInt();
  Serial.print("Alarm armed code is: ");
  Serial.print(alarm_armed);
}

void detect_movement();
void detect_sound();
void detect_light();
void turn_alarm_sound(String input);
void aim_alarm();
void connector_control();

RH_ASK driver;

void setup() {
    Serial.begin(115200);
    Serial.println("Sctipt initialization.");
    if (!driver.init())
        Serial.println("RF Driver init failed");
    pinMode(BUZZERPIN, OUTPUT);
    pinMode(REED, INPUT);
    pinMode(REDLED, OUTPUT);
    pinMode(GREENLED, OUTPUT);
    pinMode(MOTIONSENSOR, INPUT);
    pinMode(SOUNDSENSOR, INPUT);
    pinMode(LIGHTSENSOR, INPUT);
}

void loop() {
      Blynk.run();
      detect_movement(); //This function wold run on CORE 1
      connector_control(); //this fuction would run on CORE 2
      detect_sound(); //This function wold run on CORE 1
      detect_light(); //This function wold run on CORE 1

}

void detect_movement() {
    String val = digitalRead(MOTIONSENSOR);
    if (val == HIGH) {
        delay(100);
        if (motion_detected == LOW) {
            Serial.print("Motion detected");
            if (alarm_armed = 1) {
                aim_alarm("ON");
                const char *msg = "motion_detected";
                driver.send((uint8_t *)msg, strlen(msg));
                driver.waitPacketSent();
            }
            motion_detected = 1; //update alarm state to ON - 1
        }
    }
    else {
        delay(200);
        if (motion_detected == 1) {
            Serial.print("Motion stopped.");
            aim_alarm("OFF");
            motion_detected = 0; //update motion detected to OFF - 0;
        }
    }
}

void detect_sound() {
    int voice =  ; //read voice level from Sound Sensor
    if (voice > 300 && alarm_armed == 1) {
        Serial.print("Sound detected")
        const char *msg = "sound_detected";
        driver.send((uint8_t *)msg, strlen(msg));
        driver.waitPacketSent();
        Serial.print("Sent \"sound_detected\" message to reciever.");
    }
    return 1;
}

void detect_light() {
    int sensorValue = analogRead(LIGHTSENSOR);
    if (alarm_armed == 1) {
          digitalWrite(RELAY, HIGH);
          const char *msg = "light_detected";
          driver.send((uint8_t *)msg, strlen(msg));
          driver.waitPacketSent();
          Serial.print("Sent \"light_detected\" message to reciever.");
    }
    return sensorValue;
}

void turn_alarm_sound(String input) {
    if (input == "ON") {
        digital.Write(BUZZERPIN, HIGH); //turn on sound alarm
        Serial.print("Turning on alarm");
    }
    else if (input == "OFF") {
        digital.Write(BUZZERPIN, LOW); //turn on sound alarm
        Serial.print("Turning off alarm");
    }
}


void aim_alarm(int time) {
    Serial.print("Arming alarm in" + String(time) + "seconds");
    for (i=1, i++, i=time) {
        digitalWrite(REDLED, HIGH);
        delay(495);
        digitalWrite(REDLED, LOW);
        delay(495);
    }
    digitalWrite(REDLED, HIGH);
    alarm_armed = 1;
}

void connector_control() {
    reed_state = digitalRead(REED);
    if (reed_state == HIGH) {
        aim_alarm(15000);
    }
}
