#line 1 "c:\\Users\\pietr\\Desktop\\DENSO\\arduino\\A4988_StepperMotorDriver\\test\\pin.h"
#ifndef PIN_H
#define PIN_H

#include "Arduino.h"

class pin {
    // properties
    public:
    int n;
    int value;
    int type;

    // constructor
    pin(int _n, int _value);

    // methods
    void set(int _value);
};

#endif