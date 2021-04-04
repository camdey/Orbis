#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>


void setStepperEnabled(bool enabled);
bool isStepperEnabled();
void setLastBtnRead(long lastRead);
long getLastBtnRead();
void setLastBtnPress(long lastPress);
long getLastBtnPress();
void setLastPotRead(long lastRead);
long getLastPotRead();
void setStepperSpeed(int speed);
int getStepperSpeed();
void setStepperRpm(float rpm);
float getStepperRpm();
void setPrevStepperRpm(float rpm);
float getPrevStepperRpm();
void setStepperDirection(int dir);
int getStepperDirection();


#endif