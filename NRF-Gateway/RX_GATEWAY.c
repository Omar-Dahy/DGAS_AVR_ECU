#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>

RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00002";

#define ledPin A0

int lastSentI2C = -1;

void setup() {
  Serial.begin(9600);
  Wire.begin(); // I2C Master
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  int receivedData = -1;
  if (radio.available()) {
    radio.read(&receivedData, sizeof(receivedData));
    Serial.print("Received from TX: ");
    Serial.println(receivedData);

    // LED control
    if (receivedData == 5) {
      digitalWrite(ledPin, HIGH);
    } else {
      digitalWrite(ledPin, LOW);
    }

    // Determine value to send via I2C
    int toSend = (receivedData == 5) ? 20 : 0;

    if (toSend != lastSentI2C) {
      Wire.beginTransmission(8);
      Wire.write(toSend);
      Wire.endTransmission();
      Serial.print("Sent to Arduino 3 via I2C: ");
      Serial.println(toSend);
      lastSentI2C = toSend;
    }
  }
}
