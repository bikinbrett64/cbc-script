/**
  This file contains the logic and variables for the computer's internal computations.

  Author: Brett Warren
*/

int wheelCircumference = 2199;
long wheelTurns = 0;

/// Returns a trip distance in millimeters.
long getTrip(int circumference, long turns) {
  return circumference * turns;
}

/// Returns a speed in millimeters per second.
long getSpeed(int circumference, long firstTurn, long nextTurn) {
  return 1000 * circumference / (nextTurn - firstTurn);
}