#include "main.h"

#define kP 0
#define kI 0
#define kD 0

//create controller
extern pros::Controller master;

/*
Structures
*/

//Struct which contains all drivebase motors for easy access
struct drivebaseMotorStore{
    motorControl rF;
    motorControl rM;
    motorControl rR;
    motorControl lF;
    motorControl lM;
    motorControl lR;

};
//Stores all motors usd for drivebase
extern drivebaseMotorStore drivebaseMotors;
//Stores value for puncher motor and PID controls
extern puncherControl puncher;
