#include "Main.h"
#include "Globals.h"
#include "Interface.h"
#include "Video.h"

float prevStepperRpm = 0.00;


void calcStepperSpeed() {
    int speed = map(getAvgReading(), 0, 1023, 0, MAX_SPEED); 
    stepper.setSpeed(speed*getStepperDirection());
    float stepperRpm = round(map(speed, 0, MAX_SPEED, 0, MAX_RPM*100)/10.00)/10.00; // convert to 0-500, divide by 10 and round, divide by 10
    if (stepperRpm != prevStepperRpm) {
        prevStepperRpm = stepperRpm;
        printSpeed(stepperRpm);
    }
}


void printSpeed(float num) {
    display.clearDisplay();
    display.setCursor(0,0);
    display.println(num);
    display.setTextSize(3);
    display.setCursor(70,40);
    display.println(F("RPM"));
    display.display();
}


void videoScreen() {
    display.clearDisplay();
    display.setTextSize(4);
    display.setCursor(0,0);
    display.println(F("Video"));
    display.display();
    // disable stepper
    if (isStepperEnabled()) {
        setStepperEnabled(false);
    }
}


void videoSpeedScreen() {
    display.clearDisplay();
    display.setTextSize(3);
    display.setCursor(70,40);
    display.println(F("RPM"));
    display.display();
    // enable stepper
    if (!isStepperEnabled()) {
        setStepperEnabled(true);
    }
}