// Receiver Code for ESP8266 with NRF24L01

#include <SPI.h>
#include <RF24.h>

// Define NRF24L01 pins for ESP8266 (NodeMCU)
#define CE_PIN    D2  // GPIO4
#define CSN_PIN   D8  // GPIO15

// Initialize RF24 object
RF24 radio(CE_PIN, CSN_PIN);

// Define the pipe addresses for communication
const byte address[6] = "00001";

void setup() {
  Serial.begin(115200);
  Serial.println("Receiver Starting...");

  // Initialize NRF24L01
  if (!radio.begin()) {
    Serial.println("NRF24L01 initialization failed!");
    while (1);
  }

  // Set the data rate (optional, must match transmitter)
  radio.setDataRate(RF24_1MBPS);

  // Open reading pipe
  radio.openReadingPipe(0, address);

  // Start listening
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    char text[32] = ""; // Buffer to store received data
    radio.read(&text, sizeof(text));
    Serial.print("Received: ");
    Serial.println(text);
  }
}
