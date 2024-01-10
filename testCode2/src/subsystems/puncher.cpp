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
    bool isMoving = puncher.is_stopped();
    if(isMoving) {
        spinPuncher(0);
        return;
    }
    spinPuncher(puncherSpeed);
}

/*
Automatic functions
*/

