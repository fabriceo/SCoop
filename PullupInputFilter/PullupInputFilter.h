#ifndef PULLUP_INPUT_FILTER_H
#define PULLUP_INPUT_FILTER_H

#include <Arduino.h>
#include <IOFilter.h>


class PullupInputFilter : public InputFilter
{ public: 
  PullupInputFilter(uint8_t pin, int16_t timeOn);
  PullupInputFilter(uint8_t pin, int16_t timeOn, int16_t timeOff);

  void check_time(int16_t temp);
};

#endif


