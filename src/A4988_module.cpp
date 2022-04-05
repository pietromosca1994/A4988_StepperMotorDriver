#include "A4988_module.h"

// constructor function for A4988 module
A4988_module::A4988_module(int pin_SLEEP, int pin_STEP, int pin_MS1, int pin_MS2, int pin_MS3, int pin_DIR, int pin_ENABLE, int pin_RESET, int _step_resolution, int _motor_steps, double _max_speed):
    step_resolution(_step_resolution), \
    motor_steps(_motor_steps), \
    microsteps(motor_steps*step_resolution), \
    max_speed(_max_speed), \
    IO {pin_SLEEP, pin_STEP, pin_MS1, pin_MS2, pin_MS3, pin_DIR, pin_ENABLE, pin_RESET} \
{
    basic_step_angle=360.0/microsteps;

    // step initialization (from manual)
    switch(step_resolution) {
        case 1:
            IO.MS1.set(LOW);
            IO.MS2.set(LOW);
            IO.MS3.set(LOW);
            break; 
        case 2:
            IO.MS1.set(HIGH);
            IO.MS2.set(LOW);
            IO.MS3.set(LOW);
            break; 
        case 4:
            IO.MS1.set(LOW);
            IO.MS2.set(HIGH);
            IO.MS3.set(LOW);
            break;
        case 8:
            IO.MS1.set(HIGH);
            IO.MS2.set(HIGH);
            IO.MS3.set(LOW);
            break;
        case 16:
            IO.MS1.set(HIGH);
            IO.MS2.set(HIGH);
            IO.MS3.set(HIGH);
            break;
        default: // the default it's full step
            IO.MS1.set(LOW);
            IO.MS2.set(LOW);
            IO.MS3.set(LOW);
    };
        
       
    IO.SLEEP.set(LOW);
    IO.STEP.set(LOW);
    IO.DIR.set(LOW);
    IO.ENABLE.set(LOW);
    IO.RESET.set(LOW); 

};

// function to execute steps 
// inputs :
// n_step :         number of steps         [-]
// dir :            direction               [-]
// speed :          rotation speed          [deg/s]
void A4988_module::makeStep(int n_step, int dir, double speed){
     double T;      // period   [ms]

    T=basic_step_angle/speed*1000;
    
    // update direction
    switch(dir){
        case 1:
            IO.DIR.set(HIGH);
        case -1:
            IO.DIR.set(LOW);
        default:
            dir=1;              // clip direction in case  of out of range value
            IO.DIR.set(LOW);
    };

    IO.ENABLE.set(HIGH);
    for (int i=0; i<n_step; i++){

        // generate PWM 
        IO.STEP.set(HIGH);
        delay(T*pulse_duty);
        
        // add step
        step+=dir;
        if (step<0){
            step=microsteps;
        };
        if (step>microsteps){
            step=0; 
        }
        angle=step*basic_step_angle;
         
        IO.STEP.set(LOW);
        delay(T*(1-pulse_duty));          
    };
    IO.ENABLE.set(LOW);
};

// function to bring the stepper motor  to the zero position
void A4988_module::setZeroPosition(){
    makeStep(microsteps, 1, max_speed);
    step=0;
    angle=0;
};

// function
void A4988_module::dispState(){
    Serial.print("Step:");
    Serial.print(int(step), DEC);
    Serial.print("\t");

    Serial.print("Angle:");
    Serial.print(double(angle), DEC);
    Serial.print("\t");

    Serial.print("SLEEP:");
    Serial.print(int(IO.SLEEP.value), DEC);
    Serial.print("\t");

    Serial.print("STEP:");
    Serial.print(int(IO.STEP.value), DEC);
    Serial.print("\t");

    Serial.print("MS1:");
    Serial.print(int(IO.MS1.value), DEC);
    Serial.print("\t");

    Serial.print("MS2:");
    Serial.print(int(IO.MS2.value), DEC);
    Serial.print("\t");

    Serial.print("MS3:");
    Serial.print(int(IO.MS3.value), DEC);
    Serial.print("\t");

    Serial.print("DIR:");
    Serial.print(int(IO.DIR.value), DEC);
    Serial.print("\t");

    Serial.print("ENABLE:");
    Serial.print(int(IO.ENABLE.value), DEC);
    Serial.print("\t");

    Serial.print("RESET:");
    Serial.print(int(IO.RESET.value), DEC);
    Serial.print("\n");


};

double getPosition(){
    
};