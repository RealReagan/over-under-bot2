#include "main.h"

//create controller
extern pros::Controller master;

/*
Structures
*/


//Struct which contains all drivebase motors for easy access
struct drivebaseMotorStore{
    createPID<pros::Motor> rF;
    createPID<pros::Motor> rM;
    createPID<pros::Motor> rR;
    createPID<pros::Motor> lF;
    createPID<pros::Motor> lM;
    createPID<pros::Motor> lR;

};

//Stores all motors used for drivebase
extern drivebaseMotorStore drivebaseMotors;

//Stores value for PID controls
extern createPID<pros::Rotation> puncherRotation;
extern createPID<pros::Imu> inertialPID;

//Create puncher motor
extern pros::Motor liftMotor;
extern pros::Motor puncher;
extern pros::Motor intake;
