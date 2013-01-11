#ifndef TIMERUP_H
#define TIMERUP_H

/***************************************************************************/
/* SCOOP LIBRARY COMPONENT / AUTHOR FABRICE OUDERT / GNU GPL V3            */
/* https://code.google.com/p/arduino-scoop-cooperative-scheduler-arm-avr/  */
/* ENJOY IT AND USE IT AT YOUR OWN RISK  :)                                */
/* VERSION DATE JANUARY 10 / 2013                                          */
/***************************************************************************/
#include <Arduino.h>
/**** TYPICAL USAGE ****/
// #include"TimerUp.h"
// TimerUp countBillionMs;
// TimerUp countMillionSec(-1,1000);   // -1 means maximum value (1 million seconds)
// TimerUp count60Seconds(60,1000);    // count from 0 to 60 every second
// TimerUp countSecondsTenth(10,100);  // count from 0 to 10, every 1/10sec
// ... if (countMillionSec>=1000) countBillionMs.reset();
// countMillionSec=2000; countBillionMs.set(2000000);
// if (count60Seconds.rollOver()) { countHours++;}
// count.pause(); if (count.paused()) count.resume();
/***********************/

// **** PRE PROCESSING CAPABILITIES *** //
// change this parameter to change the prefix of the classname for this library. e.g. you might prefer "TimeCounter" ?
#define _TimerUpClassName TimerUp

//just change this parameter to force the library to use "int" instead of "long" for time parameters in public methods. 
#define _TimerUpInt       long     // with "int", time max will be 30seconds then but most computation remains in 32bits due to time base handling

// just change this parametrer to false to force the library to NOT include code for time base handling. default time base will be millisecond.
#define _TimerUpUseTimeBase true    

// this macro is used to provide the possibility to overload the prefix name of the constants with the class name define in the macro call below
#define _TimerUpSetConst(name) \
const long name##BillionMs  = 1000000000L; \
const long name##MillionSec = 1000000L;    \
const long name##OneWeekMs  = 604800000L;  \
const long name##OneWeekSec = 604800L;     \
const long name##30Seconds  = (int)30000;
_TimerUpSetConst(TimerUp)   // change this parameter to change the prefix of the constant for this library. e.g. you might prefer "TimeCounter" ?


class _TimerUpClassName
{public:

  _TimerUpClassName (); 

  _TimerUpClassName (_TimerUpInt timeMax); 

#if _TimerUpUseTimeBase == true
  _TimerUpClassName (_TimerUpInt timeMax, int base);
#endif

  void setRollOver(_TimerUpInt timeMax);      // redefine time rollover value. this also reset the timer and the "paused" falg
  
  bool rollOver();                            // return true each time the timer is rolling over
  
  void reset();                                // reset the timer value to 0
  
  void set(long value);

  _TimerUpInt get();                           // return the value of the timer and verify potential rollover
   
  operator _TimerUpInt()                      // overload standard operator
  { return get(); }
  
 _TimerUpClassName& operator=(const _TimerUpInt rightArg)  // overload assignement operator
  { set(rightArg); return *this; }
  
 void pause();                                 // put the timer in pause
 
 void resume();                                // resume the timer to its "paused" value and continue counting
 
 bool paused(); 

  void init(long timeMax);
  
#if _TimerUpUseTimeBase  == true
  void init(_TimerUpInt timeMax, int base); 
#endif

private:
  
  bool check(long temp);                       // check if the timer has rolledover since last call. then set the overflow flag
  
#if _TimerUpUseTimeBase == true
  long timeBase;
#endif
  long time;
  long timeRollOver;
  bool overflow;
  bool inPause;
};

#endif

