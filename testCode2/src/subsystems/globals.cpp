#include "main.h"

//initialize controller
pros::Controller master(CONTROLLER_MASTER);

#define rFPort 1
#define rMPort 8
#define rRPort 20
#define lFPort 11
#define lMPort 2
#define lRPort 5
#define puncherPort 7
#define rotationPort 2
#define inertialPort 3

//initialize motors in drivebase
drivebaseMotorStore drivebaseMotors = drivebaseMotorStore {
    speedPID{pros::Motor(rFPort, MOTOR_GEAR_200, false), 0, 0},
    speedPID{pros::Motor(rMPort, MOTOR_GEAR_200, false), 0, 0},
    speedPID{pros::Motor(rRPort, MOTOR_GEAR_200, false), 0, 0},
    speedPID{pros::Motor(lFPort, MOTOR_GEAR_200, true), 0, 0},
    speedPID{pros::Motor(lMPort, MOTOR_GEAR_200, true), 0, 0},
    speedPID{pros::Motor(lRPort, MOTOR_GEAR_200, true), 0, 0}
};

targetPID puncherRotation = targetPID{pros::Rotation(rotationPort, false), 0, 0};
targetPIDI headingHold = targetPIDI{pros::IMU(inertialPort), 0, 0};

pros::Motor puncher(puncherPort, MOTOR_GEAR_100, false);
