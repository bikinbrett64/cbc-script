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
  attachInterrupt(digitalPinToInterrupt(up.pin), recordUpButtonInteraction, CHANGE);
  attachInterrupt(digitalPinToInterrupt(down.pin), recordDownButtonInteraction, CHANGE);
  attachInterrupt(digitalPinToInterrupt(left.pin), recordLeftButtonInteraction, CHANGE);
  attachInterrupt(digitalPinToInterrupt(right.pin), recordRightButtonInteraction, CHANGE);

  attachInterrupt(MAG_SENSOR, recordMagSensorClose, FALLING);  // The magnetic sensor is handled a bit differently.

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

// ISR - records an interaction with the up button.
void recordUpButtonInteraction() {
  recordButtonInteraction(&up);
}

// ISR - records an interaction with the down button.
void recordDownButtonInteraction() {
  recordButtonInteraction(&down);
}

// ISR - records an interaction with the left button.
void recordLeftButtonInteraction() {
  recordButtonInteraction(&left);
}

// ISR - records an interaction with the right button.
void recordRightButtonInteraction() {
  recordButtonInteraction(&right);
}

// ISR - records a closing of the magnetic sensor.
void recordMagSensorClose() {
  mostRecentInput = lastMagSensorClose = millis();
  magSensorClosed = true;
}

// Helper function - this is called whenever a button is pressed/released.
void recordButtonInteraction(button* b) {
  bool isPressed = !digitalRead(b->pin);
  if (isPressed) {
    b->buttonDown = true;
    if (millis() > b->lastRelease + BUTTON_DEBOUNCE_DELAY_MS) {
      b->pressHandled = false;
      mostRecentInput = b->lastPress = millis();
    }
  } else {
    b->buttonDown = false;
    mostRecentInput = b->lastRelease = millis();
  }
}
