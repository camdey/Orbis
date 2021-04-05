#ifndef MAIN_H
#define MAIN_H

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <AccelStepper.h>
#include <TMC2130Stepper.h>

extern TMC2130Stepper    driver;
extern AccelStepper      stepper;
extern Adafruit_SSD1306  display;

#define SCREEN_WIDTH    128 // OLED display width, in pixels
#define SCREEN_HEIGHT   64 // OLED display height, in pixels
#define POT_PIN         A3
#define FUNC_BTN        2
#define OPTO_PIN        3
#define ENTR_BTN        4
#define CS_PIN          10
#define DIR_PIN         9
#define STEP_PIN        8
#define EN_PIN          7

#define MAX_RPM         5
#define NR_STEPS        200
#define NR_MICROSTEPS   32
#define MAX_SPEED       533 // 200 steps * 32 microsteps = 6400 / 5rpm = 533
#define NUM_READINGS    5


int freeMemory();

#endif