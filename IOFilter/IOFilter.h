#ifndef IO_FILTER_H
#define IO_FILTER_H

/*****************************************************************************/
/* SCOOP LIBRARY / AUTHOR FABRICE OUDERT / GNU GPL V3                        */
/* https://code.google.com/p/arduino-scoop-cooperative-scheduler-arm-avr/    */
/* BETA VERSION 0.9 FOR TESTING AND FEEDBACKS                                */
/* ENJOY AND USE AT YOUR OWN RISK  :)                                        */
/* SHOULD READ USER GUIDE FIRST (@!@)                                        */
/*****************************************************************************/

#include <Arduino.h>

// this default time delay will be checked between each call to checkAll() before proceeding
const int16_t IOFilter_defaultCheckTime = 10; // 5..250 ms is reasonable, should be quarter of the min timOn/timeOff of the whole list

// change for true, if the program will use readAll() or writeAll() as a primary condition to getting pin values read and written
// then each Input or Output is registred in a list and the corresponding code is added in constructor/destructor
#define IOFilter_ReadWriteAll true            // true by default
#define IOFilter_Counter_t    uint16_t        // 16 bit most likely enough

/**********  PROTOTYPES *********/

class Input;
class Output;
class InputMem;
class OutputMem;
class InputFilter;


// this object is used to chain the items in list and to provid add/remove mechanisms
class IOFilterItem
{public:
  void AddToList(IOFilterItem** list);        // the list parameter passed will be modified, then we have **
  void RemoveFromList(IOFilterItem** list);
  IOFilterItem* pNext;                        // this pointer makes the link to the next object in the chain/list. it has to be typecasted
};

/**********  INPUT CLASS *********/

#if IOFilter_ReadWriteAll == true
class Input : IOFilterItem                    // will inherit the object for list management
#else
class Input        
#endif
{public:

  Input(int8_t pin);                          // constructor

  uint8_t get();  

  operator uint8_t() 
  { return get(); }

#if IOFilter_ReadWriteAll == true
  ~Input();                                   // provide a destructor that can be called if the input is declared as local
  static void readAll();                      // intend to physically read all inputs in the list, not only "this"
  void read();                                // intend to physically read this inputs
#endif

private:
  int8_t pin,oldval;
};
  

/**********  OUTPUT CLASS *********/

#if IOFilter_ReadWriteAll == true
class Output : IOFilterItem
#else
class Output
#endif
{public:

  Output(int8_t pin); 

  void set(uint8_t val); 
  
  uint8_t get(); 
  
  operator uint8_t() 
  { return get(); }

  Output& operator=(const uint8_t rhs)
  { set(rhs); return *this; }

#if IOFilter_ReadWriteAll == true
  ~Output();
  static void writeAll();
  void write();
#endif

private:
  uint8_t pin, oldval;
};


/**********  INPUTMEM CLASS *********/

class InputMem
{public:

  InputMem(void* addr, uint8_t bit); 
  
  uint8_t get(); 
  
  operator uint8_t() 
  { return get(); }

private:
  uint8_t* ptrMem, bitMask;
};


/**********  OUTPUT CLASS *********/

class OutputMem
{public:

  OutputMem(void* addr, uint8_t bit);
  
  void set(uint8_t val); 
  
  uint8_t get();
  
  operator uint8_t() 
  { return get(); }

  OutputMem& operator=(const uint8_t rhs)
  { set(rhs); return *this; }

private:
  uint8_t* ptrMem, bitMask;
};


/**********  INPUTFILTER CLASS *********/

class InputFilter : IOFilterItem
{ public: 
    
  InputFilter(uint8_t pin, int16_t timeOn);
  InputFilter(uint8_t pin, int16_t timeOn, int16_t timeOff);
  ~InputFilter();
  
  uint8_t readPin(); 
  
  uint8_t get(); 

  operator uint8_t() 
  { return get(); }

  static void checkAll();

  static void checkAll(int16_t temp);
  
  static void checkAll_time(int16_t temp);

  void check();

  void check_time(int16_t temp);
  
  IOFilter_Counter_t count();
  
  void reset();

#if IOFilter_ReadWriteAll == true
  static void readAll() ;
  void read();
#endif

private:
  void init(uint8_t pin, int16_t timeOn, int16_t timeOff);

  uint8_t       pin,value,last;
  int16_t       timeOn, timeOff, time;
  IOFilter_Counter_t counter;
};

#endif

