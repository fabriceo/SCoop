
#include "TimerDown.h"

  _TimerDnClassName::_TimerDnClassName() 
#if _TimerDnUseTimeBase == true
  { init(0,1); } 
#else
  { init(0); } 
#endif
  
  _TimerDnClassName::_TimerDnClassName(_TimerDnInt time) 
#if _TimerDnUseTimeBase == true
  { init(time,1); }
#else
  { init(time); }
#endif
  
#if _TimerDnUseTimeBase == true
  _TimerDnClassName::_TimerDnClassName(_TimerDnInt time, int base) 
  { init(time,base); }
#endif

  void _TimerDnClassName::reset() { set(0); }
  
  void _TimerDnClassName::set(long value) { 
#if _TimerDnUseTimeBase == true  
  if (timeBase>1) value *= timeBase;
#endif
  if (inPause) time = value;
  else time=(long)millis() + value; }
  
  long _TimerDnClassName::get() 
  { long temp;
    if (inPause) temp=0;
    else temp = (long)millis(); 
    if ((temp-time)>=0) { time=temp; return 0; } 
    else 
#if _TimerDnUseTimeBase == true  
       if (timeBase>1) return (time-temp+(long)timeBase-1)/timeBase; 
       else return time-temp; }
#else
       return time-temp; }
#endif

void _TimerDnClassName::pause() {
    if (!inPause) {
      inPause=true;
      time -= (long)millis();                 // store effective value of the timer 
      if (time<0) time=0; }                   
  }
  
void _TimerDnClassName::resume() {
    if (inPause) {
       inPause=false;
       time += (long)millis(); } }            // restore relative value to millis()

bool _TimerDnClassName::paused() { return inPause; }


  void _TimerDnClassName::init(_TimerDnInt value) 
  { inPause=false; set(value); }

#if _TimerDnUseTimeBase == true
  void _TimerDnClassName::init(_TimerDnInt value, int base) 
  { timeBase=base; init(value); }
#endif

