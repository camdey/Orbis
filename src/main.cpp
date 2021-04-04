#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <AccelStepper.h>         // software stepping implementation
#include <TMC2130Stepper.h>       // stepper driver library
#include "Globals.h"
#include "Photo.h"
#include "Video.h"


#define SCREEN_WIDTH  128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define POT_PIN       A3
#define FUNC_BTN      2
#define OPTO_PIN      3
#define ENTR_BTN      4
#define CS_PIN        10
#define DIR_PIN       9
#define STEP_PIN      8
#define EN_PIN        7

#define MAX_RPM       5
#define NR_MICROSTEPS 32
#define MAX_SPEED     533 // 200 steps * 32 microsteps = 6400 / 5rpm = 533


TMC2130Stepper    driver    = TMC2130Stepper(EN_PIN, DIR_PIN, STEP_PIN, CS_PIN);
AccelStepper      stepper   = AccelStepper(stepper.DRIVER, STEP_PIN, DIR_PIN);
Adafruit_SSD1306  display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);


const int numReadings = 5;
int potValues[numReadings];   // the readings from the analog input
int readIndex = 0;            // the index of the current reading
int valuesTotal = 0;          // the running total
int valuesAvg = 0;            // the average


int getAvgReading();
void silentStepConfig();
void checkEntrBtn();
void FuncBtn();
void printText(float num);
int checkPotentiometer();
void calcStepperSpeed();


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
  
  for (int i = 0; i < numReadings; i++) {
    potValues[i] = 0;
  }

  driver.begin();
  driver.rms_current(707);
  driver.microsteps(NR_MICROSTEPS);
  driver.interpolate(1);

  stepper.setMaxSpeed(MAX_SPEED);
  stepper.setEnablePin(EN_PIN);
  stepper.setPinsInverted(false, false, true);
  stepper.enableOutputs();
  silentStepConfig();

  // Clear the buffer
  display.clearDisplay();
  printText(getStepperRpm());
  
  stepper.move(10);
  stepper.setSpeed(getStepperSpeed()*getStepperDirection());
  attachInterrupt(digitalPinToInterrupt(FUNC_BTN), FuncBtn, RISING);
}

void loop() {
  if (isStepperEnabled()) {
    stepper.runSpeed();
  }
  calcStepperSpeed();
  checkEntrBtn();
}


int getAvgReading() {
  valuesTotal = valuesTotal - potValues[readIndex];
  potValues[readIndex] = checkPotentiometer();
  valuesTotal = valuesTotal + potValues[readIndex];
  readIndex = readIndex + 1;
  if (readIndex >= numReadings) {
    readIndex = 0;
  }
  valuesAvg = valuesTotal / numReadings;

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


int checkPotentiometer() {
  int potVal = analogRead(POT_PIN);
  potVal = map(potVal, 1023, 0, 0, MAX_SPEED);
  return potVal;
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
    setStepperEnabled(!isStepperEnabled());
    if (isStepperEnabled()) {
      stepper.enableOutputs();
    }
    else if (!isStepperEnabled()) {
      stepper.disableOutputs();
    }
    setLastBtnPress(millis());
  }
}


void checkEntrBtn() {
  if (millis() - getLastBtnRead() >= 50) {
    if (digitalRead(ENTR_BTN) == true  && millis() - getLastBtnPress() >= 250) {
      setStepperDirection(getStepperDirection()*-1); // invert direction
      setLastBtnPress(millis());
    }
    setLastBtnRead(millis());
  }
}


// config for TMC2130
void silentStepConfig() {
  stepper.setAcceleration(2000);
  driver.push(); // reset registers
  driver.stealthChop(1);
  driver.stealth_autoscale(1);
  driver.stealth_gradient(0xF); // 1 to 15
  driver.interpolate(1);
  driver.coolstep_min_speed(0x0);
  driver.stealth_freq(0x0); // 0 or 1 for 16MHz
}