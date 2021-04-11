#include "Main.h"
#include "Interface.h"
#include "Globals.h"
#include "Photo.h"
#include "Video.h"

// flag to keep track if funcBtn was triggered during interrupt
bool funcBtnTriggered = false;
int potValues[NUM_READINGS];    // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int valuesTotal = 0;            // the running total
int valuesAvg = 0;              // the average


void introScreen() {
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0,0);               // Start at top-left corner
    display.println(F("Welcome..."));
    display.display();
    delay(1000);
    setMenuPage(photo);
    photoScreen();
}


void FuncBtnInterrupt() {
    funcBtnTriggered = true;
}


void checkFuncBtn() {
    if (funcBtnTriggered && millis() - getLastBtnPress() >= 250) {
        if (getMenuPage() == photo) {
            // go to video page
            setMenuPage(video);
            videoScreen();
        }
        else if (getMenuPage() == photo_num) {
            // go back a page
            setMenuPage(photo);
            photoScreen();
        }
        else if (getMenuPage() == photo_delay) {
            // go back a page
            setMenuPage(photo_num);
            photoNumScreen(getPhotoCount());
            // reset photo num?
        }
        else if (getMenuPage() == photo_trigger) {
            // go back a page
            setMenuPage(photo_delay);
            photoDelayScreen(getPhotoDelay());
            // reset photo delay?
        }
        else if (getMenuPage() == photo_start) {
            // go back a page
            setMenuPage(photo_trigger);
            shutterReleaseScreen();
        }
        else if (getMenuPage() == photo_progress) {
            // go back a page
            setMenuPage(photo_start);
            photoStartScreen();
            // reset photo360
            setPhotoProgress(0);
            stepper.setMaxSpeed(MAX_SPEED);
            // go back to starting position??
        }
        else if (getMenuPage() == video) {
            // go to photo page
            setMenuPage(photo);
            photoScreen();
        }
        else if (getMenuPage() == video_speed) {
            // go back a page
            setMenuPage(video);
            videoScreen();
        }
        setLastBtnPress(millis());
        funcBtnTriggered = false;
    }
}


void checkEntrBtn() {
    if (millis() - getLastBtnRead() >= 50) {
        if (digitalRead(ENTR_BTN) == true && millis() - getLastBtnPress() >= 250) {
            if (getMenuPage() == photo) {
                setMenuPage(photo_num);
                photoNumScreen(getPhotoCount());
            }
            else if (getMenuPage() == photo_num) {
                setMenuPage(photo_delay);
                photoDelayScreen(getPhotoDelay());
            }
            else if (getMenuPage() == photo_delay) {
                setMenuPage(photo_trigger);
                shutterReleaseScreen(); 
            }
            else if (getMenuPage() == photo_trigger) {
                setMenuPage(photo_start);
                photoStartScreen();
            }
            else if (getMenuPage() == photo_start) {
                setMenuPage(photo_progress);
                photoProgressScreen();
                pausePhoto360(false); //unpause if paused
            }
            else if (getMenuPage() == photo_progress) {
                pausePhoto360(!isPhoto360Paused());
            }
            else if (getMenuPage() == video) {
                setMenuPage(video_speed);
                videoSpeedScreen();
            }
            else if (getMenuPage() == video_speed) {
                // change direction
                setStepperDirection(getStepperDirection()*-1); // invert direction
            }
            setLastBtnPress(millis());
        }
        setLastBtnRead(millis());
    }
}


int checkPotentiometer() {
    if (millis() - getLastPotRead() >= 20) {
        int potVal = analogRead(POT_PIN);
        return potVal;
        setLastPotRead(millis());
    }
}


void initAvgArray() {
    for (int i = 0; i < NUM_READINGS; i++) {
        potValues[i] = 0;
    }
}


int getAvgReading() {
    valuesTotal = valuesTotal - potValues[readIndex];
    int potVal = checkPotentiometer();
    potVal = map(potVal, 1023, 0, 0, 1023);
    potValues[readIndex] = potVal;

    valuesTotal = valuesTotal + potValues[readIndex];
    readIndex = readIndex + 1;
    if (readIndex >= NUM_READINGS) {
        readIndex = 0;
    }
    valuesAvg = valuesTotal / NUM_READINGS;

    return valuesAvg;
}


void setDisplaySettings() {
    display.setTextSize(5);
    display.setTextColor(SSD1306_WHITE);    // Draw white text
    display.cp437(true);    // Use full 256 char 'Code Page 437' font
}