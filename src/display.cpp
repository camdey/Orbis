#include "Main.h"
#include "Display.h"
#include "Globals.h"


void introScreen() {
    display.clearDisplay();
    display.setTextSize(5);
    display.setTextColor(SSD1306_WHITE);  // Draw white text
    display.setCursor(5,0);               // Start at top-left corner
    display.cp437(true);                  // Use full 256 char 'Code Page 437' font
    display.println("Welcome...");
    display.display();
    delay(1000);
    setMenuPage('photo');
    photoScreen();
}


void photoScreen() {
    display.clearDisplay();
    display.setTextSize(5);
    display.setCursor(5,0);
    display.println("Photo");
    display.display();
}


void photoNumScreen() {
    display.clearDisplay();
    display.setTextSize(5);
    display.setCursor(5,0);
    display.println("Nr Photos:");
    display.display();
}


void photoDelayScreen() {
    display.clearDisplay();
    display.setTextSize(5);
    display.setCursor(5,0);
    display.println("Delay:");
    display.display();
}


void photoTriggerScreen() {
    display.clearDisplay();
    display.setTextSize(5);
    display.setCursor(5,0);
    display.println("Trigger:");
    display.display();
}


void photoStartScreen() {
    display.clearDisplay();
    display.setTextSize(5);
    display.setCursor(5,0);
    display.println("Start?");
    display.display();
}


void photoProgressScreen() {
    display.clearDisplay();
    display.setTextSize(5);
    display.setCursor(5,0);
    display.println("Progress:");
    display.display();
}


void videoScreen() {
    display.clearDisplay();
    display.setTextSize(5);
    display.setCursor(5,0);
    display.println("Progress:");
    display.display();
    // disable stepper
    if (isStepperEnabled()) {
        setStepperEnabled(false);
    }
}


void videoSpeedScreen() {
    display.clearDisplay();
    display.setTextSize(5);
    display.setCursor(5,0);
    display.println("Progress:");
    display.display();
    // enable stepper
    if (!isStepperEnabled()) {
        setStepperEnabled(true);
    }
}


void printText(float num) {
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


void FuncBtn() {
    if (millis() - getLastBtnPress() >= 250) {
        if (getMenuPage() == 'photo') {
            // nothing
        }
        else if (getMenuPage() == 'photo_num') {
            // go back a page
            setMenuPage('photo');
            photoScreen();
        }
        else if (getMenuPage() == 'photo_delay') {
            // go back a page
            setMenuPage('photo_num');
            photoNumScreen();
            // reset photo num?
        }
        else if (getMenuPage() == 'photo_trigger') {
            // go back a page
            setMenuPage('photo_delay');
            photoDelayScreen();
            // reset photo delay?
        }
        else if (getMenuPage() == 'photo_start') {
            // go back a page
            setMenuPage('photo_trigger');
            photoTriggerScreen();
        }
        else if (getMenuPage() == 'photo_progress') {
            // go back a page
            setMenuPage('photo_start');
            photoStartScreen();
            // reset progress
            // go back to starting position
        }
        else if (getMenuPage() == 'video') {
            // nothing
        }
        else if (getMenuPage() == 'video_speed') {
            // go back a page
            setMenuPage('video');
            videoScreen();
        }
        setLastBtnPress(millis());
    }
}


void checkEntrBtn() {
    if (millis() - getLastBtnRead() >= 50) {
        if (millis() - getLastBtnPress() >= 250) {
            if (getMenuPage() == 'photo') {
                setMenuPage('photo_num');
                photoNumScreen();
            }
            else if (getMenuPage() == 'photo_num') {
                setMenuPage('photo_delay');
                photoDelayScreen();
            }
            else if (getMenuPage() == 'photo_delay') {
                setMenuPage('photo_trigger');
                photoTriggerScreen();
            }
            else if (getMenuPage() == 'photo_trigger') {
                setMenuPage('photo_start');
                photoStartScreen();
            }
            else if (getMenuPage() == 'photo_start') {
                setMenuPage('photo_progress');
                photoProgressScreen();
            }
            else if (getMenuPage() == 'photo_progress') {
                
            }
            else if (getMenuPage() == 'video') {
                setMenuPage('video_speed');
                videoSpeedScreen();
            }
            else if (getMenuPage() == 'video_speed') {
                // change direction
                if (digitalRead(ENTR_BTN) == true) {
                    setStepperDirection(getStepperDirection()*-1); // invert direction
                }
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