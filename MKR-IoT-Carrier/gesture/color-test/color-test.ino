#include <Arduino_MKRIoTCarrier.h>

MKRIoTCarrier carrier;

void setup() {
  CARRIER_CASE = false;
  carrier.begin();

  // Initialize serial communication at 9600 baud rate
  Serial.begin(9600);
  // Wait for serial port to connect. Needed for native USB port only.
  while (!Serial)
    ;
}

void loop() {
  int red, green, blue, ambient;

  if (carrier.Light.colorAvailable()) {

    // store the RGB values and the ambient light intensity read by the light sensor
    carrier.Light.readColor(red, green, blue, ambient);

    Serial.println("red: " + String(red) + " ~ green: " + String(green) + " ~ blue: " + String(blue) + " ~ ambient: " + String(ambient));
  }
  delay(50);
}