/*
 * RBG LED Color Control
 * 
 * Docs: https://www.arduino.cc/reference/en/libraries/arduino_mkriotcarrier/
 * Reference: https://opla.arduino.cc/opla/module/iot-starter-kit-maker/lesson/01-remote-controlled-lights
*/

#include <Arduino_MKRIoTCarrier.h>
MKRIoTCarrier carrier;

uint8_t r = 0, g = 0, b = 0;

void setup() {
  CARRIER_CASE = false;
  
  // initialize the MKR IoT Carrier and output any errors in the serial monitor
  carrier.begin();
  carrier.display.setRotation(0);

  carrier.leds.setPixelColor(0, 100, 0, 0);
  carrier.leds.show();

  /*
  uint8_t i;
  // loop through red 
  for(i = 0; i < 256; i++) {
    r = i;
    lightsOn();
    delay(50);
  }

  // wait for a second
  delay(500);
  lightsOff();

  r = 0;
  i = 0;
  // loop through green 
  for(i = 0; i < 256; i++) {
    g = i;
    lightsOn();
    delay(50);
  }

  // wait for a second
  delay(500);
  lightsOff();
  
  r = 0;
  g = 0;
  // loop through blue 
  for(i = 0; i < 256; i++) {
    b = i;
    lightsOn();
    delay(50);
  }

  // wait for a second
  delay(500);
  */  
}

// rainbow loop
void loop() {
  short int wait_time = 500;

  // red  
  r = 255;
  g = 0;
  b = 0;
  lightsOn();
  delay(wait_time);

  // yellow
  r = 240;
  g = 255;
  b = 0;
  lightsOn();
  delay(wait_time);

  // green
  r = 15;
  g = 255;
  b = 0;
  lightsOn();
  delay(wait_time);
  
  // indaco
  r = 0;
  g = 70;
  b = 206;
  lightsOn();
  delay(wait_time);

  // violette
  r = 153;
  g = 0;
  b = 201;
  lightsOn();
  delay(wait_time);
}
	
void lightsOn() {
  carrier.leds.setPixelColor(0, g, r, b);
  carrier.leds.setPixelColor(1, g, r, b);
  carrier.leds.setPixelColor(2, g, r, b);
  carrier.leds.setPixelColor(3, g, r, b);
  carrier.leds.setPixelColor(4, g, r, b);
  carrier.leds.show();
}
	
 
	
void lightsOff() {
  carrier.leds.setPixelColor(0, 0, 0, 0);
  carrier.leds.setPixelColor(1, 0, 0, 0);
  carrier.leds.setPixelColor(2, 0, 0, 0);
  carrier.leds.setPixelColor(3, 0, 0, 0);
  carrier.leds.setPixelColor(4, 0, 0, 0);	
  carrier.leds.show();
}
