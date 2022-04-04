#include "pin.h" 

pin::pin(int _n, int _value):
    n(_n), \
    value(_value)
{
    pinMode(n, OUTPUT);
    digitalWrite(n, value);
};

void pin::set(int _value){
    digitalWrite(n, _value);
};
