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
enum PROGRAM_STATE {
  SETUP,
  MONITOR,
  MENU
} programState = MONITOR;

// For tracking the status of a given button.
enum BUTTON_STATE {
  PRESS,
  RELEASE,
  PENDING
};

// For tracking the time elapsed since the last frame was printed.
unsigned long frameTimer;

// Variables related to the buttons.
volatile unsigned long lastUpButtonPress = 0;
volatile unsigned long lastDownButtonPress = 0;
volatile unsigned long lastLeftButtonPress = 0;
volatile unsigned long lastRightButtonPress = 0;
volatile unsigned long lastUpButtonRelease = 0;
volatile unsigned long lastDownButtonRelease = 0;
volatile unsigned long lastLeftButtonRelease = 0;
volatile unsigned long lastRightButtonRelease = 0;

// For detecting an overflow of micros().
volatile unsigned long mostRecentInput = 0;

// Variables related to the magnetic sensor.
volatile unsigned long lastMagSensorClose = 0;
volatile unsigned long lastMagSensorOpen = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting up.");

  Wire.begin();

  // TODO: Implement SD card reading/writing.

  // TODO: Perform unit tests.

  // Enabling the pullup resistors.
  pinMode(UP_BUTTON, INPUT_PULLUP);
  pinMode(DOWN_BUTTON, INPUT_PULLUP);
  pinMode(LEFT_BUTTON, INPUT_PULLUP);
  pinMode(RIGHT_BUTTON, INPUT_PULLUP);
  pinMode(MAG_SENSOR, INPUT_PULLUP);

  frameTimer = millis();
}

void loop() {
  switch (programState) {
    case SETUP:
      // TODO: Ask the user for wheel diameter (and maybe other things)
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

void queryButtons(BUTTON_STATE* up, BUTTON_STATE* down, BUTTON_STATE* left, BUTTON_STATE* right) {
  unsigned long timeStamp = micros();
  
  
}

// ISR - records a press of the up button.
void recordUpButtonPress() {
  mostRecentInput = lastUpButtonPress = micros();
}

// ISR - records a press of the down button.
void recordDownButtonPress() {
  mostRecentInput = lastDownButtonPress = micros();
}

// ISR - records a press of the left button.
void recordLeftButtonPress() {
  mostRecentInput = lastLeftButtonPress = micros();
}

// ISR - records a press of the right button.
void recordRightButtonPress() {
  mostRecentInput = lastRightButtonPress = micros();
}

// ISR - records a release of the up button.
void recordUpButtonRelease() {
  mostRecentInput = lastUpButtonRelease = micros();
}

// ISR - records a release of the down button.
void recordDownButtonRelease() {
  mostRecentInput = lastDownButtonRelease = micros();
}

// ISR - records a release of the left button.
void recordLeftButtonRelease() {
  mostRecentInput = lastLeftButtonRelease = micros();
}

// ISR - records a release of the right button.
void recordRightButtonRelease() {
  mostRecentInput = lastRightButtonRelease = micros();
}

// ISR - records a closing of the magnetic sensor.
void recordMagSensorClose() {
  mostRecentInput = lastMagSensorClose = micros();
}

// ISR - records an opening of the magnetic sensor.
void recordMagSensorOpen() {
  mostRecentInput = lastMagSensorOpen = micros();
}
