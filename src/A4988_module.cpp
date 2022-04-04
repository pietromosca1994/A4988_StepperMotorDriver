#include "A4988_module.h"

A4988_module::A4988_module(struct_pin_n _pin_n, int _step_resolution, int _motor_steps):
    step_resolution(_step_resolution), \
    motor_steps(_motor_steps), \
    IO {_pin_n.SLEEP, _pin_n.STEP, _pin_n.MS1, _pin_n.MS2, _pin_n.MS3, _pin_n.DIR, _pin_n.ENABLE, _pin_n.RESET} \
{

    // pin initilization
    // step initialization (from manual)
    switch(step_resolution) {
        case 1:
            IO.MS1.set(LO);
            IO.MS2.set(LO);
            IO.MS3.set(LO);
            break; 
        case 2:
            IO.MS1.set(HI);
            IO.MS2.set(LO);
            IO.MS3.set(LO);
            break; 
        case 4:
            IO.MS1.set(LO);
            IO.MS2.set(HI);
            IO.MS3.set(LO);
            break;
        case 8:
            IO.MS1.set(HI);
            IO.MS2.set(HI);
            IO.MS3.set(LO);
            break;
        case 16:
            IO.MS1.set(HI);
            IO.MS2.set(HI);
            IO.MS3.set(HI);
            break;
        default: // the default it's full step
            IO.MS1.set(LO);
            IO.MS2.set(LO);
            IO.MS3.set(LO);
    }
        
        IO.RESET.set(LO);
};

void step(int n_step, int dir, double speed){

};

double getPosition(){

};

void init(){

};