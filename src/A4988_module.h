#ifndef A4988_MODULE
#define A4988_MODULE

#include "pin.h"

struct struct_IO{
    pin SLEEP;
    pin STEP;
    pin MS1;
    pin MS2;
    pin MS3;
    pin DIR;
    pin ENABLE;
    pin RESET;
    
    struct_IO(int SLEEP_pin, int STEP_pin, int MS1_pin, int MS2_pin, int MS3_pin, int DIR_pin, int ENABLE_pin, int RESET_pin): \
        SLEEP(SLEEP_pin, LO), \
        STEP(STEP_pin, LO), \
        MS1(MS1_pin, LO), \
        MS2(MS2_pin, LO), \
        MS3(MS3_pin, LO), \
        DIR(DIR_pin, LO), \
        ENABLE(ENABLE_pin, LO), \
        RESET(RESET_pin, LO){
        };
};

struct struct_pin_n{
    int SLEEP;
    int STEP;
    int MS1;
    int MS2;
    int MS3;
    int DIR;
    int ENABLE;
    int RESET;
};

class A4988_module {
    // properties 
    public:
    struct_IO IO;
    int step_resolution;
    // 1:   full step
    // 2:   1/2 step
    // 3:   1/4 step
    // 4:   1/8 step
    // 8:   1/8 step
    // 16:  1/16 step
    int motor_steps;

    
    // constructor 
    A4988_module(struct_pin_n _pin_n, int _step_resolution, int _motor_steps);

    // methods
    void init();
    void step(int n_step, int dir, double speed);
    double getPosition();
};

#endif