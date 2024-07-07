#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9 // Configurable, see typical pin layout above
#define SS_PIN 10 // Configurable, see typical pin layout above

MFRC522 rfid(SS_PIN, RST_PIN); // Create MFRC522 instance

void setup() {
  Serial.begin(9600); // Initialize serial communications with the PC
  SPI.begin();        // Init SPI bus
  rfid.PCD_Init();    // Init MFRC522
  Serial.println("Scan an RFID card...");
}

void loop() {
  // Look for new cards
  if ( ! rfid.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( ! rfid.PICC_ReadCardSerial()) {
    return;
  }

  // Show UID on serial monitor
  Serial.print("UID tag :");
  String content = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(rfid.uid.uidByte[i], HEX);
    content.concat(String(rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(rfid.uid.uidByte[i], HEX));
  }
  Serial.println();
  
  delay(1000); // Add a delay to prevent flooding the serial output
  rfid.PICC_HaltA(); // Halt PICC
}
