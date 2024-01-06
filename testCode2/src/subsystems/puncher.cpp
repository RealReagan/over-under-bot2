#include "main.h"

#define puncherSpeed 127 * .80

/*
Helper functions
*/
void spinPuncher(const float& speed) {
    puncher = speed;
}

/*
Driver controls
*/
#define restingPosition 0

void PIDPuncherSet() {
    const int32_t& distance = restingPosition - puncherRotation.sensor.get_position();
    puncherRotation.PIDAdjust(float(distance));
}

void puncherToggle(bool shouldSpin) {
    spinPuncher(shouldSpin * puncherSpeed);
}

/*
Automatic functions
*/

/*
functions in targetPID
*/
#define kP 0
#define kI 0
#define kD 0
#define integralLimit 20

const float targetPID::PIDAdjust(const float& target) {
    const float& position = sensor.get_position();

    return target - proport(target, position);
}

const float targetPID::proport(const float& target, const float& position) {
    float error = target - position;
    if(fabs(error) > 127) {
        error = (error / fabs(error)) * 127;
    }

    return kP * error + integrate(error);
}

const float targetPID::integrate(const float& error) {
    integral = integral + error;

    if(fabs(error) > integralLimit) {
        integral = 0;
    }

    return kI * integral + derive(error);
}

const float targetPID::derive(const float& error) {
    const float derivative = error - lastError;

    return kD * derivative;
}
