# 1 "c:\\Users\\pietr\\Desktop\\DENSO\\arduino\\A4988_StepperMotorDriver\\test\\A4988_module.cpp"
# 2 "c:\\Users\\pietr\\Desktop\\DENSO\\arduino\\A4988_StepperMotorDriver\\test\\A4988_module.cpp" 2

// constructor function for A4988 module
A4988_module::A4988_module(int pin_SLEEP, int pin_STEP, int pin_MS1, int pin_MS2, int pin_MS3, int pin_DIR, int pin_ENABLE, int pin_RESET, int _step_resolution, int _motor_steps, double _max_speed):
    step_resolution(_step_resolution),
    motor_steps(_motor_steps),
    microsteps(motor_steps*step_resolution),
    max_speed(_max_speed),
    IO {pin_SLEEP, pin_STEP, pin_MS1, pin_MS2, pin_MS3, pin_DIR, pin_ENABLE, pin_RESET}
 {
    basic_step_angle=360.0/microsteps;

    // step initialization (from manual)
    switch(step_resolution) {
        case 1:
            IO.MS1.set(0x0);
            IO.MS2.set(0x0);
            IO.MS3.set(0x0);
            break;
        case 2:
            IO.MS1.set(0x1);
            IO.MS2.set(0x0);
            IO.MS3.set(0x0);
            break;
        case 4:
            IO.MS1.set(0x0);
            IO.MS2.set(0x1);
            IO.MS3.set(0x0);
            break;
        case 8:
            IO.MS1.set(0x1);
            IO.MS2.set(0x1);
            IO.MS3.set(0x0);
            break;
        case 16:
            IO.MS1.set(0x1);
            IO.MS2.set(0x1);
            IO.MS3.set(0x1);
            break;
        default: // the default it's full step
            IO.MS1.set(0x0);
            IO.MS2.set(0x0);
            IO.MS3.set(0x0);
    };


    IO.SLEEP.set(0x0);
    IO.STEP.set(0x0);
    IO.DIR.set(0x0);
    IO.ENABLE.set(0x0);
    IO.RESET.set(0x0);

};

// function to execute steps 
// inputs :
// n_step :         number of steps         [-]
// dir :            direction               [-]
// speed :          rotation speed          [deg/s]
void A4988_module::makeStep(int n_step, int dir, double speed){
     double T; // period   [ms]

    T=basic_step_angle/speed*1000;

    // update direction
    switch(dir){
        case 1:
            IO.DIR.set(0x1);
        case -1:
            IO.DIR.set(0x0);
        default:
            dir=1; // clip direction in case  of out of range value
            IO.DIR.set(0x0);
    };

    IO.ENABLE.set(0x1);
    for (int i=0; i<n_step; i++){

        // generate PWM 
        IO.STEP.set(0x1);
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

        IO.STEP.set(0x0);
        delay(T*(1-pulse_duty));
    };
    IO.ENABLE.set(0x0);
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
    Serial.print(int(step), 10);
    Serial.print("\t");

    Serial.print("Angle:");
    Serial.print(double(angle), 10);
    Serial.print("\t");

    Serial.print("SLEEP:");
    Serial.print(int(IO.SLEEP.value), 10);
    Serial.print("\t");

    Serial.print("STEP:");
    Serial.print(int(IO.STEP.value), 10);
    Serial.print("\t");

    Serial.print("MS1:");
    Serial.print(int(IO.MS1.value), 10);
    Serial.print("\t");

    Serial.print("MS2:");
    Serial.print(int(IO.MS2.value), 10);
    Serial.print("\t");

    Serial.print("MS3:");
    Serial.print(int(IO.MS3.value), 10);
    Serial.print("\t");

    Serial.print("DIR:");
    Serial.print(int(IO.DIR.value), 10);
    Serial.print("\t");

    Serial.print("ENABLE:");
    Serial.print(int(IO.ENABLE.value), 10);
    Serial.print("\t");

    Serial.print("RESET:");
    Serial.print(int(IO.RESET.value), 10);
    Serial.print("\n");


};

double getPosition(){

};
# 1 "c:\\Users\\pietr\\Desktop\\DENSO\\arduino\\A4988_StepperMotorDriver\\test\\src.ino"
//#include <A4988_module.h>
# 3 "c:\\Users\\pietr\\Desktop\\DENSO\\arduino\\A4988_StepperMotorDriver\\test\\src.ino" 2

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
}

void loop()
{

 stepper_driver.makeStep(4, 1, 20);
 //Serial.println("Hello World");
    //delay(1000);
 stepper_driver.dispState();
}
