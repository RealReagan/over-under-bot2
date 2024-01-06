#include "main.h"

/*
Helper functions
*/
void spinMotors(const float& rFSpd, const float& rMSpd, const float& rRSpd, const float& lFSpd, const float& lMSpd, const float& lRSpd) {
    drivebaseMotors.rF.storedMotor = rFSpd;
    drivebaseMotors.rM.storedMotor = rMSpd;
    drivebaseMotors.rR.storedMotor = rRSpd;
    drivebaseMotors.lF.storedMotor = lFSpd;
    drivebaseMotors.lM.storedMotor = lMSpd;
    drivebaseMotors.lR.storedMotor = lRSpd;

}

/*
Driver controls
*/
void PIDMotorSet(const float& vertTar, const float& latTar) {
    const float& rightTar = vertTar - latTar;
    const float& leftTar = vertTar + latTar;

    auto adjustedValues = calcPIDMotors(rightTar, leftTar);

    spinMotors(
    adjustedValues.rF,
    adjustedValues.rM,
    adjustedValues.rR,
    adjustedValues.lF,
    adjustedValues.lM,
    adjustedValues.lR
    );

}

void inertialMotorSet(const float& target) {

    auto adjustedValues = inertialCalcPIDMotors(target);

    spinMotors(
    adjustedValues.rF,
    adjustedValues.rM,
    adjustedValues.rR,
    adjustedValues.lF,
    adjustedValues.lM,
    adjustedValues.lR
    );

}

const bool toggleTurnControl() {
    const auto shouldSpin = puncher.is_stopped();

    return !shouldSpin;    
}

/*
Calculations
*/
const adjustedMotors calcPIDMotors(const float& rightTar, const float& leftTar) {
    const auto& temp = adjustedMotors{
        drivebaseMotors.rF.PIDAdjust(rightTar),
        drivebaseMotors.rM.PIDAdjust(rightTar),
        drivebaseMotors.rR.PIDAdjust(rightTar),
        drivebaseMotors.lF.PIDAdjust(leftTar),
        drivebaseMotors.lM.PIDAdjust(leftTar),
        drivebaseMotors.lR.PIDAdjust(leftTar)
    };

    return temp;
}

const adjustedMotors inertialCalcPIDMotors(const float& target) {
    const auto& returnedValue = headingHold.PIDAdjust(target);

    const auto& temp = adjustedMotors{
        - returnedValue,
        - returnedValue,
        - returnedValue,
        returnedValue,
        returnedValue,
        returnedValue
    };

    return temp;
}

/*
Collection of functions used in speedPID
*/
#define kP 0
#define kI 0
#define kD 0

const float speedPID::PIDAdjust(const float& target) {
    const float& speed = storedMotor.get_actual_velocity();

    return target - proport(target, speed);
}

const float speedPID::proport(const float& target, const float& speed) {
    const float error = speed - target;

    return kP * error + integrate(error);
}

const float speedPID::integrate(const float& error) {
    integral = integral + error;

    if (fabs(integral) < 10) {
        integral = 0;
    }

    return kI * integral + derive(error);
}

const float speedPID::derive(const float& error) {
    const float derivative = error - lastError;

    return kD * derivative;
}

#define kPI .75
#define kII .1
#define kDI 0
#define integralLimit 10

const float targetPIDI::PIDAdjust(const float& target) {
    const float& position = sensor.get_rotation();

    return proport(target, position);
}

const float targetPIDI::proport(const float& target, const float& position) {
    float error = target - position;
    if(fabs(error) > 127) {
        error = (error / fabs(error)) * 127;
    }

    return kPI * error + integrate(error);
}

const float targetPIDI::integrate(const float& error) {
    integral = integral + error;

    if(fabs(error) > integralLimit) {
        integral = 0;
    }
    if(fabs(integral) > 100) {
        integral = integral/fabs(integral) * 100;
    }

    return kII * integral + derive(error);
}

const float targetPIDI::derive(const float& error) {
    const float derivative = error - lastError;

    return kD * derivative;
}