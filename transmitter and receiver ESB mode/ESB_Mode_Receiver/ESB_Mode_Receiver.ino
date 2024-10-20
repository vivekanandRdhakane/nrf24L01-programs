#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Define NRF24L01 pins for ESP8266 (NodeMCU)
#define CE_PIN    D3  // GPIO4
#define CSN_PIN   D8  // GPIO15

// Initialize RF24 object
RF24 radio(CE_PIN, CSN_PIN);

// Address (must be the same on both transmitter and receiver)
const byte address[6] = "00001"; 

void setup() {
  Serial.begin(115200);
  radio.begin();
  
  // Set the address of the receiver
  radio.openReadingPipe(1, address);
  
  // Enable auto acknowledgment (ESB feature)
  radio.setAutoAck(true);
  
  // Set data rate
  radio.setDataRate(RF24_250KBPS);
  
  // Use 1-byte payload size (same as transmitter)
  radio.setPayloadSize(20);
  
  // Set PA level
  radio.setPALevel(RF24_PA_HIGH);
  
  // Start listening for incoming data
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    char send_string[20];
    
    // Read the incoming data
    radio.read(&send_string, sizeof(send_string));
    
    Serial.print("Received data: ");
    Serial.println(send_string);
  }
}
