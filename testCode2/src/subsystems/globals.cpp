#include "main.h"

//initialize controller
pros::Controller master(CONTROLLER_MASTER);

#define rFPort 11
#define rMPort 1
#define rRPort 12
#define lFPort 20
#define lMPort 10
#define lRPort 19
#define rotationPort 2
#define inertialPort 3
#define puncherPort 15

#define motorP 0
#define motorI 0
#define motorD 0
#define inertialP 0
#define inertialI 0
#define inertialD 0
#define rotationP 0
#define rotationI 0
#define rotationD 0

//initialize motors in drivebase
drivebaseMotorStore drivebaseMotors = drivebaseMotorStore {
    createPID<pros::Motor>{pros::Motor(rFPort, MOTOR_GEAR_600, false), motorP, motorI, motorD},
    createPID<pros::Motor>{pros::Motor(rMPort, MOTOR_GEAR_600, false), motorP, motorI, motorD},
    createPID<pros::Motor>{pros::Motor(rRPort, MOTOR_GEAR_200, true), motorP, motorI, motorD},
    createPID<pros::Motor>{pros::Motor(lFPort, MOTOR_GEAR_600, true), motorP, motorI, motorD},
    createPID<pros::Motor>{pros::Motor(lMPort, MOTOR_GEAR_600, true), motorP, motorI, motorD},
    createPID<pros::Motor>{pros::Motor(lRPort, MOTOR_GEAR_200, false), motorP, motorI, motorD}
};

 createPID<pros::Rotation> puncherRotation = createPID<pros::Rotation> {
    pros::Rotation(rotationPort, false), rotationP, rotationI, rotationD
};

 createPID<pros::Imu> inertialPID = createPID<pros::Imu>{pros::Imu(inertialPort), inertialP, inertialI, inertialD};

pros::Motor puncher(puncherPort, MOTOR_GEAR_100, false);
