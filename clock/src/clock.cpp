/* 
 * Project myProject
 * Author: Evelyn
 * Date: October 27,2023
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

// Include Particle Device OS APIs
#include <Particle.h>
#include "RTClibrary.h"
#include "Grove_4Digit_Display.h"


#define CLK 8
#define DIO 9
RTC_DS3231 rtc;
TM1637 display(CLK, DIO);

void setup() {

  Serial.begin(9600);
  delay(3000);

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time");
    rtc.adjust(DateTime(F(__DATE__),F(__TIME__)));
  }
  display.set(BRIGHT_TYPICAL);
  display.clearDisplay();
  }
}
  void loop() {
    DateTime now =rtc.now();
    int displaytime = (now.hour() * 100) + now.minute();
    Serial.println(displaytime);
    display.display(displaytime, 0b11100000);

  }