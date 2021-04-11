#include "Main.h"
#include "Globals.h"

volatile bool stepperEnabled    = false;
long lastBtnRead                = 0;
long lastBtnPress               = 0;
long lastPotRead                = 0;
int stepperDirection            = -1;
int photoCount                  = 6;
int photoDelay                  = 100;
bool shutterReleaseEnabled               = false;
int photoProgress               = 0;
bool photo360Active             = false;
long lastPhoto360Step           = 0;
bool photo360Paused             = false;
menu menuPage                   = photo;
bool shutterReleased            = false;
long shutterReleaseStart        = 0;
int stepsPerMovements           = 0;


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


void setShutterRelease(bool enable) {
    shutterReleaseEnabled = enable;
}


int isShutterReleaseEnabled() {
    return shutterReleaseEnabled;
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


bool isPhoto360Active() {
    return photo360Active;
}


void setLastPhoto360Step(long lastStep) {
    lastPhoto360Step = lastStep;
}


long getLastPhoto360Step() {
    return lastPhoto360Step;
}


void pausePhoto360(bool pause) {
    photo360Paused = pause;
}


bool isPhoto360Paused() {
    return photo360Paused;
}


void setShutterReleased(bool released) {
    shutterReleased = released;
}


bool isShutterReleased() {
    return shutterReleased;
}


void setShutterReleaseStart(long started) {
    shutterReleaseStart = started;
}


long getShutterReleaseStart() {
    return shutterReleaseStart;
}


void setStepsPerMovement(int steps) {
    stepsPerMovements = steps;
}


long getStepsPerMovement() {
    return stepsPerMovements;
}