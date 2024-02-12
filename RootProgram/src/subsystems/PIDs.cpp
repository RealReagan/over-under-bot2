#include "main.h"

#define INTEGRALTHRESHOLD 25
#define INTEGRALMAX 127
#define ERRORMAX 127
#define RPMTOVOLT (127/600)

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
    return PIDCalculations.proport(target, sensorReading);
}

template <> const float createPID<averageMotors>::PIDAdjust(const float& target) {
    float sensorReading = readInput.getEncoders();
    float returnValue = PIDCalculations.proport(target, sensorReading);
    return returnValue;
}

template <> const float createPID<splitMotors>::PIDAdjust(const float& target) {
    float sensorReading = readInput.getEncoders();
    float returnValue = PIDCalculations.proport(target, sensorReading);
    return returnValue;
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
    if (fabs(error) > INTEGRALTHRESHOLD) {
        integral = 0;
    }
    return (kI * integral) + derive(error);
}

const float calcPID::derive(const float& error) {
    if(lastError != 0) {
        derivative = error - lastError;
    }
    lastError = error;
    return (kD * derivative);
}
