/**
  This file contains the logic and variables defining the overall behavior of the system.

  Author: Brett Warren
*/

// Pin definitions.
#define UP_BUTTON 15
#define DOWN_BUTTON 4
#define LEFT_BUTTON 18
#define RIGHT_BUTTON 5
#define MAG_SENSOR 13

// Timing constants.
#define FRAME_DURATION_MS 200
#define BUTTON_DEBOUNCE_DELAY_MS 5
#define MAG_SENSOR_DEBOUNCE_DELAY_MS 5
#define BUTTON_BRIEF_PRESS_MS 200
#define BUTTON_HOLD_DELAY_MS 1000
#define REPEAT_ACTION_DELAY_MS 200

// For tracking whether the program is recording data, displaying the menu, etc.
enum PROGRAM_STATES {
  SIMPLE
} programState = SIMPLE;

// For tracking the time elapsed since the last frame was printed.
unsigned long frameTimer;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting up.");

  Wire.begin();

  // TODO: Implement SD card reading/writing.

  // Assigning pins for the inputs.
  pinMode(UP_BUTTON, INPUT_PULLUP);
  pinMode(DOWN_BUTTON, INPUT_PULLUP);
  pinMode(LEFT_BUTTON, INPUT_PULLUP);
  pinMode(RIGHT_BUTTON, INPUT_PULLUP);
  pinMode(MAG_SENSOR, INPUT_PULLUP);

  frameTimer = millis();
}

void loop() {
  // TODO: Everything else.
}
