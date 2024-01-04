#include "main.h"

/*
Helper functions
*/
//spin puncher according to given speed
extern void spinPuncher(const float& speed);

/*
Driver controls
*/
//use rotation and pid function to rotate puncher without locking into primed position
extern void PIDPuncherSet();

/*
Automatic functions
*/
//starter function to release the hold after a release has been pressed
extern void puncherRelease();

//create struct for unique motor cmds on puncher
struct puncherControl {
    pros::Motor motor;
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