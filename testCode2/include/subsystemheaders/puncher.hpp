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
//Toggle spinning of puncher
extern void puncherToggle();

/*
Automatic functions
*/
