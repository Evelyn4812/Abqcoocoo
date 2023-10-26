/*
 * Project Abqcoocoo1
 * Author: Evelyn Rosenberg
 * Date: Oct. 26, 2021
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

// Include Particle Device OS APIs
#include "Particle.h"
const int GREENLED = D17;
const int REDLED = D15;
const int DELAYTIME = 1000;
const int PHOTOPIN = A2;
bool doorOpen;
int ledValue, photoValue;
float volts;
float intoVolts(int inputValue);
    
SYSTEM_MODE(SEMI_AUTOMATIC);

// Run the application and system concurrently in separate threads
SYSTEM_THREAD(ENABLED);

SerialLogHandler logHandler(LOG_LEVEL_INFO);

void setup() {
  Serial.begin(9600);
  pinMode(REDLED,OUTPUT);
  pinMode(GREENLED,OUTPUT);
  pinMode(PHOTOPIN,INPUT);
}

void loop() {
  digitalWrite (GREENLED,LOW);
  digitalWrite (REDLED,LOW);
  delay(2);
  photoValue=analogRead(PHOTOPIN);
  if(photoValue>5){
      digitalWrite(GREENLED,HIGH);
      digitalWrite(REDLED,HIGH);
  }
  else{
    digitalWrite (GREENLED,LOW);
    digitalWrite (REDLED,LOW);
  }
  Serial.printf("%i,%i\n",photoValue,ledValue);
  
  }