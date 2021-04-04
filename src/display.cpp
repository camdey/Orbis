#include "Main.h"
#include "Display.h"
#include "Globals.h"

// flag to keep track if funcBtn was triggered during interrupt
bool funcBtnTriggered = false;


void introScreen() {
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);  // Draw white text
    display.setCursor(5,0);               // Start at top-left corner
    display.cp437(true);                  // Use full 256 char 'Code Page 437' font
    display.println(F("Welcome..."));
    display.display();
    delay(1000);
    setMenuPage(photo);
    photoScreen();
}


void photoScreen() {
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(5,0);
    display.println(F("Photo"));
    display.display();
}


void photoNumScreen() {
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(5,0);
    display.println(F("Nr Photos:"));
    display.display();
}


void photoDelayScreen() {
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(5,0);
    display.println(F("Delay:"));
    display.display();
}


void photoTriggerScreen() {
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(5,0);
    display.println(F("Trigger:"));
    display.display();
}


void photoStartScreen() {
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(5,0);
    display.println(F("Start?"));
    display.display();
}


void photoProgressScreen() {
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(5,0);
    display.println(F("Progress:"));
    display.display();
}


void videoScreen() {
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(5,0);
    display.println(F("Video"));
    display.display();
    // disable stepper
    if (isStepperEnabled()) {
        setStepperEnabled(false);
    }
}


void videoSpeedScreen() {
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(5,0);
    display.println(F("Progress:"));
    display.display();
    // enable stepper
    if (!isStepperEnabled()) {
        setStepperEnabled(true);
    }
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
            photoNumScreen();
            // reset photo num?
        }
        else if (getMenuPage() == photo_trigger) {
            // go back a page
            setMenuPage(photo_delay);
            photoDelayScreen();
            // reset photo delay?
        }
        else if (getMenuPage() == photo_start) {
            // go back a page
            setMenuPage(photo_trigger);
            photoTriggerScreen();
        }
        else if (getMenuPage() == photo_progress) {
            // go back a page
            setMenuPage(photo_start);
            photoStartScreen();
            // reset progress
            // go back to starting position
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
                photoNumScreen();
            }
            else if (getMenuPage() == photo_num) {
                setMenuPage(photo_delay);
                photoDelayScreen();
            }
            else if (getMenuPage() == photo_delay) {
                setMenuPage(photo_trigger);
                photoTriggerScreen();
            }
            else if (getMenuPage() == photo_trigger) {
                setMenuPage(photo_start);
                photoStartScreen();
            }
            else if (getMenuPage() == photo_start) {
                setMenuPage(photo_progress);
                photoProgressScreen();
            }
            else if (getMenuPage() == photo_progress) {
                
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
    int potVal = analogRead(POT_PIN);
    potVal = map(potVal, 1023, 0, 0, MAX_SPEED);
    return potVal;
}