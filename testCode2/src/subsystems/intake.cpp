#include "main.h"

/*
Helpers
*/
void spinIntake(int32_t speed){
    intake = speed;
}
/*
Driver functions
*/
#define intakeSpeed 127
void setIntake(int32_t shouldSpin){
    spinIntake(intakeSpeed *  shouldSpin);
}