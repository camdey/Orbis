#include "Photo.h"
#include "Main.h"
#include "Interface.h"
#include "Globals.h"

#define arraySize 17
int photoCountArray[] = {6, 8, 9, 10, 12, 15, 18, 20, 24, 30, 36, 40, 45, 60, 72, 90, 120};
int prevNumPhotos = 0;
int prevPhotoDelay = 0;
bool prevTriggerState = false;


void setPhotoCount() {
    int potVal = getAvgReading();
    // map pot values to index of array holding photo counts
    int arrayIndex = map(potVal, 0, 1022, 0, arraySize-1);
    int numPhotos = photoCountArray[arrayIndex];
    if (numPhotos != prevNumPhotos) {
        setPhotoCount(numPhotos);
        photoNumScreen(getPhotoCount());
        prevNumPhotos = getPhotoCount();
    }
}


void setPhotoDelay() {
    int potVal = getAvgReading();
    // map pot values from 100ms to 10000ms (0.1s to 10s)
    int delay = map(potVal, 0, 1022, 1, 100)*100;
    if (delay != prevPhotoDelay) {
        setPhotoDelay(delay);
        photoDelayScreen(getPhotoDelay());
        prevPhotoDelay = getPhotoDelay();
    }
}


void setPhotoTrigger() {
    int potVal = getAvgReading();
    int val = map(potVal, 0, 1022, 0, 10);
    bool triggerCamera;
    if (val < 5) {
        triggerCamera = false;
    }
    else if (val >= 5) {
        triggerCamera = true;
    }
    if (triggerCamera != prevTriggerState) {
        setPhotoTrigger(triggerCamera);
        photoTriggerScreen();
        prevTriggerState = isPhotoTriggerEnabled();
    }
}


void photo360() {
    // calculate number of microsteps to move for each photo
    int stepsPerMovement = (NR_STEPS*NR_MICROSTEPS) / getPhotoCount();
    // init settings for photo360
    if (getPhotoProgress() == 0) {
        setStepperEnabled(true);
        stepper.setMaxSpeed(200);
        stepper.setSpeed(200);
    }
    // if progress less than required and we're not currently moving towards next target, set new target
    // but only set new target if delay has been exceeded
    if (getPhotoProgress() < getPhotoCount() && !isPhoto360Active()) {
        if (millis() - getLastPhoto360Step() >= getPhotoDelay()) {
            stepper.move(stepsPerMovement);
            setPhoto360Active(true);
        }
    }
    // if we reached the target position, reset flag and increment and update progress
    if (isPhoto360Active() && stepper.currentPosition() == stepper.targetPosition()) {
        setPhoto360Active(false);
        setPhotoProgress(getPhotoProgress()+1);
        photoProgressScreen();
        setLastPhoto360Step(millis());
    }
}


void photoScreen() {
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0,0);
    display.println(F("Photo"));
    display.display();
}


void photoNumScreen(int num) {
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0,0);
    display.println(F("Nr Photos:"));
    display.setTextSize(3);
    display.setCursor(40,40);
    display.println(num);
    display.display();
}


void photoDelayScreen(int delay) {
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0,0);
    display.println(F("Delay:"));
    display.setTextSize(3);
    display.setCursor(30,40);
    display.println(delay);
    display.display();
}


void photoTriggerScreen() {
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0,0);
    display.println(F("Trigger?"));
    display.setTextSize(3);
    display.setCursor(40, 40);
    if (isPhotoTriggerEnabled()) {
        display.println(F("YES"));
    }
    else {
        display.println(F("NO"));
    }
    display.display();
}


void photoStartScreen() {
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0,0);
    display.println(F("Start?"));
    display.display();
}


void photoProgressScreen() {
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0,0);
    display.println(F("Progress:"));
    char charProgress[10]  = "0/0";
    sprintf_P(charProgress, PSTR("%02d/%02d"), getPhotoProgress(), getPhotoCount());
    display.setTextSize(3);
    display.setCursor(10,40);
    display.println(charProgress);
    display.display();
}