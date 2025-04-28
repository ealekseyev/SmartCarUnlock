#include "RFID.h"
#include "knock.h"
#include "carFunctions.h"

bool unlock = false;

void setup() {
  Serial.begin(115200);
  initCarFunctions();
  RFIDInit();
  knockSSInit();
}

long lastUnlock = -1000;
long nowTime = 0;
void loop() {
  runKnockDetection(&unlock);
  checkRFID(&unlock);
  nowTime = millis();
  if(unlock && (nowTime - lastUnlock) > 4000) {
    unlockCar();
    lastUnlock = millis();
  }
  unlock = false;
}