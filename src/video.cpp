#include "Video.h"


// void loop() {
//   if (isStepperEnabled()) {
//     stepper.runSpeed();
//   }
//   calcStepperSpeed();
//   checkEntrBtn();
// }


// int getAvgReading() {
//   valuesTotal = valuesTotal - potValues[readIndex];
//   potValues[readIndex] = checkPotentiometer();
//   valuesTotal = valuesTotal + potValues[readIndex];
//   readIndex = readIndex + 1;
//   if (readIndex >= numReadings) {
//     readIndex = 0;
//   }
//   valuesAvg = valuesTotal / numReadings;

//   return valuesAvg;
// }


// void calcStepperSpeed() {
//   if (millis() - getLastPotRead() >= 20) {
//     setStepperSpeed(getAvgReading());
//     stepper.setSpeed(getStepperSpeed()*getStepperDirection());
//     setLastPotRead(millis());
//     setStepperRpm(round(map(getStepperSpeed(), 0, MAX_SPEED, 0, MAX_RPM*100)/10.00)/10.00); // convert to 0-500, divide by 10 and round, divide by 10
//     if (getStepperRpm() != getPrevStepperRpm()) {
//       setPrevStepperRpm(getStepperRpm());
//       printText(getStepperRpm());
//     }
//   }
// }


// int checkPotentiometer() {
//   int potVal = analogRead(POT_PIN);
//   potVal = map(potVal, 1023, 0, 0, MAX_SPEED);
//   return potVal;
// }

// void printText(float num) {
//   display.clearDisplay();
//   display.setTextSize(5);
//   display.setTextColor(SSD1306_WHITE);  // Draw white text
//   display.setCursor(5,0);               // Start at top-left corner
//   display.cp437(true);                  // Use full 256 char 'Code Page 437' font
//   display.println(num);
//   display.setTextSize(3);
//   display.setCursor(70,40);
//   display.println("RPM");
//   display.display();
// }

// void FuncBtn() {
//   if (millis() - getLastBtnPress() >= 250) {
//     setStepperEnabled(!isStepperEnabled());
//     if (isStepperEnabled()) {
//       stepper.enableOutputs();
//     }
//     else if (!isStepperEnabled()) {
//       stepper.disableOutputs();
//     }
//     setLastBtnPress(millis());
//   }
// }


// void checkEntrBtn() {
//   if (millis() - getLastBtnRead() >= 50) {
//     if (digitalRead(ENTR_BTN) == true  && millis() - getLastBtnPress() >= 250) {
//       setStepperDirection(getStepperDirection()*-1); // invert direction
//       setLastBtnPress(millis());
//     }
//     setLastBtnRead(millis());
//   }
// }