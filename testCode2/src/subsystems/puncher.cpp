#include "main.h"

#define puncherSpeed 127

/*
Helper functions
*/
void spinPuncher(const float& speed) {
    puncher = speed;
}

/*
Driver controls
*/

void puncherToggle() {
    bool isMoving = puncher.get_actual_velocity() != 0;
    spinPuncher(puncherSpeed * isMoving);
}

/*
Automatic functions
*/

