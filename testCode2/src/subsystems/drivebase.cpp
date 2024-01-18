#include "main.h"

/*
Helper functions
*/
void spinMotors(const float& rFSpd, const float& rMSpd, const float& rRSpd, const float& lFSpd, const float& lMSpd, const float& lRSpd) {
    drivebaseMotors.rF.readInput = rFSpd;
    drivebaseMotors.rM.readInput = rMSpd;
    drivebaseMotors.rR.readInput = rRSpd;
    drivebaseMotors.lF.readInput = lFSpd;
    drivebaseMotors.lM.readInput = lMSpd;
    drivebaseMotors.lR.readInput = lRSpd;

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

/*
Auto Controls
*/
#define errorTolerance 5 //in encoder Ticks
#define turnErrorTolerance 2 //in degrees

void PIDTranslate(const float &valueChange, const float & degreeChange) {
    const float &target = autoPID.readInput.getEncoders() + valueChange;
    float difference = autoPID.readInput.getEncoders() - target;

    const float &degreeTarget = inertialPID.readInput.get_rotation() + valueChange;
    float degreeDifference = inertialPID.readInput.get_rotation() - target;

    while (difference > errorTolerance && degreeDifference > turnErrorTolerance) {
        float straightValue = autoPID.PIDAdjust(target);
        float turnValue = inertialPID.PIDAdjust(degreeTarget);

        float rightValue = straightValue - turnValue;
        float leftValue = straightValue + turnValue;

        spinMotors(
            rightValue,
            rightValue,
            rightValue,
            leftValue,
            leftValue,
            leftValue
        );

        difference = autoPID.readInput.getEncoders() - target;
        degreeDifference = inertialPID.readInput.get_rotation() - target;
    }
}
/*
Calculations
*/
const adjustedMotors calcPIDMotors(const float& rightTar, const float& leftTar) {
    const auto& adjustedValues = adjustedMotors{
        drivebaseMotors.rF.PIDAdjust(rightTar),
        drivebaseMotors.rM.PIDAdjust(rightTar),
        drivebaseMotors.rR.PIDAdjust(rightTar),
        drivebaseMotors.lF.PIDAdjust(leftTar),
        drivebaseMotors.lM.PIDAdjust(leftTar),
        drivebaseMotors.lR.PIDAdjust(leftTar)
    };

    return adjustedValues;
}
