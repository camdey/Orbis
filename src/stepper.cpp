#include "main.h"
#include "stepper.h"

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