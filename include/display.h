#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>

void introScreen();
void photoScreen();
void photoNumScreen();
void photoDelayScreen();
void photoTriggerScreen();
void photoStartScreen();
void photoProgressScreen();
void videoScreen();
void videoSpeedScreen();
void FuncBtnInterrupt();
void checkFuncBtn();
void checkEntrBtn();
int checkPotentiometer();

#endif