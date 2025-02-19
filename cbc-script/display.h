/**
  This file contains the logic and variables to control the display.

  Author: Brett Warren
*/

#include <Custom_SSD1306.h>
#include <matrixFont.h>

enum UNITS {
  METRIC,
  IMPERIAL
} preferredUnit = METRIC;

Custom_SSD1306 display;

/// Prints a trip distance at the given coordinates with the format [UUUU.ss km] OR [UUUU.ss mi]. Takes a distance in millimeters.
void printTripDistance(int x, int y, char* output, unsigned long dist) {
  int wholeUnits = 0;
  int subUnits = 0;
  if (preferredUnit == METRIC) {
    wholeUnits = dist / 1000000;
    subUnits = (dist - wholeUnits) / 10000;
    output[0] = (wholeUnits / 1000) + '0';
    output[1] = ((wholeUnits / 100) % 10) + '0';
    output[2] = ((wholeUnits / 10) % 10) + '0';
    output[3] = (wholeUnits % 10) + '0';
    output[4] = '.';
    output[5] = subUnits / 10;
    output[6] = subUnits % 10;
    strncpy(output + 7, " km\0", 4);
  } else {
    // TODO: Implement imperial units properly.
    // For now, make it plainly obvious that this is not implemented.
    strncpy(output, "NO_IMP\0", 7);
  }
  display.drawString(x, y, output, &matrixFont, 1, WHITE);
}