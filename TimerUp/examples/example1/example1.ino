///// EXAMPLE ////

#include "TimerUp.h"

#define led_pin LED_BUILTIN
#define ledOn()   digitalWrite(led_pin,HIGH)
#define ledOff()  digitalWrite(led_pin,LOW)

int countMinutes=0;
TimerUp T1_countBillionMs;
TimerUp T2_countMillionSec(-1,1000);
TimerUp T3_count60Seconds(60,1000);
TimerUp T4_countTenthSeconds(10,100);
TimerUp everyHalfSecond(500);

void setup(){
Serial.begin(57600); while (!Serial);
pinMode(led_pin, OUTPUT);
}

void loop(){

  if (everyHalfSecond.rollOver()){ Serial.println("");ledOn();
  Serial.print("T1 = ");Serial.print(T1_countBillionMs);Serial.println("ms");
  Serial.print("T2 = ");Serial.print(T2_countMillionSec);Serial.println("s");
  Serial.print("T3 = ");Serial.print(T3_count60Seconds);Serial.print("s ");Serial.print(countMinutes);Serial.println("min");
  Serial.print("T4 = ");Serial.print(T4_countTenthSeconds);Serial.println("/10s");ledOff();
}

if (T3_count60Seconds.rollOver()) countMinutes++; 

if (Serial.available()) {   // press a key (or send a cariage return with the Send button) to pause/resume this timer
  char cc = Serial.read();
  if (T1_countBillionMs.paused()) { T1_countBillionMs.resume(); Serial.println("T1_countBillionMs resumed"); }
  else { T1_countBillionMs.pause(); Serial.println("T1_countBillionMs paused"); } }

}
