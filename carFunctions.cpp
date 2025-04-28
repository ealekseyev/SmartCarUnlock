#ifndef _CARFUNC_CPP_
#define _CARFUNC_CPP_

#include <Arduino.h>

const int fetPin = 16;

void initCarFunctions() {
  pinMode(fetPin, INPUT);
  pinMode(2, INPUT);
}

void unlockCar() {
  Serial.println("Unlocking Vehicle");
  digitalWrite(2, 1);
  digitalWrite(fetPin, 1);
  delay(100);
  digitalWrite(2, 0);
  digitalWrite(fetPin, 0);
}

#endif
