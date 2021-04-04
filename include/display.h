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
void checkEntrBtn();
void FuncBtn();
void printText(float num);
int checkPotentiometer();

#endif