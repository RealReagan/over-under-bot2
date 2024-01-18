#include "main.h"

//initialize controller
pros::Controller master(CONTROLLER_MASTER);

#define rFPort 1
#define rMPort 8
#define rRPort 20
#define lFPort 11
#define lMPort 2
#define lRPort 6
#define rotationPort 3
#define inertialPort 4
#define puncherPort 7
#define intakePort 19
#define liftPort 12
#define rightPneumaticPort 2
#define leftPneumaticPort 5

#define motorP 0
#define motorI 0
#define motorD 0
#define autoP 0
#define autoI 0
#define autoD 0
#define inertialP 0
#define inertialI 0
#define inertialD 0
#define rotationP 0
#define rotationI 0
#define rotationD 0

drivebaseMotorStore drivebaseMotors = drivebaseMotorStore {
    createPID<pros::Motor>{pros::Motor(rFPort, MOTOR_GEAR_200, true), motorP, motorI, motorD},
    createPID<pros::Motor>{pros::Motor(rMPort, MOTOR_GEAR_600, false), motorP, motorI, motorD},
    createPID<pros::Motor>{pros::Motor(rRPort, MOTOR_GEAR_600, false), motorP, motorI, motorD},
    createPID<pros::Motor>{pros::Motor(lFPort, MOTOR_GEAR_200, false), motorP, motorI, motorD},
    createPID<pros::Motor>{pros::Motor(lMPort, MOTOR_GEAR_600, true), motorP, motorI, motorD},
    createPID<pros::Motor>{pros::Motor(lRPort, MOTOR_GEAR_600, true), motorP, motorI, motorD}
};

const int32_t &averageMotors::getEncoders() {
    const int32_t &averageEncoderValue = (
        (motors.rF.readInput.get_position() * 3) +
         motors.rM.readInput.get_position() +
          motors.rR.readInput.get_position() +
           (motors.lF.readInput.get_position() * 3) +
            motors.lM.readInput.get_position() +
             motors.lR.readInput.get_position()
             ) / 6;

    return averageEncoderValue;
}

createPID<averageMotors> autoPID = createPID<averageMotors>{drivebaseMotors, autoP, autoI, autoD};

 createPID<pros::Rotation> puncherRotation = createPID<pros::Rotation> {
    pros::Rotation(rotationPort, false), rotationP, rotationI, rotationD
};

 createPID<pros::Imu> inertialPID = createPID<pros::Imu>{pros::Imu(inertialPort), inertialP, inertialI, inertialD};

pros::Motor liftMotor(liftPort, MOTOR_GEAR_100, true);
pros::Motor puncher(puncherPort, MOTOR_GEAR_100, false);
pros::Motor intake(intakePort, MOTOR_GEAR_200, false);

makeToggleable<pros::ADIDigitalOut> rightWing = makeToggleable<pros::ADIDigitalOut>{pros::ADIDigitalOut(rightPneumaticPort)};
makeToggleable<pros::ADIDigitalOut> leftWing = makeToggleable<pros::ADIDigitalOut>{pros::ADIDigitalOut(leftPneumaticPort)};
