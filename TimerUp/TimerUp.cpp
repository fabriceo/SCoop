
#include "TimerUp.h"

  _TimerUpClassName::_TimerUpClassName() 
#if _TimerUpUseTimeBase == true
  { init(1000000000L,1); } 
#else
  { init(1000000000L); } 
#endif

  _TimerUpClassName::_TimerUpClassName (_TimerUpInt timeMax) 
#if _TimerUpUseTimeBase == true
  { init(timeMax,1); }
#else
  { init(timeMax); }
#endif

#if _TimerUpUseTimeBase == true
  _TimerUpClassName::_TimerUpClassName (_TimerUpInt timeMax, int base) 
  { init(timeMax,base); }
#endif


void _TimerUpClassName::setRollOver(_TimerUpInt timeMax)       // redefine time rollover value. this also reset the timer and the "paused" falg
  { init(timeMax); }                          

  
bool _TimerUpClassName::rollOver()                             // return true each time the timer is rolling over
  { bool temp=check((long)millis()); 
    overflow=false; 
    return temp; }
  
	
  void _TimerUpClassName::reset()                                // reset the timer value to 0
  { if (inPause) time=0;                      // effective value
    else time=(long)millis();                 // relative value
    overflow=false; }


  void _TimerUpClassName::set(long value) {                     // set the timer to a user defined value
#if _TimerUpUseTimeBase  == true
   if (timeBase>1) value *= timeBase;
#endif
    if (value>=timeRollOver)                  // sanity check with max rollover value defined in constructor
       { timeRollOver=value; value=0;}        // if value is above then timer is forced to 0 like with a rollover
    if (inPause) time = value;                // effective time value
    else time=(long)millis()- value;          // relative time value
    overflow=false; }


  _TimerUpInt _TimerUpClassName::get()                           // return the value of the timer and verify potential rollover
  { register long temp;
    if (inPause) { temp =  time; }            // effective time
    else         { temp = (long)millis(); check(temp); temp -= time; }
#if _TimerUpUseTimeBase == true
    if (timeBase>1) { temp /= timeBase; }
#endif
   return (_TimerUpInt)temp; }

   
    
 void _TimerUpClassName::pause()                                 // put the timer in pause
 { if (!inPause) {
      inPause=true;
      register long temp = (long)millis();
      check(temp);
      time = temp-time; }                     // store effective time in variable
 } 
 
 void _TimerUpClassName::resume()                                // resume the timer to its "paused" value and continue counting
 { if (inPause) {
      inPause=false;
      time= (long)millis()-time; }            // recalculate relative time from efective value
 }


 bool _TimerUpClassName::paused() { return inPause; }
 

  void _TimerUpClassName::init(long timeMax) {
#if _TimerUpUseTimeBase == true
    if (timeBase>1) {
       if (timeMax==-1) timeMax = 1000000000L / timeBase;
       timeRollOver = timeMax * timeBase; }
    else {
       if (timeMax==-1) timeMax = 1000000000L;
       timeRollOver = timeMax; }     
#else
     if (timeMax==-1) { timeMax = 1000000000L; }
     timeRollOver = timeMax; 
#endif
    inPause=false; 
    reset(); } 
  
#if _TimerUpUseTimeBase  == true
  void _TimerUpClassName::init(_TimerUpInt timeMax, int base) 
  { timeBase=base; init(timeMax); }
#endif
  
  bool _TimerUpClassName::check(long temp)                       // check if the timer has rolledover since last call. then set the overflow flag
  { if ((temp-time)>=timeRollOver) 
       { time += timeRollOver; 
         return overflow=true; } 
    else return overflow;}
  
