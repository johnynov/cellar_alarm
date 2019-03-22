/*
Author - (c) Jan Wieczorek : 21/03/3019
Subject - Cellar alarm
Description - This is project for cellar alarm controlled by bluetooth.
    User can disarm
*/

//include libraries
#include <ESP8266WiFi.h>



// Declare and define variables
#define BUZZERPIN D1 // output buzzer pin
#define REED D2 // input reed pin
#define REDLED D3 // output red led pin`
#define GREENLED D4 // output green led pin
#define MOTIONSENSOR D5 // input pin for motion sensor
#define SOUNDSENSOR D6 //input pin for sound sensor
#define LIGHTSENSOR D7 //input pin for light sensor
#define A0

int StatSwitch = 0;
str state = LOW; //by default, no motion detected
string alarm_armed = 0; //by default alarm not armed

//Blynk credentials
char auth[] = "e3d7d584f2c04bcaa5fbc7e92ada2f31";


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

void setup() {
    Serial.begin(115200);
    Serial.print("Sctipt initilization.");
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
      detect_movement();
      connector_control();
}

void detect_movement() {
    str val = digitalRead(MOTIONSENSOR);
    if (val == HIGH) {
        delay(100);
        if (state == LOW){
            Serial.print("Motion detected")
            if (alarm_armed = 1;) {
                alarm("ON");
                Blynk.notify("Wykryto ruch w piwnicy przy włączonym alarmie");
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

}

void detect_light() {

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
