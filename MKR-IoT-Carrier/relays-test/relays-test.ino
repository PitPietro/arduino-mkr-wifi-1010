#include <Arduino_MKRIoTCarrier.h>

MKRIoTCarrier carrier;
#define DELAY_TIME 10000

void setup() {
  CARRIER_CASE = false;
  carrier.begin();

  // Initialize serial communication at 9600 baud rate
  Serial.begin(9600);
  // Wait for serial port to connect. Needed for native USB port only.
  while (!Serial);
}

void loop() {
  // swap to the Normally Open (NO) circuit of relay 1 (turns it on)
  carrier.Relay1.open();
  printInfo();
  delay(DELAY_TIME);

  // swap to the Normally Closed (NC) circuit of relay 1 (turns it off)
  carrier.Relay1.close();
  printInfo();
  delay(DELAY_TIME);

  // swap to the Normally Open (NO) circuit of relay 2 (turns it on)
  carrier.Relay2.open();
  printInfo();
  delay(DELAY_TIME);

  // swap to the Normally Closed (NC) circuit of relay 2 (turns it off)
  carrier.Relay2.close();
  printInfo();
  delay(DELAY_TIME);
}

void printInfo() {
  bool relayOne, relayTwo;
  
  // boolean variable, returns the status: LOW means NC and HIGH means NO
  relayOne = carrier.Relay1.getStatus();
  relayTwo = carrier.Relay2.getStatus();

  Serial.print("relayOne: ");
  Serial.print(relayOne);
  Serial.print("\t relayTwo: ");
  Serial.println(relayTwo);
}
