#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <stdlib.h>

// Define NRF24L01 pins for ESP8266 (NodeMCU)
#define CE_PIN D3   // GPIO4
#define CSN_PIN D8  // GPIO15

// Initialize RF24 object
RF24 radio(CE_PIN, CSN_PIN);

// Address (must be the same on both transmitter and receiver)
const byte address[6] = "00001";

uint32_t count = 0;

void setup() {
  Serial.begin(115200);
  radio.begin();

  // Set the address of the transmitter
  radio.openWritingPipe(address);

  // Enable auto acknowledgment (ESB feature)
  radio.setAutoAck(true);

  // Set data rate (can be RF24_1MBPS, RF24_2MBPS, RF24_250KBPS)
  radio.setDataRate(RF24_250KBPS);

  // Set retries (delay between retries, number of retries)
  radio.setRetries(15, 15);  // 15 * 250μs delay, 15 retries

  // Use 1-byte payload size (change as needed)
  radio.setPayloadSize(20);

  // Set PA level (Power Amplification level)
  radio.setPALevel(RF24_PA_HIGH);

  // Stop listening to start sending data
  radio.stopListening();
}

void loop() {
  char send_string[20];
  sprintf(send_string, "count = %u", count++);

  // Send the data
  bool success = radio.write(&send_string, sizeof(send_string));

  if (success) {
    Serial.println("Transmission successful");
  } else {
    Serial.println("Transmission failed");
  }

  // Wait for a second before sending again
  delay(1000);
}
