#include "main.h"

void setPneumatic() {

}

/*
Driver Controls
*/

void inverseWing()  {
    rightWing.state = !rightWing.state;
    leftWing.state = !leftWing.state;

    setPneumatic(rightWing.state, leftWing.state);
}
