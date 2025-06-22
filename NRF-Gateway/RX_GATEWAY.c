#include <SPI.h>          // Include SPI library (required for nRF24L01 communication)
#include <nRF24L01.h>     // Include nRF24L01 definitions
#include <RF24.h>         // Include RF24 library for easier control of the nRF24L01
#include <Wire.h>         // Include Wire library for I2C communication

RF24 radio(9, 10);        // Create RF24 radio object with CE on pin 9 and CSN on pin 10
const byte address[6] = "00002";  // Address for the RX pipe (must match TX address)

#define ledPin A0         // Define LED pin (can be any digital or analog pin)

int lastSentI2C = -1;     // Store last value sent over I2C to avoid sending duplicate data

void setup() {
  Serial.begin(9600);       // Initialize serial communication for debugging
  Wire.begin();             // Join I2C bus as a master
  pinMode(ledPin, OUTPUT);  // Set LED pin as output
  digitalWrite(ledPin, LOW); // Turn LED off initially

  radio.begin();                     // Initialize the nRF24L01 module
  radio.openReadingPipe(0, address); // Open pipe 0 for reading, using the specified address
  radio.setPALevel(RF24_PA_MIN);     // Set Power Amplifier level to minimum (to reduce power and interference)
  radio.startListening();            // Begin listening for incoming data
}

void loop() {
  int receivedData = -1;  // Variable to hold the received RF24 data

  if (radio.available()) {   // Check if data is available from the transmitter
    radio.read(&receivedData, sizeof(receivedData)); // Read the incoming data
    Serial.print("Received from TX: ");
    Serial.println(receivedData); // Print the received data to Serial Monitor

    // Control LED based on received data
    if (receivedData == 5) {
      digitalWrite(ledPin, HIGH); // Turn LED on if received value is 5
    } else {
      digitalWrite(ledPin, LOW);  // Turn LED off for any other value
    }

    // Set the value to send over I2C based on received data
    int toSend = (receivedData == 5) ? 20 : 0;

    // Send new value only if it changed since last time
    if (toSend != lastSentI2C) {
      Wire.beginTransmission(8); // Start I2C transmission to slave device at address 8
      Wire.write(toSend);        // Send data byte (20 or 0)
      Wire.endTransmission();    // End I2C transmission
      Serial.print("Sent to Arduino 3 via I2C: ");
      Serial.println(toSend);    // Print the sent value to Serial Monitor
      lastSentI2C = toSend;      // Update last sent value
    }
  }
}
