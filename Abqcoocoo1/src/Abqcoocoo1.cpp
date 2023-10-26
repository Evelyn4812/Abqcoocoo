/*
 * Project Abqcoocoo1
 * Author: Evelyn Rosenberg
 * Date: Oct. 26, 2021
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

// Include Particle Device OS APIs
#include "Particle.h"
const int GREENLED = A5;
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
  photoValue=analogRead(PHOTOPIN);
  ledValue = photoValue / 18;
  analogWrite(GREENLED,ledValue);
  analogWrite(REDLED,ledValue);
  if(photoValue > 100){
    doorOpen = true;
  Serial.printf("%i,%i\n",photoValue,ledValue);

  }
}

  // The core of your code will likely live here.

  // Example: Publish event to cloud every 10 seconds. Uncomment the next 3 lines to try it!
  // Log.info("Sending Hello World to the cloud!");
  // Particle.publish("Hello world!");
  // delay( 10 * 1000 ); // milliseconds and blocking - see docs for more info!

