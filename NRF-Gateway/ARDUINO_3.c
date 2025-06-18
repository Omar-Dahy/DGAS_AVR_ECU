#include <Wire.h>

volatile int receivedValue = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin(8);  // Slave address
  Wire.onReceive(receiveEvent);
}

void loop() {
  Serial.print("Received via I2C: ");
  Serial.println(receivedValue);
  delay(500);
}

void receiveEvent(int howMany) {
  if (howMany >= 1) {
    receivedValue = Wire.read();  // Read first byte only
  }
}
