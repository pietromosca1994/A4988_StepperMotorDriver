#line 1 "c:\\Users\\pietr\\Desktop\\DENSO\\arduino\\A4988_StepperMotorDriver\\test\\pin.cpp"
// #include "Arduino.h"
#include "pin.h" 

pin::pin(int _n, int _value):
    n(_n), \
    value(_value)
{
    if (n>0){ // in case n<0 the pin is disabled
        pinMode(n, OUTPUT);
        digitalWrite(n, value);
    };
};

void pin::set(int _value){
    if (n>0){
        value=_value;
        digitalWrite(n, _value);
    };
};
