#ifndef PHOTO_H
#define PHOTO_H

#include <Arduino.h>


void setPhotoCount();
void setPhotoDelay();
void setPhotoTrigger();
void photoScreen();
void photoNumScreen(int num);
void photoDelayScreen(int delay);
void photoTriggerScreen();
void photoStartScreen();
void photoProgressScreen();
void photo360();

#endif