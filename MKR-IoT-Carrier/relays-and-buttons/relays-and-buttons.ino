#include <Arduino_MKRIoTCarrier.h>

MKRIoTCarrier carrier;
bool relayOne, relayTwo;

/**
 * Use the touch buttons to perform the following actions:
 * Button 00: Open relay n°1
 * Button 01: Close relay n°1
 * Button 02: Get the status of relays
 * Button 03: Open relay n°2
 * Button 04: Close relay n°2
 */
void setup() {
  CARRIER_CASE = false;
  carrier.begin();

  // Initialize serial communication at 9600 baud rate
  Serial.begin(9600);
  // Wait for serial port to connect. Needed for native USB port only.
  while (!Serial);
}

void loop() {
  delay(100);
}
