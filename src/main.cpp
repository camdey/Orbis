#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <AccelStepper.h>
#include <TMC2130Stepper.h>
#include "Main.h"
#include "Globals.h"
#include "Interface.h"
#include "Photo.h"
#include "Video.h"
#include "Stepper.h"


TMC2130Stepper      driver      = TMC2130Stepper(EN_PIN, DIR_PIN, STEP_PIN, CS_PIN);
AccelStepper        stepper     = AccelStepper(stepper.DRIVER, STEP_PIN, DIR_PIN);
Adafruit_SSD1306    display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);


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
    pinMode(SHUTTER_PIN, OUTPUT);
    digitalWrite(SHUTTER_PIN, LOW);

    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
        Serial.println(F("SSD1306 allocation failed"));
        for(;;); // Don't proceed, loop forever
    }

    // fill array with 0s
    initAvgArray();

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

    // attach interrupt for function button
    attachInterrupt(digitalPinToInterrupt(FUNC_BTN), FuncBtnInterrupt, RISING);

    setDisplaySettings();
    introScreen();
}


void loop() {
    checkEntrBtn();
    checkFuncBtn();
    if (getMenuPage() == photo_num) {
        setPhotoCountOption();
    }
    else if (getMenuPage() == photo_delay) {
        setPhotoDelayOption();
    }
    else if (getMenuPage() == photo_trigger) {
        setShutterReleaseOption();
    }
    else if (getMenuPage() == photo_progress) {
        // (0) start photo360, (1) set new target, (2) step towards next position, or (3) pause and release shutter
        photo360();
    }
    else if (getMenuPage() == video_speed) {
        stepper.runSpeed();
        calcStepperSpeed();
    }
    // if (millis() % 1000 == 0) {
        // Serial.print(F("0. shutter state: ")); Serial.println(digitalRead(SHUTTER_PIN));
    // bool state = digitalRead(SHUTTER_PIN);
    // Serial.print(state);
    // digitalWrite(SHUTTER_PIN, !state);
    // delay(3000);
    // }
}