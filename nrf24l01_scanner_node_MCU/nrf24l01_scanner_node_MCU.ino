#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN   D2  // Chip Enable pin for nRF24L01 (adjust to your pin configuration)
#define CSN_PIN  D8  // Chip Select Not pin for nRF24L01 (adjust to your pin configuration)

RF24 radio(CE_PIN, CSN_PIN);  // Create radio object

void setup() {
  Serial.begin(115200);  // Begin Serial communication for output
  while (!Serial) {
    delay(100);
  }

  // Initialize the radio
  if (!radio.begin()) {
    Serial.println(F("nRF24L01 module failed to initialize."));
    while (1);
  }

  radio.setPALevel(RF24_PA_LOW);  // Set the Power Amplifier level to low
  radio.setDataRate(RF24_1MBPS);  // Set the data rate to 1Mbps
  radio.setChannel(0);  // Initial channel setting

  Serial.println(F("nRF24L01 Scanner Ready"));
  Serial.println(F("Scanning all channels..."));
}

void loop() {
  Serial.println(F("Channel\tNoise Level"));
  
  // Scan all available channels
  for (int channel = 0; channel <= 125; channel++) {
    radio.setChannel(channel);
    uint8_t noiseLevel = radio.testRPD();  // Returns if signal power was detected (greater than -64dBm)
    
    Serial.print(channel);
    Serial.print("\t");
    Serial.println(noiseLevel ? "Noise Detected" : "Free");
    
    delay(10);  // Small delay to avoid overwhelming the serial monitor
  }
  
  Serial.println(F("\nScanning complete. Waiting 5 seconds before next scan...\n"));
  delay(1000000);  // Wait for 5 seconds before scanning again
}
