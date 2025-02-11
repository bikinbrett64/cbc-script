/**
  This file contains the logic and variables defining the overall behavior of the system.

  Author: Brett Warren
*/

#include "button.h"

// Pin definitions.
#define UP_BUTTON 15
#define DOWN_BUTTON 4
#define LEFT_BUTTON 18
#define RIGHT_BUTTON 5
#define MAG_SENSOR 13

// Timing constants.
#define FRAME_DURATION_MS 200
#define MAG_SENSOR_DEBOUNCE_DELAY_US 5000
#define BUTTON_BRIEF_PRESS_MS 200
#define BUTTON_HOLD_DELAY_MS 1000
#define REPEAT_ACTION_DELAY_MS 200

// For tracking whether the program is recording data, displaying the menu, etc.
enum PROGRAM_STATE {
  SETUP,
  MONITOR,
  MENU
} programState = MONITOR;

// For tracking the time elapsed since the last frame was printed.
unsigned long frameTimer;

// For detecting an overflow of micros().
volatile unsigned long mostRecentInput = 0;

// Variables related to the magnetic sensor.
volatile unsigned long lastMagSensorClose = 0;
volatile unsigned long lastMagSensorOpen = 0;
volatile bool magSensorClosed = false;

// Instantiating the buttons.
button up;
button down;
button left;
button right;

// Any additional buttons can be declared here.

void setup() {
  Serial.begin(115200);
  Serial.println("Starting up.");

  up.pin = UP_BUTTON;
  down.pin = DOWN_BUTTON;
  left.pin = LEFT_BUTTON;
  right.pin = RIGHT_BUTTON;

  //Wire.begin();

  // TODO: Implement SD card reading/writing.

  // TODO: Perform unit tests(?).

  // Enabling the pullup resistors.
  pinMode(up.pin, INPUT_PULLUP);
  pinMode(down.pin, INPUT_PULLUP);
  pinMode(left.pin, INPUT_PULLUP);
  pinMode(right.pin, INPUT_PULLUP);
  pinMode(MAG_SENSOR, INPUT_PULLUP);

  // Attaching interrupts.
  attachInterrupt(up.pin, recordUpButtonPress, FALLING);
  attachInterrupt(down.pin, recordDownButtonPress, FALLING);
  attachInterrupt(left.pin, recordLeftButtonPress, FALLING);
  attachInterrupt(right.pin, recordRightButtonPress, FALLING);

  attachInterrupt(up.pin, recordUpButtonRelease, RISING);
  attachInterrupt(down.pin, recordDownButtonRelease, RISING);
  attachInterrupt(left.pin, recordLeftButtonRelease, RISING);
  attachInterrupt(right.pin, recordRightButtonRelease, RISING);

  attachInterrupt(MAG_SENSOR, recordMagSensorClose, FALLING);  // The magnetic sensor is handled a bit differently.
  attachInterrupt(MAG_SENSOR, recordMagSensorOpen, RISING);

  frameTimer = millis();
}

void loop() {
  BUTTON_STATE upStatus, downStatus, leftStatus, rightStatus;
  upStatus = queryButton(&up);
  downStatus = queryButton(&down);
  leftStatus = queryButton(&left);
  rightStatus = queryButton(&right);

  if (upStatus == PRESS) {
    Serial.println("up");
  }
  if (downStatus == PRESS) {
    Serial.println("down");
  }
  if (leftStatus == PRESS) {
    Serial.println("left");
  }
  if (rightStatus == PRESS) {
    Serial.println("right");
  }

  switch (programState) {
    case SETUP:
      // TODO: Ask the user for wheel diameter (and maybe other things).
      break;
    case MONITOR:
      break;
    case MENU:
      // TODO: Implement a menu system (this will likely involve the SD card).
      break;
  }
}

bool microsOverflow() {
  return micros() < mostRecentInput;
}

// ISR - records a press of the up button.
void recordUpButtonPress() {
  recordButtonPress(&up);
}

// ISR - records a press of the down button.
void recordDownButtonPress() {
  recordButtonPress(&down);
}

// ISR - records a press of the left button.
void recordLeftButtonPress() {
  recordButtonPress(&left);
}

// ISR - records a press of the right button.
void recordRightButtonPress() {
  recordButtonPress(&right);
}

// ISR - records a release of the up button.
void recordUpButtonRelease() {
  recordButtonRelease(&up);
}

// ISR - records a release of the down button.
void recordDownButtonRelease() {
  recordButtonRelease(&down);
}

// ISR - records a release of the left button.
void recordLeftButtonRelease() {
  recordButtonRelease(&left);
}

// ISR - records a release of the right button.
void recordRightButtonRelease() {
  recordButtonRelease(&right);
}

// ISR - records a closing of the magnetic sensor.
void recordMagSensorClose() {
  mostRecentInput = lastMagSensorClose = micros();
  magSensorClosed = true;
}

// ISR - records an opening of the magnetic sensor.
void recordMagSensorOpen() {
  mostRecentInput = lastMagSensorOpen = micros();
  magSensorClosed = false;
}

// Helper function - this is called whenever a button's pin goes low.
void recordButtonPress(button* b) {
  mostRecentInput = b->lastPress = micros();
  b->buttonDown = true;
}

// Helper function - this is called whenever a button's pin goes high.
void recordButtonRelease(button* b) {
  mostRecentInput = b->lastRelease = micros();
  b->buttonDown = false;
  if (micros() > b->lastPress + BUTTON_DEBOUNCE_DELAY_US) {
    b->pressHandled = false;
  }
}
