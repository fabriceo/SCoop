
#include "IOFilter.h"

Output led(LED_BUILTIN);
/* teensy2+ only
Output pin15(15);
Output pin17(17);
Input  pin16(16);
*/
InputFilter IN(1,1000,500); 

uint16_t reg=0x0080;

InputMem  bitIn(&reg,10);
OutputMem bitOut(&reg,10);

void setup()
{ 
Serial.begin(57600); while (!Serial);
// pin17=1; pin15=0; teensy only
};

void loop()
{
  bitOut = IN;
  led = bitIn;
  Serial.print("reg=");Serial.print(reg,HEX);Serial.print(" count=");Serial.println(IN.count());delay(100);
};
