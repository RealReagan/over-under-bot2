#include "main.h"

//create controller
extern pros::Controller master;

/*
Structures
*/

//create struct for unique motor cmds on puncher
struct targetPID {
    pros::Rotation sensor;
    float integral;
    float lastError;
    //returns value to spin motor according to PID adjusment
    const float PIDAdjust(const float& target);
    //finds error in motor speed to target
    const float proport(const float& target, const float& speed);
    //finds total value of accumulated error(integral)
    const float integrate(const float& error);
    //finds immediate change in error(derivative)
    const float derive(const float& error);
};

struct targetPIDI {
    pros::IMU sensor;
    float integral;
    float lastError;
    //returns value to spin motor according to PID adjusment
    const float PIDAdjust(const float& target);
    //finds error in motor speed to target
    const float proport(const float& target, const float& speed);
    //finds total value of accumulated error(integral)
    const float integrate(const float& error);
    //finds immediate change in error(derivative)
    const float derive(const float& error);
};

//create struct for unique motor cmds
struct speedPID {
    pros::Motor storedMotor;
    float integral;
    float lastError;
    //returns value to spin motor according to PID adjusment
    const float PIDAdjust(const float& target);
    //finds error in motor speed to target
    const float proport(const float& target, const float& speed);
    //finds total value of accumulated error(integral)
    const float integrate(const float& error);
    //finds immediate change in error(derivative)
    const float derive(const float& error);

};

//Struct which contains all drivebase motors for easy access
struct drivebaseMotorStore{
    speedPID rF;
    speedPID rM;
    speedPID rR;
    speedPID lF;
    speedPID lM;
    speedPID lR;

};

//Stores all motors usd for drivebase
extern drivebaseMotorStore drivebaseMotors;

//Stores value for puncher motor and PID controls
extern targetPID puncherRotation;
extern targetPIDI headingHold;

//Create rotation sensor for puncher
extern pros::Motor puncher;