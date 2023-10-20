#include <Servo.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);

Servo myservo;

int servoPosition = 90;
bool servoActive = false; 
bool a = true;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  myservo.attach(3);  
}

void loop() {
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    Serial.println("RFID Card detected!");

    if (authenticateCard() && !servoActive) {
      Serial.println("Access granted. Rotating servo.");
      servoActive = true;
      rotateServo(a);
    } else {
      Serial.println("Access denied or servo already active.");
    }

    delay(2000);
  }

  
  if (servoActive && myservo.read() == 0) {
    Serial.println("Servo rotation complete. Waiting for the next card.");
    servoActive = false;
  }
}

bool authenticateCard() {
  byte allowedCard1[] = {0x2A, 0x65, 0x92, 0x76};
  byte allowedCard2[] = {0x1A, 0x20, 0xE1, 0x7E};
  return (arraysEqual(mfrc522.uid.uidByte, allowedCard1) || arraysEqual(mfrc522.uid.uidByte, allowedCard2));
}

void rotateServo(a) {
  if (a = true){
    for (int pos = myservo.read(); pos <= 180; pos += 1) {
      myservo.write(pos);
      delay(15);
    }
  }

  if (a = false){
    for (int pos = myservo.read(); pos >= 0; pos -= 1) {
      myservo.write(pos);
      delay(15);
    }
  }
  delay(1000); // Wait for a second
  a = false
}
  
bool arraysEqual(byte arr1[], byte arr2[]) {
  // Check if two arrays are equal
  for (int i = 0; i < sizeof(arr1); i++) {
    if (arr1[i] != arr2[i]) {
      return false;
    }
  }
  return true;
}

