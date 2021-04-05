#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <AccelStepper.h>
#include <TMC2130Stepper.h>
#include "Main.h"
#include "Globals.h"
#include "Display.h"
#include "Photo.h"
#include "Video.h"
#include "Stepper.h"

#ifdef __arm__
    // should use uinstd.h to define sbrk but Due causes a conflict
    extern "C" char* sbrk(int incr);
#else  // __ARM__
    extern char *__brkval;
#endif  // __arm__

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

    // stepper.move(10);
    stepper.setSpeed(getStepperSpeed()*getStepperDirection());
    attachInterrupt(digitalPinToInterrupt(FUNC_BTN), FuncBtnInterrupt, RISING);

    setDisplaySettings();
    introScreen();
}


void loop() {
    checkEntrBtn();
    checkFuncBtn();
    if (getMenuPage() == photo) {
        //
    }
    else if (getMenuPage() == photo_num) {
        setPhotoCount();
    }
    else if (getMenuPage() == photo_delay) {
        setPhotoDelay();
    }
    else if (getMenuPage() == photo_trigger) {
        setPhotoTrigger();
    }
    // else if (getMenuPage() == photo_start) {
    // }
    else if (getMenuPage() == photo_progress) {
        photo360();
        if (isPhoto360Active()) {
            stepper.runSpeed();
        }
    }
    // else if (getMenuPage() == video) {
    // }
    else if (getMenuPage() == video_speed) {
        stepper.runSpeed();
        calcStepperSpeed();
    }
    if (millis() % 200 == 0) {Serial.println(freeMemory());}
}

 
int freeMemory() {
    char top;
#ifdef __arm__
    return &top - reinterpret_cast<char*>(sbrk(0));
#elif defined(CORE_TEENSY) || (ARDUINO > 103 && ARDUINO != 151)
    return &top - __brkval;
#else  // __arm__
    return __brkval ? &top - __brkval : &top - __malloc_heap_start;
#endif  // __arm__
}