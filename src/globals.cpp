#include "Main.h"
#include "Globals.h"

volatile bool stepperEnabled    = false;
long lastBtnRead                = 0;
long lastBtnPress               = 0;
long lastPotRead                = 0;
int stepperSpeed                = 500;
float stepperRpm                = 0.00;
float prevStepperRpm            = 0.00;
int stepperDirection            = -1;
menu menuPage                   = photo;


void setMenuPage(menu page) {
    menuPage = page;
}


menu getMenuPage() {
    return menuPage;
}


void setStepperEnabled(bool enabled) {
    stepperEnabled = enabled;
    if (enabled) {
        stepper.enableOutputs();
    }
    else if (!enabled) {
        stepper.disableOutputs();
    }
}


bool isStepperEnabled() {
    return stepperEnabled;
}


void setLastBtnRead(long lastRead) {
    lastBtnRead = lastRead;
}


long getLastBtnRead() {
    return lastBtnRead;
}


void setLastBtnPress(long lastPress) {
    lastBtnPress = lastPress;
}


long getLastBtnPress() {
    return lastBtnPress;
}


void setLastPotRead(long lastRead) {
    lastPotRead = lastRead;
}


long getLastPotRead() {
    return lastPotRead;
}


void setStepperSpeed(int speed) {
    stepperSpeed = speed;
}


int getStepperSpeed() {
    return stepperSpeed;
}


void setStepperRpm(float rpm) {
    stepperRpm = rpm;
}


float getStepperRpm() {
    return stepperRpm;
}


void setPrevStepperRpm(float rpm) {
    prevStepperRpm = rpm;
}


float getPrevStepperRpm() {
    return prevStepperRpm;
}


void setStepperDirection(int dir) {
    stepperDirection = dir;
}


int getStepperDirection() {
    return stepperDirection;
}