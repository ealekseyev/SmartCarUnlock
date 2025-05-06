#ifndef _KNOCK_CPP_
#define _KNOCK_CPP_

#include <Arduino.h>
// preset
int delayDurations[6] = {
  200, 85, 60, 220, 450, 200
};

int delayShifter[6] = {
  0, 0, 0, 0, 0, 0
};

// global variables to use
int delayCount = 6;
long touchOffStart, touchOffDelay;
bool lastState = 0;
long lastKnock;

void knockSSInit() {
  pinMode(13, OUTPUT);
  delay(100);
  digitalWrite(13, 1);
  lastState = 0;
  lastKnock = millis();
  analogReadResolution(12);
}

void shiftDelays(int* toshift, int insert) {
  for(int i = 0; i < delayCount-1; i++) {
    toshift[i] = toshift[i+1];
  }
  toshift[delayCount-1] = insert;
}

bool matchesKnock(int* _delayShifter) {
  float totalDiff = 0;
  //Serial.print(" (");
  bool retFalse = false;
  for(int i = 0; i < delayCount; i++) {
    float difference = abs(1.0 - (float) _delayShifter[i] / (float)delayDurations[i]);
    if(difference > 0.8) retFalse = true;
    // Serial.print(difference);
    // Serial.print(" ");
    totalDiff += difference;
  }
  totalDiff /= delayCount;
  // Serial.print(" , average: " + String(totalDiff) + ")");
  if(retFalse) {
    return false;
  }
  return totalDiff < 0.6;
}

unsigned long lastDebounceTime = 0;  // Last time the input was toggled
const unsigned long debounceDelay = 40;  // Minimum time between valid state changes (ms)

void runKnockDetection(bool* unlock) {
  int curState = analogRead(12) < 3500;
  unsigned long currentTime = millis();

  // Debounce logic: only allow state change if enough time has passed
  if (curState != lastState && (currentTime - lastDebounceTime) > debounceDelay) {
    lastDebounceTime = currentTime;

    if (curState == 0 && lastState == 1) {
      touchOffStart = currentTime;
      lastState = curState;
    } else if (curState == 1 && lastState == 0) {
      touchOffDelay = currentTime - touchOffStart;

      shiftDelays(delayShifter, touchOffDelay);
      Serial.print(" knock ");

      if (matchesKnock(delayShifter)) {
        *unlock = true;
        Serial.println(" Matches Knock!");
      }
      lastState = curState;
    }
  }
}

#endif