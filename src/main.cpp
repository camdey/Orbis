#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <AccelStepper.h>                      // software stepping implementation
#include <TMC2130Stepper.h>                   // stepper driver library
//#include <IRremote.h>


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
//#define REMOTE_PIN    5

#define MAX_RPM       5
#define NR_MICROSTEPS 32
#define MAX_SPEED     533 // 200 steps * 32 microsteps = 6400 / 5rpm = 533


TMC2130Stepper  driver    = TMC2130Stepper(EN_PIN, DIR_PIN, STEP_PIN, CS_PIN);
AccelStepper    stepper   = AccelStepper(stepper.DRIVER, STEP_PIN, DIR_PIN);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);
//IRrecv irRemote(REMOTE_PIN); //create a new instance of receiver
//
//decode_results remoteValue;

volatile bool stepperEnabled = false; // off by default
volatile unsigned long lastBtnRead = 0;
volatile unsigned long lastBtnPress = 0;
unsigned long lastPotRead = 0;
int stepperSpeed = 500;
float rpm = 0.00;
float prev_rpm = 0.00;
int dir = -1;

const int numReadings = 5;
int potValues[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int valuesTotal = 0;            // the running total
int valuesAvg = 0;          // the average

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

//  irRemote.enableIRIn(); //init the remote receiver
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
  printText(rpm);
  
  stepper.move(10);
  stepper.setSpeed(stepperSpeed*dir);
  attachInterrupt(digitalPinToInterrupt(FUNC_BTN), FuncBtn, RISING);
}

void loop() {
  if (stepperEnabled) {
    stepper.runSpeed();
  }
  setStepperSpeed();
  checkEntrBtn();

//  if (irRemote.decode(&remoteValue)) { //we have received an IR
//    Serial.println (remoteValue.value, HEX); //display HEX
//    irRemote.resume(); //next value
//  }
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


void setStepperSpeed() {
  if (millis() - lastPotRead >= 20) {
    stepperSpeed = getAvgReading();
    stepper.setSpeed(stepperSpeed*dir);
    lastPotRead = millis();
    float rpm = round(map(stepperSpeed, 0, MAX_SPEED, 0, MAX_RPM*100)/10.00)/10.00; // convert to 0-500, divide by 10 and round, divide by 10
    if (rpm != prev_rpm) {
      prev_rpm = rpm;
      printText(rpm);
    }
  }
}


int checkPotentiometer() {
  int potVal = analogRead(POT_PIN);
  potVal = map(potVal, 1023, 0, 0, MAX_SPEED);
//  Serial.print("Pot val: "); Serial.println(potVal);
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
  if (millis() - lastBtnPress >= 250) {
    stepperEnabled = !stepperEnabled;
    if (stepperEnabled) {
      stepper.enableOutputs();
    }
    else if (!stepperEnabled) {
      stepper.disableOutputs();
    }
    lastBtnPress = millis();
  }
}


void checkEntrBtn() {
  if (millis() - lastBtnRead >= 50) {
    if (digitalRead(ENTR_BTN) == true  && millis() - lastBtnPress >= 250) {
      dir = dir*-1; // invert direction
      lastBtnPress = millis();
    }
    lastBtnRead = millis();
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
//    driver.chopper_mode(0);
//    driver.stealth_max_speed(0x0002F);
//    driver.double_edge_step(1);
//    driver.chopper_mode(1);
//    driver.sync_phases(1);
}
