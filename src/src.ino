//#include <A4988_module.h>
#include "A4988_module.h"

// pin assignment
int pin_SLEEP=1;
int pin_STEP=2;
int pin_MS1=3;
int pin_MS2=4;
int pin_MS3=5;
int pin_DIR=6;
int pin_ENABLE=7;
int pin_RESET=8;

// system physical properties
int step_resolution=4;
int motor_steps=200;
double max_speed=30;

A4988_module stepper_driver(pin_SLEEP, pin_STEP, pin_MS1, pin_MS2, pin_MS3, pin_DIR, pin_ENABLE, pin_RESET, step_resolution, motor_steps, max_speed);

void setup()
{
	Serial.begin(9600);
	stepper_driver.setZeroPosition();
}

void loop()
{	
	int n_step=4;
	int dir=1;

	stepper_driver.makeStep(n_step, dir, max_speed);
	stepper_driver.dispState();
}
