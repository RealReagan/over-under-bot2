#include "main.h"
#define PI 3.141592654
#define DISTANCERIGHT 7
#define DISTANCELEFT 7
#define TICKSPERROTATION 333.3333333
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
//Stores motors to create averaging command for use in PID
struct averageMotors {
    drivebaseMotorStore motors;

    const float getEncoders();
};

struct splitMotors {
    pros::Motor front;
    pros::Motor mid;
    pros::Motor rear;

    const float getEncoders();
};
//Makes an item toggleable by storeing it's current state
template <class item> struct makeToggleable {
    item controlledItem;

    bool state = false;
};

/*
Motors
*/
//Stores all motors used for drivebase
extern drivebaseMotorStore drivebaseMotors;
//store motors for usage in auto

extern createPID<splitMotors> rightPID;
extern createPID<splitMotors> leftPID;
extern createPID<averageMotors> autoPID;

//Stores value for PID controls
extern createPID<pros::Rotation> puncherRotation;
extern createPID<pros::Imu> inertialPID;

//Create puncher motor
extern pros::Motor liftMotor;
extern pros::Motor puncher;
extern pros::Motor intake;

//Create pneumatic colonoids
extern makeToggleable<pros::ADIDigitalOut> rightWing;
extern makeToggleable<pros::ADIDigitalOut> leftWing;
extern makeToggleable<pros::ADIDigitalOut> clip;
