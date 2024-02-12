#include "main.h"

struct calcPID {
    float kP;
    float kI;
    float kD;
    float integral = 0;
    float derivative = 0;
    float lastError = 0;
    //finds error in motor speed to target
    const float proport(const float& target, const float& speed);
    //finds total value of accumulated error(integral)
    const float integrate(const float& error);
    //finds immediate change in error(derivative)
    const float derive(const float& error);
};

//create struct for unique motor cmds on puncher
template <class inputType> struct createPID {
    inputType readInput;
    const float kP;
    const float kI;
    const float kD;
    calcPID PIDCalculations = calcPID{kP , kI, kD};
    //returns value to spin motor according to PID adjusment
    const float PIDAdjust(const float& target);
};

extern float ERRORMAX;
