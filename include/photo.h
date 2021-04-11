#ifndef PHOTO_H
#define PHOTO_H

#include <Arduino.h>


void setPhotoCountOption();
void setPhotoDelayOption();
void setShutterReleaseOption();
void photoScreen();
void photoNumScreen(int num);
void photoDelayScreen(int delay);
void shutterReleaseScreen();
void photoStartScreen();
void photoProgressScreen();
void photo360();
void releaseShutter(bool initRelease);

#endif