#include "main.h"

//initialize controller
pros::Controller master(CONTROLLER_MASTER);

//initialize motors in drivebase
drivebaseMotorStore drivebaseMotors = drivebaseMotorStore {
    motorControl{pros::Motor(11, MOTOR_GEAR_600, false), 0, 0},
    motorControl{pros::Motor(1, MOTOR_GEAR_600, false)},
    motorControl{pros::Motor(12, MOTOR_GEAR_200, true)},
    motorControl{pros::Motor(20, MOTOR_GEAR_600, true)},
    motorControl{pros::Motor(10, MOTOR_GEAR_600, true)},
    motorControl{pros::Motor(19, MOTOR_GEAR_200, false)}
};
