#include <Arduino_MKRIoTCarrier.h>

MKRIoTCarrier carrier;
float x, y, z;

/**
 * <Arduino_MKRIoTCarrier.h> includes <Arduino_LSM6DS3.h> library.
 * Follow the instructions here: https://www.arduino.cc/en/Reference/Arduino_LSM6DS3
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
  if (carrier.IMUmodule.accelerationAvailable()) {
    carrier.IMUmodule.readAcceleration(x, y, z);
    
    // print the acceleration information on the serial monitor
    printAcceleration();
  }

  // always place a short delay before closing the loop to let the board "take a breath" between the cycles
  delay(100);
}

void printAcceleration() {
  Serial.print("x: ");
  Serial.print(x);
  Serial.print(", y: ");
  Serial.print(y);
  Serial.print(", z: ");
  Serial.println(z);
}
