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
        (adjustedValues.rF ),
        (adjustedValues.rM ),
        (adjustedValues.rR ),
        (adjustedValues.lF ),
        (adjustedValues.lM ),
        (adjustedValues.lR )
    );

}

/*
Auto Controls
*/
#define errorTolerance 80
#define curveErrorTolerance 20
#define turnErrorTolerance 1

void PIDTranslate(const float &valueChange, const float &degreeChange, const float maxSpeed, const int maxTime) {
    const float target = autoPID.readInput.getEncoders() + valueChange;
    const float degreeTarget = inertialPID.readInput.get_rotation() + degreeChange;

    float straightValue = autoPID.PIDAdjust(target);
    float turnValue = inertialPID.PIDAdjust(degreeTarget);

    int straightDirection = (straightValue > 0) ? 1: -1;
    int turnDirection = (turnValue > 0) ? 1: -1;
    if (fabs(valueChange) != 0) {
        int time = 0;
        while ((fabs(autoPID.readInput.getEncoders() - target) > errorTolerance || fabs(inertialPID.readInput.get_rotation() - degreeTarget) > turnErrorTolerance) && time < maxTime) {
            enforceMaxSpeedGeneral(&straightValue, &turnValue, maxSpeed);
            PIDMotorSet(straightValue, turnValue);

            straightValue = autoPID.PIDAdjust(target);
            turnValue = inertialPID.PIDAdjust(degreeTarget);

            time += 10;
            pros::delay(10);
        }
    }
    else {
        while (fabs(inertialPID.readInput.get_rotation() - degreeTarget) > turnErrorTolerance) {
            turnValue = inertialPID.PIDAdjust(degreeTarget);
            straightValue = 0;
            enforceMaxSpeedGeneral(&straightValue, &turnValue, maxSpeed);
            spinMotors (
                -turnValue,
                -turnValue,
                -turnValue,
                turnValue,
                turnValue,
                turnValue
            );
            pros::delay(10);
        }
    }
    int stopTime = 0;
    if(degreeChange == 0) {
        while (stopTime < 200) {
            PIDMotorSet(0,0);
            stopTime += 20;
            pros::delay(20);
        }
    }
    spinMotors(0,0,0,0,0,0);
}

void curveTurn(const float &rightTarget, const float& leftTarget, const float maxSpeed) {
    float rightValue = rightPID.PIDAdjust(rightTarget);
    float leftValue = leftPID.PIDAdjust(leftTarget);
    while(fabs(rightPID.readInput.getEncoders() - rightTarget) > curveErrorTolerance || fabs(leftPID.readInput.getEncoders() - leftTarget) > curveErrorTolerance) {
        enforceMaxSpeedCurves(&rightValue, &leftValue, maxSpeed);
        spinMotors(
            rightValue, rightValue, rightValue, leftValue, leftValue, leftValue
        );

        rightValue = rightPID.PIDAdjust(rightTarget);
        leftValue = leftPID.PIDAdjust(leftTarget);


        pros::delay(10);
    }
    int time = 0;
    while (time < 200) {
            PIDMotorSet(0,0);
            time += 20;
            pros::delay(20);
    }
    spinMotors(0,0,0,0,0,0);
}

/*
Calculations
*/
const adjustedMotors calcPIDMotors(const float& rightTar, const float& leftTar) {
    const float &twoRight  = (drivebaseMotors.rF.PIDAdjust(rightTar * 200/127.0) * (127/200.0));
    const float &sixRight  = (drivebaseMotors.rM.PIDAdjust(rightTar * 600/127.0) * (127/600.0));
    const float &twoLeft  = (drivebaseMotors.lF.PIDAdjust(leftTar * 200/127.0) * (127/200.0));
    const float &sixLeft  = (drivebaseMotors.lM.PIDAdjust(leftTar * 600/127.0) * (127/600.0));
    const auto& adjustedValues = adjustedMotors{
        rightTar + twoRight,
        rightTar + sixRight,
        rightTar + sixRight,
        leftTar + twoLeft,
        leftTar + sixLeft,
        leftTar + sixLeft
    };

    return adjustedValues;
}

void enforceMaxSpeedGeneral(float* straightValue, float* turnValue, const float maxSpeed) {
    int straightDirection = (*straightValue > 0) ? 1: -1;
    int turnDirection = (*turnValue > 0) ? 1: -1;
    if(fabs(*straightValue + *turnValue) > maxSpeed || fabs(*straightValue - *turnValue) > maxSpeed) {
        float turnRatio = fabs(*turnValue / (fabs(*turnValue) + fabs(*straightValue)));
        float straightRatio = fabs(*straightValue / (fabs(*straightValue) + fabs(*turnValue)));
        *turnValue = turnDirection * turnRatio * maxSpeed;
        *straightValue = straightDirection * straightRatio * maxSpeed;
    }
}

void enforceMaxSpeedCurves(float* rightValue, float* leftValue, const float maxSpeed) {
    int rightDirection = (*rightValue > 0) ? 1: -1;
    int leftDirection = (*leftValue > 0) ? 1: -1;
    if(fabs(*rightValue) > maxSpeed || fabs(*leftValue) > maxSpeed) {
        float leftRatio = fabs(*leftValue / (fabs(*leftValue) + fabs(*rightValue)));
        float rightRatio = fabs(*rightValue / (fabs(*rightValue) + fabs(*leftValue)));
        *leftValue = leftDirection * fabs(leftRatio * maxSpeed);
        *rightValue = rightDirection * fabs(rightRatio * maxSpeed);
    }
}

void execCurveTurn(const float &turnDegrees, const float &radiusInches, const int &direction, const float maxSpeed) {
    const float &turnRadians = turnDegrees * ((2 * PI)/360.0);
    
    const float &rightTargetRad = PI * (radiusInches - (direction * DISTANCERIGHT));
    const float &leftTargetRad = PI * (radiusInches + (direction * DISTANCELEFT));

    const float &rightTargetTicks = (rightTargetRad * (TICKSPERROTATION / (2 * PI)));
    const float &leftTargetTicks = (leftTargetRad * (TICKSPERROTATION / (2 * PI)));

    curveTurn(rightTargetTicks, leftTargetTicks, maxSpeed);
}
