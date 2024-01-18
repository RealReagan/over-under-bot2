#include "main.h"

/*
Helpers
*/
void spinLift(int32_t speed){
    liftMotor = speed;
}
/*
Driver functions
*/
#define liftSpeed 127
void setLift(int32_t shouldSpin){
    spinLift(liftSpeed *  shouldSpin);
}