#include "main.h"

void setPneumatic(const bool &rightState, const bool &leftState) {
    rightWing.controlledItem.set_value(rightState);
    leftWing.controlledItem.set_value(leftState);
}

void setClip(const bool &state) {
    clip.controlledItem.set_value(state);
}

/*
Driver Controls
*/

void inverseWing()  {
    rightWing.state = !rightWing.state;
    leftWing.state = !leftWing.state;

    setPneumatic(rightWing.state, leftWing.state);
}

void inverseRight()  {
    rightWing.state = !rightWing.state;

    setPneumatic(rightWing.state, leftWing.state);
}

void inverseLeft()  {
    leftWing.state = !leftWing.state;

    setPneumatic(rightWing.state, leftWing.state);
}

void inverseClip() {
    clip.state = !clip.state;

    setClip(clip.state);
}
