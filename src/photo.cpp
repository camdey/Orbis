#include "Photo.h"
#include "Main.h"
#include "Interface.h"
#include "Globals.h"

#define arraySize 17
int photoCountArray[] = {6, 8, 9, 10, 12, 15, 18, 20, 24, 30, 36, 40, 45, 60, 72, 90, 120};
int prevNumPhotos = 0;
int prevPhotoDelay = 0;
bool prevShutterActiveState = false;


void setPhotoCountOption() {
    int potVal = getAvgReading();
    // map pot values to index of array holding photo counts
    int arrayIndex = map(potVal, 0, 1022, 0, arraySize-1);
    int numPhotos = photoCountArray[arrayIndex];
    if (numPhotos != prevNumPhotos) {
        setPhotoCount(numPhotos);
        // calculate number of microsteps to move for each photo, will truncate to int
        int nrSteps = (NR_STEPS*NR_MICROSTEPS) / getPhotoCount();
        setStepsPerMovement(nrSteps);
        photoNumScreen(getPhotoCount());
        prevNumPhotos = getPhotoCount();
    }
}


void setPhotoDelayOption() {
    int potVal = getAvgReading();
    // map pot values from 100ms to 10000ms (0.6s to 10s)
    int delay = map(potVal, 0, 1022, 6, 100)*100;
    if (delay != prevPhotoDelay) {
        setPhotoDelay(delay);
        photoDelayScreen(getPhotoDelay());
        prevPhotoDelay = getPhotoDelay();
    }
}


void setShutterReleaseOption() {
    int potVal = getAvgReading();
    int val = map(potVal, 0, 1022, 0, 10);
    bool shutterActive;
    if (val < 5) {
        shutterActive = true;
    }
    else if (val >= 5) {
        shutterActive = false;
    }
    if (shutterActive != prevShutterActiveState) {
        setShutterRelease(shutterActive);
        shutterReleaseScreen();
        prevShutterActiveState = isShutterReleaseEnabled();
    }
}


void photo360() {
    // 0 - if start of new photo360, set speed, take first photo, and enable stepper
    if (getPhotoProgress() == 0 && !isPhoto360Active()) {
        stepper.setSpeed(300);
        setStepperEnabled(true);
        releaseShutter(true);
        // Serial.print(F("3. shutter state: ")); Serial.println(digitalRead(SHUTTER_PIN));
        delay(SHUTTER_DELAY);
        // reset target position
        // stepper.move(0);
    }

    // 1 - if photo360 incomplete and stepper is currently paused mid-step
    if (getPhotoProgress() < getPhotoCount() && !isPhoto360Active()) {
        // 1b - check if delay period has been exceeded, if so set new target for next movement
        if (millis() - getLastPhoto360Step() >= getPhotoDelay()) {
            stepper.move(getStepsPerMovement());
            stepper.setSpeed(300);
            setPhoto360Active(true);
        }
        // keep checking if time needed to release shutter has been exceeded, if so reset shutter release
        releaseShutter(false);
        // Serial.print(F("2. shutter state: ")); Serial.println(digitalRead(SHUTTER_PIN));
    }

    // 2 - if target set and not reached, step towards target position
    if (isPhoto360Active() && !isPhoto360Paused()) {
        stepper.runSpeed();
    }


    // 3 - if we reached the target position, release shutter, reset flags, and increment and update progress
    if (isPhoto360Active() && stepper.currentPosition() == stepper.targetPosition()) {
        setPhoto360Active(false);
        setPhotoProgress(getPhotoProgress()+1);
        photoProgressScreen();
        setLastPhoto360Step(millis());

        // 3b - only release shutter if not at end of photo360
        if (getPhotoProgress() < getPhotoCount()) {
            releaseShutter(true);
            // Serial.print(F("1. shutter state: ")); Serial.println(digitalRead(SHUTTER_PIN));
        }
    }
}


void releaseShutter(bool initRelease) {
    // only take photos if enabled
    if(isShutterReleaseEnabled()) {
        // start taking a photo
        if (initRelease) {
            // if shutter not released, release it
            if (!isShutterReleased()) {
                digitalWrite(SHUTTER_PIN, HIGH);
                setShutterReleased(true);
                setShutterReleaseStart(millis());
            }
        }
        // if it has been released, wait until delay exceeded
        if (isShutterReleased()) {
            // wait for shutter to be released
            if (millis() - getShutterReleaseStart() >= SHUTTER_DELAY) {
                digitalWrite(SHUTTER_PIN, LOW);
                setShutterReleased(false);
            }
        }
    }
}


void photoScreen() {
    display.clearDisplay();
    display.setTextSize(4);
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


void shutterReleaseScreen() {
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0,0);
    display.println(F("Trigger?"));
    display.setTextSize(3);
    display.setCursor(40, 40);
    if (isShutterReleaseEnabled()) {
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