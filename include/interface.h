#ifndef INTERFACE_H
#define INTERFACE_H

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