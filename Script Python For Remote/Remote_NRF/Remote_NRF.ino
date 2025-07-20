#include <SPI.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00002";

#define ledPin1 A0
#define ledPin2 A1
#define ledPin3 A2

#pragma pack(push, 1)
struct ControllerPacket {
  int8_t lx;
  int8_t ly;
  int8_t rx;
  int8_t ry;
  uint8_t l2;
  uint8_t r2;
  uint8_t buttons_low;
  uint8_t buttons_high;
  char driver_state;
};
#pragma pack(pop)

ControllerPacket receivedPacket;

void setup() {
  Serial.begin(115200);
  
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);

  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin3, LOW);

  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    radio.read(&receivedPacket, sizeof(receivedPacket));

    uint16_t buttons = receivedPacket.buttons_low | (receivedPacket.buttons_high << 8);
    digitalWrite(ledPin1, buttons & 0x0001 ? HIGH : LOW);
    digitalWrite(ledPin2, buttons & 0x0002 ? HIGH : LOW);
    digitalWrite(ledPin3, buttons & 0x0008 ? HIGH : LOW);

    // ✨ Send full struct as JSON line
    Serial.print("{\"lx\":"); Serial.print(receivedPacket.lx);
    Serial.print(",\"ly\":"); Serial.print(receivedPacket.ly);
    Serial.print(",\"rx\":"); Serial.print(receivedPacket.rx);
    Serial.print(",\"ry\":"); Serial.print(receivedPacket.ry);
    Serial.print(",\"l2\":"); Serial.print(receivedPacket.l2);
    Serial.print(",\"r2\":"); Serial.print(receivedPacket.r2);
    Serial.print(",\"buttons_low\":"); Serial.print(receivedPacket.buttons_low);
    Serial.print(",\"buttons_high\":"); Serial.print(receivedPacket.buttons_high);
    Serial.print(",\"driver_state\":\""); Serial.print(receivedPacket.driver_state); Serial.println("\"}");
  }
}
