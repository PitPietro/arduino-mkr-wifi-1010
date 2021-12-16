#include <Arduino_MKRIoTCarrier.h>
MKRIoTCarrier carrier;

void setup() {
  CARRIER_CASE = false;
  carrier.begin();

  // Initialize serial communication at 9600 baud rate
  Serial.begin(9600);
  // Wait for serial port to connect. Needed for native USB port only.
  while (!Serial);
}

void loop() {
  // Each time you want to update the reads from the pads use this
  // It will update all the pads at the same time
  carrier.Buttons.update();

  // Different types of touches
  // When you first touch it
  if (carrier.Button0.onTouchDown()) {
    Serial.println("Touched Down Button 1");
    carrier.leds.setPixelColor(0, 200, 20, 20); // 'Off' pixel at tail
    carrier.leds.show(); // Refresh strip
    delay(50);
  } else {
    carrier.leds.setPixelColor(0, 0);
    carrier.leds.show(); // Refresh strip
  }

  // When you release it
  if (carrier.Button1.onTouchUp()) {
    Serial.println("Release Touch Button 2");
    carrier.leds.setPixelColor(1, 20, 20, 20); // 'Off' pixel at tail
    carrier.leds.show(); // Refresh strip
    delay(50);
  } else {
    carrier.leds.setPixelColor(1, 0);
    carrier.leds.show(); // Refresh strip
  }

  // When it detects a change, down or up
  if (carrier.Button2.onTouchChange()) {
    Serial.println("Changed Touch Button 3");
    carrier.leds.setPixelColor(2, 20, 20, 250); // 'Off' pixel at tail
    carrier.leds.show(); // Refresh strip
    delay(50);
  } else {
    carrier.leds.setPixelColor(2, 0);
    carrier.leds.show(); // Refresh strip
  }

  //Normal, if it is being pressed
  if (carrier.Button3.getTouch()) {
    Serial.println("Touching Button 4");
    carrier.leds.setPixelColor(3, 20, 20, 20); // 'Off' pixel at tail
    carrier.leds.show(); // Refresh strip
    delay(5);
  } else {
    carrier.leds.setPixelColor(3, 0);
    carrier.leds.show(); // Refresh strip
  }

  if (carrier.Button4.getTouch()) {
    Serial.println("Touching Button 5");
    carrier.leds.setPixelColor(4, 20, 20, 20); // 'Off' pixel at tail
    carrier.leds.show(); // Refresh strip
    delay(5);
  } else {
    carrier.leds.setPixelColor(4, 0);
    carrier.leds.show(); // Refresh strip
  }

  Serial.println();
  delay(10);
}
