#include "main.h"

void setPneumatic(const bool &rightState, const bool &leftState) {
    rightWing.controlledItem.set_value(rightState);
    leftWing.controlledItem.set_value(leftState);
}

/*
Driver Controls
*/

void inverseWing()  {
    rightWing.state = !rightWing.state;
    leftWing.state = !leftWing.state;

    setPneumatic(rightWing.state, leftWing.state);
}
