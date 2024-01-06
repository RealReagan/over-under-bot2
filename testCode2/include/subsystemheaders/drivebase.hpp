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
