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
