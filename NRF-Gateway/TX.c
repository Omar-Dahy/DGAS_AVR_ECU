#include <SPI.h>            // Include SPI library (used by nRF24L01)
#include <nRF24L01.h>       // Include nRF24L01 register definitions
#include <RF24.h>           // Include RF24 library for easier use of the nRF24L01 module

#define buttonPin 3         // Define the pin connected to the push button

RF24 radio(9, 10);          // Create an RF24 object with CE on pin 9 and CSN on pin 10
const byte address[6] = "00002";  // Address to communicate with the receiver (must match RX address)

int lastSent = -1;          // Variable to track the last value sent to avoid redundant transmissions

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);  // Set button pin as input with internal pull-up resistor
  Serial.begin(9600);                // Start serial communication for debugging

  radio.begin();                     // Initialize the nRF24L01 module
  radio.openWritingPipe(address);   // Open a writing pipe with the specified address
  radio.setPALevel(RF24_PA_MIN);    // Set the Power Amplifier level to minimum (short range, less interference)
  radio.stopListening();            // Set the module to transmitter mode (disable receiving)
}

void loop() {
  int value = digitalRead(buttonPin);              // Read the button state (LOW when pressed, HIGH when not)
  int dataToSend = (value == LOW) ? 5 : 0;         // If pressed, send 5; otherwise, send 0

  // Send only if the value has changed from the last sent value
  if (dataToSend != lastSent) {
    radio.write(&dataToSend, sizeof(dataToSend)); // Send the value via RF
    Serial.print("Sent: ");                        // Print sent value to Serial Monitor
    Serial.println(dataToSend);
    lastSent = dataToSend;                         // Update last sent value
  }

  delay(100);  // Small delay to avoid flooding the RF channel and reduce power usage
}
