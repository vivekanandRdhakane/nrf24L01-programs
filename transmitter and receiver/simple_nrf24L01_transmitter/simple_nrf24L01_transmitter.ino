// Transmitter Code for ESP8266 with NRF24L01

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
  Serial.println("Transmitter Starting...");

  // Initialize NRF24L01
  if (!radio.begin()) {
    Serial.println("NRF24L01 initialization failed!");
    while (1);
  }

  // Set the data rate (optional, can be 250KBPS, 1MBPS, or 2MBPS)
  radio.setDataRate(RF24_1MBPS);

  // Open writing pipe
  radio.openWritingPipe(address);

  // Optional: Power up the module
  radio.stopListening();
}

void loop() {
  const char text[] = "Hello ESP8266";

  // Send the data
  bool report = radio.write(&text, sizeof(text));

  if (report) {
    Serial.println("Data sent successfully.");
  } else {
    Serial.println("Sending failed.");
  }

  delay(1000); // Wait for a second before sending next data
}
