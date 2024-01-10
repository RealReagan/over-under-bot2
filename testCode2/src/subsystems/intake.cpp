#include "main.h"

/*
Helpers
*/
extern void spinIntake(int32_t speed){
    intake = speed;
}
/*
Driver functions
*/
#define intakeSpeed 127
extern void setIntake(int32_t shouldSpin){
    spinIntake(intakeSpeed *  shouldSpin);
}