///// EXAMPLE ////

#include "TimerDown.h"

#define led_pin LED_BUILTIN
#define ledOn()   digitalWrite(led_pin,HIGH)
#define ledOff()  digitalWrite(led_pin,LOW)

TimerDown countMs;
TimerDown count10sec(10,1000);

void setup() {
  Serial.begin(57600);while(!Serial);
  pinMode(led_pin, OUTPUT);
  ledOff(); 
}

void loop() {
  if (countMs==0) { countMs=500;
     Serial.print("count10sec = ");Serial.println(count10sec);
     if (count10sec==0) { ledOn();
        Serial.println("press any key to reload count10sec with a value (enter=13)");
        if (Serial.available()) {
           char cc=Serial.read(); 
           count10sec = (int)cc;  
           ledOff();
           }
        }
     }
     else
        if (count10sec) 
         if (Serial.available()) {
         char cc=Serial.read(); 
         if (count10sec.paused()) { Serial.println("counter resumed"); count10sec.resume(); }
         else { Serial.println("counter paused"); count10sec.pause(); }
         }
        
}
