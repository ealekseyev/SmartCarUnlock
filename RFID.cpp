#include <SPI.h>
#include <MFRC522.h>
void RFIDInit() {
	SPI.begin();
  mfrc522.PCD_Init();
  delay(4);
}
void checkRFID(bool* unlock) {
  if (!mfrc522.PICC_IsNewCardPresent()) {
		return;
	}
  if (!mfrc522.PICC_ReadCardSerial()) {
		return;
	}
  mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
}