#ifndef _RFID_CPP_
#define _RFID_CPP_

#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN    15 
#define SS_PIN     22

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance

void RFIDInit() {
	SPI.begin();
  mfrc522.PCD_Init();
  delay(4);
  Serial.println("RFID Initialized");
}

void checkRFID(bool* unlock) {
  if (!mfrc522.PICC_IsNewCardPresent()) {
		return;
	}
  if (!mfrc522.PICC_ReadCardSerial()) {
		return;
	}

  byte PSWBuff[] = {0x23, 0x9E, 0xDE, 0xD9};

  bool auth = true;
  for(int i = 0; i < 4; i++) {
    if(PSWBuff[i] != mfrc522.uid.uidByte[i]) {
      auth = false;
      break;
    }
  }
  if(auth) {
    //Serial.println("Card Accepted");
    *unlock = true;
    return;
  }
  //Serial.println("Card Rejected");
}
#endif