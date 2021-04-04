#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <AccelStepper.h>
#include <TMC2130Stepper.h>
#include "Main.h"
#include "Globals.h"
#include "Display.h"
#include "Photo.h"
#include "Video.h"
#include "Stepper.h"


TMC2130Stepper      driver      = TMC2130Stepper(EN_PIN, DIR_PIN, STEP_PIN, CS_PIN);
AccelStepper        stepper     = AccelStepper(stepper.DRIVER, STEP_PIN, DIR_PIN);
Adafruit_SSD1306    display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);


int potValues[NUM_READINGS];    // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int valuesTotal = 0;            // the running total
int valuesAvg = 0;              // the average


void setup() {
    Serial.begin(9600);
    SPI.begin();
    pinMode(FUNC_BTN, INPUT);
    pinMode(ENTR_BTN, INPUT);
    pinMode(EN_PIN, OUTPUT);
    digitalWrite(EN_PIN, LOW);
    pinMode(CS_PIN, OUTPUT);
    digitalWrite(CS_PIN, HIGH);
    pinMode(DIR_PIN, OUTPUT);
    digitalWrite(DIR_PIN, LOW);

    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
        Serial.println(F("SSD1306 allocation failed"));
        for(;;); // Don't proceed, loop forever
    }

    for (int i = 0; i < NUM_READINGS; i++) {
        potValues[i] = 0;
    }

    driver.begin();
    driver.rms_current(707);
    driver.microsteps(NR_MICROSTEPS);
    driver.interpolate(1);

    stepper.setMaxSpeed(MAX_SPEED);
    stepper.setEnablePin(EN_PIN);
    stepper.setPinsInverted(false, false, true);
    // disable stepper
    setStepperEnabled(false);
    silentStepConfig();

    // stepper.move(10);
    stepper.setSpeed(getStepperSpeed()*getStepperDirection());
    attachInterrupt(digitalPinToInterrupt(FUNC_BTN), FuncBtn, RISING);

    introScreen();
}


void loop() {
    checkEntrBtn();
    if (getMenuPage() == photo) {
        //
    }
    else if (getMenuPage() == photo_num) {
        //
    }
    else if (getMenuPage() == photo_delay) {
        //
    }
    else if (getMenuPage() == photo_trigger) {
        //
    }
    else if (getMenuPage() == photo_start) {
        //
    }
    else if (getMenuPage() == photo_progress) {
    //
    }
    else if (getMenuPage() == video) {
        //
    }
    else if (getMenuPage() == video_speed) {
        stepper.runSpeed();
        calcStepperSpeed();
    }
}