#ifndef PIN_CLASS
#define PIN_CLASS

#include "Arduino.h"

const int HI = 1;
const int LO = 0;

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