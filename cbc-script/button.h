/**
  Just a header for handling buttons.

  Author: Brett Warren
*/

#define BUTTON_DEBOUNCE_DELAY_US 5000
#define BUTTON_DEBOUNCE_DELAY_MS 5
#define BUTTON_HOLD_DELAY_US 1000000
#define BUTTON_HOLD_DELAY_MS 1000

// For tracking the status of a given button.
enum BUTTON_STATE {
  PRESS,
  RELEASE,
  WAIT,
  HOLD
};

// For defining a button.
struct button {
  int pin = -1;
  volatile unsigned long lastPress = 0;
  volatile unsigned long lastRelease = 0;
  volatile bool buttonDown = false;
  volatile bool pressHandled = true;
};

/// Returns a debounced query of the given button.
BUTTON_STATE queryButton(button* b) {
  if (b->buttonDown) {
    if (!(b->pressHandled)) {
      b->pressHandled = true;
      return PRESS;
    }
    if (millis() > b->lastPress + BUTTON_HOLD_DELAY_MS) {
      return HOLD;
    }
    return WAIT;
  }
  return RELEASE;
}

/*
class button {
private:
  bool buttonDown = false;
  unsigned long lastPress = 0;
  unsigned long lastRelease = 0;

public:
  button(int pin) {
    pinMode(pin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(pin), recordButtonPress, FALLING);
    attachInterrupt(digitalPinToInterrupt(pin), recordButtonRelease, RISING);
  }

  /// Returns a debounced query of the button.
  BUTTON_STATE queryButton() {
    unsigned long timeStamp = micros();
    if (buttonDown) {
      if (timeStamp - lastPress > BUTTON_DEBOUNCE_DELAY_US) {
        return PRESS;
      }
      return WAIT;
    }
    return RELEASE;
  }

  /// ISR - updates relevant values upon a press of the button.
  void recordButtonPress() {
    lastPress = micros();
  }

  /// ISR - updates relevant values upon a release of the button.
  void recordButtonRelease() {
    lastRelease = micros();
  }
};
*/