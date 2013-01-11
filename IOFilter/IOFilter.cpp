
#include "IOFilter.h"

int16_t        InputFilterPrevTime = 0;
int16_t        InputFilterNewTime  = 0;
IOFilterItem * ptrInputFilterList  = NULL;

#if IOFilter_ReadWriteAll == true

IOFilterItem * ptrInputList        = NULL;
IOFilterItem * ptrOutputList       = NULL;

#endif


void IOFilterItem::AddToList(IOFilterItem** list)
{ pNext=(*list); (*list) = this;}


void IOFilterItem::RemoveFromList(IOFilterItem** list)
{IOFilterItem * ptr = (*list);                 // lets try first one
if (ptr==this) (*list) = ptr->pNext;           // if this item is the last one registered
else 
  do { if (ptr->pNext==this) {                 // if the next is the one to remove
           ptr->pNext = ptr->pNext->pNext;     // skip it
           break; } }               
  while ((ptr=ptr->pNext));                    // try next item
};


Input::Input(int8_t pin)                       // constructor, just launch the standard pin mode
{ pinMode((this->pin = pin),INPUT); 
#if IOFilter_ReadWriteAll == true
  AddToList(&ptrInputList);
#endif
};


uint8_t Input::get()   
{ if ((oldval=digitalRead(pin))) return 1; else return 0;  }


#if IOFilter_ReadWriteAll == true

Input::~Input()
{ RemoveFromList(&ptrInputList); };

void Input::readAll() 
  { Input * ptr = (Input*)ptrInputList; 
    do { ptr->read(); } while ((ptr=(Input*)(ptr->pNext))); }

void Input::read() { };

#endif


Output::Output(int8_t pin)
{ pinMode(this->pin = pin, OUTPUT); oldval=0; 
#if IOFilter_ReadWriteAll == true
  AddToList(&ptrOutputList);
#endif
};

void Output::set(uint8_t val) 
{ digitalWrite(pin, oldval=val); }

uint8_t Output::get() 
{ return oldval; }



#if IOFilter_ReadWriteAll == true

Output::~Output()
{ RemoveFromList(&ptrOutputList); };

void Output::writeAll() 
{ Output * ptr = (Output*)ptrOutputList; 
  do { ptr->write(); } while ((ptr=(Output*)(ptr->pNext))); }

void Output::write() { };  // TBD

#endif


InputMem::InputMem(void* addr, uint8_t bit) 
{ ptrMem = (uint8_t*)addr + bit/8; 
  bit %= 8; bitMask=(1 << bit); };

uint8_t InputMem::get() 
{ if ((*ptrMem) & bitMask) return 1; else return 0; }


OutputMem::OutputMem(void* addr, uint8_t bit) 
{ ptrMem = (uint8_t*)addr + bit/8; 
  bit %= 8; bitMask=(1 << bit); };

void OutputMem::set(uint8_t val) 
{ if (val) { val = bitMask;}; 
  (*ptrMem) = ((*ptrMem) & ~bitMask) | val; }

uint8_t OutputMem::get() 
{ if ((*ptrMem) & bitMask) return 1; else return 0; }



InputFilter::InputFilter(uint8_t pin, int16_t timeOn)
{ init(pin, timeOn, 0); }


InputFilter::InputFilter(uint8_t pin, int16_t timeOn, int16_t timeOff)
{ init(pin, timeOn, timeOff); }


InputFilter::~InputFilter()
{ RemoveFromList(&ptrInputFilterList);   }


void  InputFilter::init(uint8_t pin, int16_t timeOn, int16_t timeOff)
{ pinMode((this->pin=pin), INPUT); 
  AddToList(&ptrInputFilterList);
  value = last = 0; 
  time = 0; this->timeOn = timeOn; this->timeOff = timeOff; };


uint8_t InputFilter::readPin() 
{ return (last=digitalRead(pin)); }

  
void InputFilter::checkAll(int16_t temp)
{ InputFilterNewTime = (int16_t)millis();
  if (temp) if ((InputFilterNewTime - InputFilterPrevTime) <= temp) return;
  InputFilterPrevTime = InputFilterNewTime;
  checkAll_time(InputFilterNewTime); 
}


void InputFilter::checkAll()
{ checkAll(IOFilter_defaultCheckTime); }


void InputFilter::checkAll_time(int16_t temp)
{ InputFilter * ptr = (InputFilter*)ptrInputFilterList;
  do { ptr->check_time(temp); } while ((ptr=(InputFilter*)(ptr->pNext))); };


void InputFilter::check_time(int16_t temp)
{ if (readPin() != value)
     if (value) { // falling edge
        if ((temp - time) > timeOff) { value=0; } }
     else { // rising edge
        if ((temp - time) > timeOn)  { counter++; value=1; } } 
  else { time=temp; }
}


void InputFilter::check()
{ check_time((int16_t)millis()); };


uint8_t InputFilter::get() 
{ int16_t temp = (int16_t)millis();
  if ((temp - InputFilterPrevTime) > IOFilter_defaultCheckTime) { check_time(temp); };
 return value; } 


IOFilter_Counter_t InputFilter::count() { return counter; }
  
void InputFilter::reset() { counter=0; }

 
#if IOFilter_ReadWriteAll == true
  void readAll() { };                         // WIP & TBD
  void read() { };                            // WIP & TBD
#endif

