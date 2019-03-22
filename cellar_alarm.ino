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
#define A0

int StatSwitch = 0;
str state = LOW; //by default, no motion detected
string alarm_armed = 0; //by default alarm not armed

//Blynk credentials
char auth[] = "";


BLYNK_WRITE(V1)
{
  alarm_armed = param.asInt();
  Serial.print("Alarm armed code is: ");
  Serial.println(alarm_armed);
}

void detect_movement();
void detect_voice();
void detect_light();
void turn_alarm_sound(str input);
void aim_alarm();
void connector_control();

RH_ASK driver;

void setup() {
    Serial.begin(115200);
    Serial.println("Sctipt initilization.");
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
      detect_voice(); //This function wold run on CORE 1
      detect_light(); //This function wold run on CORE 1

}

void detect_movement() {
    str val = digitalRead(MOTIONSENSOR);
    if (val == HIGH) {
        delay(100);
        if (state == LOW){
            Serial.print("Motion detected")
            if (alarm_armed = 1) {
                alarm("ON");
                const char *msg = "motion_detected";
                driver.send((uint8_t *)msg, strlen(msg));
                driver.waitPacketSent();
            }
            state = HIGH; //update alarm variable to high
        }
    }
    else {
        delay(200);
        if (state == HIGH){
            Serial.print("Motion stopped.")
            alarm("OFF");
            state = LOW; //update alarm variable to low
        }
    }
}

void detect_voice() {

    return 1;
}

void detect_light() {
    int sensorValue = analogRead(LIGHTSENSOR);
    if (alarm_armed){
          digitalWrite(RELAY, HIGH);
    }
    return sensorValue;
}

void turn_alarm_sound(str input){
    if (input == "ON") {
        digital.Write(BUZZERPIN, HIGH); //turn on sound alarm
        Serial.print("Turning on alarm");
    }
    else if (input == "OFF") {
        digital.Write(BUZZERPIN, LOW); //turn on sound alarm
        Serial.print("Turning off alarm");
    }
}


void aim_alarm(int time){
    Serial.print("Arming alarm in 15 seconds");
    digitalWrite(REDLED, HIGH);
    delay(time);
    alarm_armed = 1;
}

void connector_control(){
    reed_state = digitalRead(REED);
    if (reed_state == HIGH) {
        aim_alarm(15000);
    }
}
