#include <Wire.h>  // Include the Wire library for I2C communication

volatile int receivedValue = 0;  // Variable to store the received value; 'volatile' because it’s changed inside an interrupt

void setup() {
  Serial.begin(9600);           // Initialize serial communication at 9600 baud for debugging
  Wire.begin(8);                // Join the I2C bus with address 8 as a slave
  Wire.onReceive(receiveEvent); // Register the receiveEvent function to be called when data is received
}

void loop() {
  Serial.print("Received via I2C: "); // Print label
  Serial.println(receivedValue);     // Print the latest received I2C value
  delay(500);                        // Wait for 500 milliseconds before repeating
}

void receiveEvent(int howMany) {
  if (howMany >= 1) {         // Check if at least one byte was received
    receivedValue = Wire.read(); // Read the first byte from the I2C bus and store it
  }
}
