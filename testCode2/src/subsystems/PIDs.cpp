#include "main.h"

#define INTEGRALTHRESHOLD 25
#define ERRORMAX 100
#define RPMTOVOLT 127/200

template <> const float createPID<pros::Rotation>::PIDAdjust(const float& target) {
    const float& sensorReading = readInput.get_position();
    return PIDCalculations.proport(target, sensorReading);
}

template <> const float createPID<pros::Imu>::PIDAdjust(const float& target) {
    const float& sensorReading = readInput.get_rotation();
    return PIDCalculations.proport(target, sensorReading);
}

template <> const float createPID<pros::Motor>::PIDAdjust(const float& target) {
    float sensorReading = readInput.get_actual_velocity();
    sensorReading *= RPMTOVOLT;
    return target + PIDCalculations.proport(target, sensorReading);
}

template <> const float createPID<averageMotors>::PIDAdjust(const float& target) {
    float sensorReading = readInput.getEncoders();
    return PIDCalculations.proport(target, sensorReading);
}


const float calcPID::proport(const float& target, const float& sensorReading) {
    float error = target - sensorReading;
    if (fabs(error) > ERRORMAX) {
        error = (error/fabs(error)) * ERRORMAX;
    }
    return (kP * error) + integrate(error);
}

const float calcPID::integrate(const float& error) {
    integral += error;
    if (error > INTEGRALTHRESHOLD) {
        integral = 0;
    }
    return kI * integral + derive(error);
}

const float calcPID::derive(const float& error) {
    const float& derivative = lastError - error;
    return kD * derivative;
}
