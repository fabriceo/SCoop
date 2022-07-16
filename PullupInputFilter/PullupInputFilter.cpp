
#include "PullupInputFilter.h"

PullupInputFilter::PullupInputFilter(uint8_t pin, int16_t timeOn) : InputFilter(pin, timeOn)
{
  pinMode(pin, INPUT_PULLUP);
  value = last = 1;
}

PullupInputFilter::PullupInputFilter(uint8_t pin, int16_t timeOn, int16_t timeOff) : InputFilter(pin, timeOn, timeOff)
{
  pinMode(pin, INPUT_PULLUP);
  value = last = 1;
}

void PullupInputFilter::check_time(int16_t temp)
{ if (readPin() != value)
     if (value) { // falling edge
        if ((temp - time) > timeOff) { counter++; value=1; } }
     else { // rising edge
        if ((temp - time) > timeOn)  { value=0; } } 
  else { time=temp; }
}

