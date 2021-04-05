#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>

void introScreen();
void FuncBtnInterrupt();
void checkFuncBtn();
void checkEntrBtn();
void initAvgArray();
int getAvgReading();
int checkPotentiometer();
void setDisplaySettings();

#endif