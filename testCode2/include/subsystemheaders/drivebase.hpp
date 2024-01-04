#include "main.h"

//Stuct which contains values for PID adjusted motors
struct adjustedMotors {
    float rF;
    float rM;
    float rR;
    float lF;
    float lM;
    float lR;

};

/*
Helper functions
*/
//spins motors according to each's given value
extern void spinMotors(const float& rFSpd, const float& rMSpd, const float& rRSpd, const float& lFSpd, const float& lMSpd, const float& lRSpd);

/*
Driver controls
*/
//finds PID values to spin motors given target
extern void PIDMotorSet(const float& vertTar, const float& latTar);

/*
Calculations
*/
//calculates values to spin motors at via. PID functionality
extern const adjustedMotors calcPIDMotors(const float& rightTar, const float& leftTar);

//create struct for unique motor cmds
struct motorControl{
    pros::Motor storedMotor;
    float integral;
    float lastError;
    //returns value to spin motor according to PID adjusment
    const float PIDAdjust(const float& target);
    //finds error in motor speed to target
    const float proport(const float& target, const float& speed);
    //finds total value of accumulated error(integral)
    const float integrate(const float& error);
    //finds immediate change in error(derivative)
    const float derive(const float& error);

};