#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define buttonPin 3

RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00002";

int lastSent = -1;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  int value = digitalRead(buttonPin);
  int dataToSend = (value == LOW) ? 5 : 0;

  if (dataToSend != lastSent) {
    radio.write(&dataToSend, sizeof(dataToSend));
    Serial.print("Sent: ");
    Serial.println(dataToSend);
    lastSent = dataToSend;
  }

  delay(100);  // reduce transmission frequency
}
