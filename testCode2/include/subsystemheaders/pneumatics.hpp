#include "main.h"

//Set pneumatic to given state
extern void setPneumatic(const bool &rightState,const bool &leftState);

extern void setClip(const bool &state);

/*
Driver Controls
*/

extern void inverseWing();
extern void inverseRight();
extern void inverseLeft();

extern void inverseClip();