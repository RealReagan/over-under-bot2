#include "main.h"

//initialize controller
pros::Controller master(CONTROLLER_MASTER);

#define rFPort 11
#define rMPort 1
#define rRPort 12
#define lFPort 20
#define lMPort 10
#define lRPort 19
#define puncherPort 15
#define rotationPort 2

//initialize motors in drivebase
drivebaseMotorStore drivebaseMotors = drivebaseMotorStore {
    speedPID{pros::Motor(rFPort, MOTOR_GEAR_600, false), 0, 0},
    speedPID{pros::Motor(rMPort, MOTOR_GEAR_600, false), 0, 0},
    speedPID{pros::Motor(rRPort, MOTOR_GEAR_200, true), 0, 0},
    speedPID{pros::Motor(lFPort, MOTOR_GEAR_600, true), 0, 0},
    speedPID{pros::Motor(lMPort, MOTOR_GEAR_600, true), 0, 0},
    speedPID{pros::Motor(lRPort, MOTOR_GEAR_200, false), 0, 0}
};

 targetPID puncherRotation = targetPID{pros::Rotation(rotationPort, false), 0, 0};

pros::Motor puncher(puncherPort, MOTOR_GEAR_100, false);
