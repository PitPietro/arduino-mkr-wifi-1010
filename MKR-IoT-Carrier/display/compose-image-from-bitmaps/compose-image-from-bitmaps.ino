/**************************************************************************
  This example shows how to compose images from bitmaps

  We have used this tool to convert the .bmp to cpp
  https://javl.github.io/image2cpp/
  Thanks!
  
 **************************************************************************/

/*
 * Compose Image from Bitmaps
*/

#include <Arduino_MKRIoTCarrier.h>

// save the images code there
#include "images.h"

MKRIoTCarrier carrier;

uint16_t custom_delay = 4000;

void setup() {
  CARRIER_CASE = false;
  carrier.begin();
  carrier.display.setRotation(0);

  uint16_t time = millis();
  carrier.display.fillScreen(ST77XX_BLACK);
  time = millis() - time;
}

void loop() {
  carrier.display.fillScreen(ST77XX_BLACK);
  drawArduino(0x04B3);
  delay(custom_delay);
  carrier.display.fillScreen(ST77XX_BLACK);
  drawEIoT();
  delay(custom_delay);
  
  carrier.display.fillScreen(ST77XX_WHITE);
  drawArduino(0x0000);
  delay(custom_delay);
  
  drawArduino(0xF324);
  delay(custom_delay);
  drawArduino(0x04B3);
  delay(custom_delay);

  carrier.display.fillScreen(ST77XX_WHITE);
  drawEIoT();
  delay(custom_delay);
}

//Compose the differentn parts of the image
void drawEIoT() {
  carrier.display.drawBitmap(44, 25, ArduinoLogo, 152, 72, 0x04B3);
  carrier.display.drawBitmap(48, 110, ArduinoText, 144, 23, 0x04B3);
  carrier.display.drawBitmap(0, 150, ExploreFrame, 240, 75, 0xF324);
  carrier.display.drawBitmap(0, 150, ExplreIoTKittext, 240, 75, 0x04B3);
  carrier.display.drawBitmap(0, 150, ExploreIoTtext, 240, 75, 0xFFFF);
}

//Same with the Arduino Logo and the text
void drawArduino(uint16_t color) {
  carrier.display.drawBitmap(44, 60, ArduinoLogo, 152, 72, color);
  carrier.display.drawBitmap(48, 145, ArduinoText, 144, 23, color);
}
