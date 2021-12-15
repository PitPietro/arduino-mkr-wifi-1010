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
  if (carrier.Light.gestureAvailable()) {

    // store the type of gesture read by the light sensor
    uint8_t gesture = carrier.Light.readGesture();

    Serial.print(gesture);
    Serial.print(" ~~~ ");

    if (gesture == UP) {
      Serial.println("UP");
    } else if (gesture == DOWN) {
      Serial.println("DOWN");
    } else if (gesture == LEFT) {
      Serial.println("LEFT");
    } else if (gesture == RIGHT) {
      Serial.println("RIGHT");
    }
  }
}