#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>

enum menu {
  photo,
  photo_num,
  photo_delay,
  photo_trigger,
  photo_start,
  photo_progress,
  video,
  video_speed
};

void setMenuPage(menu page);
menu getMenuPage();
void setStepperEnabled(bool enabled);
bool isStepperEnabled();
void setLastBtnRead(long lastRead);
long getLastBtnRead();
void setLastBtnPress(long lastPress);
long getLastBtnPress();
void setLastPotRead(long lastRead);
long getLastPotRead();
void setStepperDirection(int dir);
int getStepperDirection();
void setPhotoCount(int count);
int getPhotoCount();
void setPhotoDelay(int delay);
int getPhotoDelay();
void setPhotoTrigger(bool trigger);
int isPhotoTriggerEnabled();
void setPhotoProgress(int progress);
int getPhotoProgress();
void setPhoto360Active(bool active);
bool isPhoto360Active();
void setLastPhoto360Step(long lastStep);
long getLastPhoto360Step();
void pausePhoto360(bool pause);
bool isPhoto360Paused();


#endif