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
int photoCount                  = 6;
int photoDelay                  = 100;
bool photoTrigger               = false;
int photoProgress               = 0;
bool photo360Active             = false;
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


void setPhotoCount(int count) {
    photoCount = count;
}


int getPhotoCount() {
    return photoCount;
}


void setPhotoDelay(int delay) {
    photoDelay = delay;
}


int getPhotoDelay() {
    return photoDelay;
}


void setPhotoTrigger(bool trigger) {
    photoTrigger = trigger;
}


int isPhotoTriggerEnabled() {
    return photoTrigger;
}


void setPhotoProgress(int progress) {
    photoProgress = progress;
}


int getPhotoProgress() {
    return photoProgress;
}


void setPhoto360Active(bool active) {
    photo360Active = active;
}


int isPhoto360Active() {
    return photo360Active;
}