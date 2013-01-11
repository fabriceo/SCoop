#ifndef TIMERDOWN_H
#define TIMERDOWN_H

/***************************************************************************/
/* SCOOP LIBRARY COMPONENT / AUTHOR FABRICE OUDERT / GNU GPL V3            */
/* https://code.google.com/p/arduino-scoop-cooperative-scheduler-arm-avr/  */
/* ENJOY IT AND USE IT AT YOUR OWN RISK  :)                                */
/* VERSION DATE JANUARY 10 / 2013                                          */
/***************************************************************************/
#include <Arduino.h>
/**** TYPICAL USAGE ****/
// #include"TimerDown.h"
// TimerDown countMs;
// TimerDown count(10,1000) 
/***********************/

// **** PRE PROCESSING CAPABILITIES *** //
// change this parameter to change the prefix of the classname for this library. e.g. you might prefer "TimeCounter" ?
#define _TimerDnClassName TimerDown

//just change this parameter to force the library to use "int" instead of "long" for time parameters in public methods. 
#define _TimerDnInt long     // with "int", time max will be 30seconds then but most computation remains in 32bits due to time base handling

// just change this parametrer to false to force the library to NOT include code for time base handling. default time base will be millisecond.
#define _TimerDnUseTimeBase true    

// this macro is used to provide the possibility to overload the prefix name of the constants with the class name define in the macro call below
#define _TimerDnSetConst(name) \
const long name##BillionMs  = (long)1000000000;    \
const long name##MillionSec = (long)1000000;       \
const long name##OneWeekMs  = (long)(604800000L);  \
const long name##OneWeekSec = (long)(604800L);     \
const long name##30Seconds  = (int)30000;
_TimerDnSetConst(TimerDown)   // change this parameter to change the prefix of the constant for this library. e.g. you might prefer "TimeCounter" ?


// code below is not commented ... suggest to see in timerup to get a better insight :)

class _TimerDnClassName
{public:
  _TimerDnClassName() ;
  
  _TimerDnClassName(_TimerDnInt time); 
  
#if _TimerDnUseTimeBase == true
  _TimerDnClassName(_TimerDnInt time, int base); 
#endif

  void reset();
  
  void set(long value);  // voluntary keep long here
  long get(); 
  
  void pause();
  
  void resume();
  
  bool paused();

  operator _TimerDnInt() 
  { return get(); }
  
  _TimerDnClassName & operator=(const _TimerDnInt rightArg) 
  { set(rightArg); return *this; }
  
  void init(_TimerDnInt value); 
  
#if _TimerDnUseTimeBase == true
  void init(_TimerDnInt value, int base); 
#endif

  private:
#if _TimerDnUseTimeBase == true
  int  timeBase;
#endif  
  long time;
  bool inPause;
};


#endif

