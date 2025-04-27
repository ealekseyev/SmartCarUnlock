#include "knock.cpp"
#include "carFunctions.cpp"
#include "RFID.cpp"

bool unlock = false;

void setup() {
  Serial.begin(115200);
  RFIDInit();
}
void loop() {
  runKnockDetection(&unlock);
  checkRFID(&unlock);
  if(unlock) {
    unlockCar();
    unlock = false;
  }
}