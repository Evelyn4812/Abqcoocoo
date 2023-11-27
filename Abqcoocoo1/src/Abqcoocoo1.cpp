/*
 * Project Abqcoocoo1
 * Author: Evelyn Rosenberg
 * Date: Oct. 26, 2021
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

//Include Particle Device OS APIs
#include <Particle.h>
#include <Stepper.h>
#include "Grove_4Digit_Display.h"
const int GREENLED = D17;
const int REDLED = D10;
const int DELAYTIME = 1000;
const int PHOTOPIN = A2;
const int SPR = 2048; // 28BY}--48 2048 steps per revolution;
const int MOTORSPEED = 10;
const int RELAYPIN = D18;
const int MAGNETSENSOR = D6;
// IN1, IN3, IN2, IN4
bool magnitized;
Stepper myStepperslide(SPR, D0, D1, D16, D15);
Stepper myStepperdoor(SPR, D2, D4, D3, D5);
void doorClosed();
/* Pin Connections
IN1 on Stepperslide goes to D6
IN2 on Stepperslide goes to D16
IN3 on Stepperslide goes to D19
IN4 on Stepperslide goes to D15
"_" on Stepperslide  goes to GND
"+" on Stepperslide goes to VUSB (this needs 5V)
*/

bool doorOpen;
int ledValue, photoValue;
float volts;
float intoVolts(int inputValue);
void displayTime();
const int CLK = D8;
const int DIO = D9;

TM1637 tm1637(CLK,DIO);

SYSTEM_MODE(AUTOMATIC);

// Run the application and system concurrently in separate threads
SYSTEM_THREAD(ENABLED);

SerialLogHandler logHandler(LOG_LEVEL_INFO);

void setup()
{
  myStepperslide.setSpeed(MOTORSPEED);
  myStepperdoor.setSpeed(MOTORSPEED);
  Serial.begin(9600);
  pinMode(REDLED, OUTPUT);
  pinMode(GREENLED, OUTPUT);
  pinMode(PHOTOPIN, INPUT);
  pinMode(RELAYPIN, OUTPUT);
  pinMode (MAGNETSENSOR, INPUT);
  doorClosed();



  Time.zone(-7);
  Particle.syncTime();
  tm1637.init(); // Initialize the 4 digit display
  tm1637.set(BRIGHT_TYPICAL);//BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
  tm1637.point(POINT_ON);// Show colon
}
void loop()
{
  displayTime();
  digitalWrite(GREENLED, LOW);
  digitalWrite(REDLED, LOW);
  delay(2);
  photoValue = analogRead(PHOTOPIN);
  if (photoValue > 5)
  {
    digitalWrite(GREENLED, HIGH);
    digitalWrite(REDLED, HIGH);
  }
  else
  {

    digitalWrite(GREENLED, LOW);
    digitalWrite(REDLED, LOW);
  }
  Serial.printf("%i,%i\n", photoValue, ledValue);
delay (500);
  myStepperdoor.step(10250);
 delay (5000);
  myStepperslide.step(-1900);
  delay (5000);
  myStepperslide.step(1900);
 delay(3000);
doorClosed(); 
magnitized = digitalRead(MAGNETSENSOR);
Serial.printf("magnetized %i\n",magnitized);


 }
 void doorClosed(){
  while (digitalRead(MAGNETSENSOR)==1){
    myStepperdoor.step(-50);
  }
   myStepperdoor.step(-200);
  delay (8000);
  
} 


// displays the time from Particle on a 4-Digit segment display TM1637
void displayTime(){
  int hour, minute;
  hour = Time.hourFormat12();
  minute = Time.minute();
  tm1637.display(0,hour%1);
  tm1637.display(1,hour%10);
  tm1637.display(2,minute/10);
  tm1637.display(3,minute%10);
 
}

