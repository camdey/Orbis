#include "Main.h"
#include "Globals.h"
#include "Display.h"
#include "Video.h"


int getAvgReading() {
    valuesTotal = valuesTotal - potValues[readIndex];
    potValues[readIndex] = checkPotentiometer();
    valuesTotal = valuesTotal + potValues[readIndex];
    readIndex = readIndex + 1;
    if (readIndex >= NUM_READINGS) {
        readIndex = 0;
    }
    valuesAvg = valuesTotal / NUM_READINGS;

    return valuesAvg;
}


void calcStepperSpeed() {
    if (millis() - getLastPotRead() >= 20) {
        setStepperSpeed(getAvgReading());
        stepper.setSpeed(getStepperSpeed()*getStepperDirection());
        setLastPotRead(millis());
        setStepperRpm(round(map(getStepperSpeed(), 0, MAX_SPEED, 0, MAX_RPM*100)/10.00)/10.00); // convert to 0-500, divide by 10 and round, divide by 10
        if (getStepperRpm() != getPrevStepperRpm()) {
            setPrevStepperRpm(getStepperRpm());
            printText(getStepperRpm());
        }
    }
}


void printSpeed(float num) {
  display.clearDisplay();
  display.setTextSize(5);
  display.setTextColor(SSD1306_WHITE);  // Draw white text
  display.setCursor(5,0);               // Start at top-left corner
  display.cp437(true);                  // Use full 256 char 'Code Page 437' font
  display.println(num);
  display.setTextSize(3);
  display.setCursor(70,40);
  display.println("RPM");
  display.display();
}