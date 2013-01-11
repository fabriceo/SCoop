///// TEMPLATE ////

#include "TimerUp.h"

#define led_pin LED_BUILTIN // pin 6 for Teensy++20
#define ledOn()   digitalWrite(led_pin,HIGH)
#define ledOff()  digitalWrite(led_pin,LOW)

TimerUp countBillionMs;
TimerUp countMillionSec(-1,1000);
TimerUp countOneWeek(TimerUpOneWeekSec,1000); // (long)(7*24*3600)
TimerUp pulseOneSecond(1,1000);

void setup(){
Serial.begin(57600); while (!Serial); pinMode(led_pin, OUTPUT);

}

void loop(){

  if (pulseOneSecond.rollOver()) {
     if (countBillionMs.paused()) { ledOn(); countBillionMs.resume();}
     else { ledOff(); countBillionMs.pause(); } }
  
  if (!countBillionMs.paused()) {
     Serial.println(countBillionMs); delay (100); }

}
