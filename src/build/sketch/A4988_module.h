#line 1 "c:\\Users\\pietr\\Desktop\\DENSO\\arduino\\A4988_StepperMotorDriver\\test\\A4988_module.h"
/*
  A4988_module.h - Library for controlling the A4988 stepper motor driver
  Created by Pietro Mosca, April 4, 2021.
  Released into the public domain.
*/

#ifndef A4988_MODULE_H
#define A4988_MODULE_H

#include "Arduino.h"
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
        SLEEP(SLEEP_pin, LOW), \
        STEP(STEP_pin, LOW), \
        MS1(MS1_pin, LOW), \
        MS2(MS2_pin, LOW), \
        MS3(MS3_pin, LOW), \
        DIR(DIR_pin, LOW), \
        ENABLE(ENABLE_pin, LOW), \
        RESET(RESET_pin, LOW){
        };
};

/*
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
*/

class A4988_module {
    // properties 
    public:
        // public properties
        struct_IO IO;
        int step_resolution;        // step resolution                          [-]
        // 1:   full step
        // 2:   1/2 step
        // 3:   1/4 step
        // 4:   1/8 step
        // 8:   1/8 step
        // 16:  1/16 step
        int motor_steps;            // total amount of motor steps              [-]
        int microsteps;             // total amount of motor microsteps         [-] 
        double max_speed;           // max motor speed for                      [deg/s]
        double basic_step_angle;    // basic step angle                         [deg]
        double pulse_duty=20/100;   // pulse_duty                               [-]
        int step;                   // step count                               [-]
        double angle;               // angle                                    [deg]
        
        // public methods
        
        // constructor 
        A4988_module(int pin_SLEEP, int pin_STEP, int pin_MS1, int pin_MS2, int PIN_MS3, int pin_DIR, int pin_ENABLE, int pin_RESET, int _step_resolution, int _motor_steps, double _max_speed);

        // methods
        void makeStep(int n_step, int dir, double speed);     
        void setZeroPosition();
        double getPosition();
        void dispState();
        

    private:
        // private properties 

};

#endif