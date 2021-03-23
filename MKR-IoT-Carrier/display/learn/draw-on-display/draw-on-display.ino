/*
   Learn draw functions of MKR IoT Carrier's display

   the display is controller using the Adafruit-ST7735-Library with a resolution of 240x240
   https://cdn-learn.adafruit.com/downloads/pdf/adafruit-gfx-graphics-library.pdf

   width and height are defined in the same header file as above
   ```
   #define ST7735_TFTWIDTH_128 128  // for 1.44 and mini
   #define ST7735_TFTWIDTH_80 80    // for mini
   #define ST7735_TFTHEIGHT_128 128 // for 1.44" display
   #define ST7735_TFTHEIGHT_160 160 // for 1.8" and mini display
   ```

   And are setted in https://github.com/adafruit/Adafruit-ST7735-Library/blob/master/Adafruit_ST7735.cpp


   Docs: https://www.arduino.cc/reference/en/libraries/arduino_mkriotcarrier/
   Arduino Style Guide: https://www.arduino.cc/en/Reference/StyleGuide
   Adafruit-ST7735-Library: https://github.com/adafruit/Adafruit-ST7735-Library/
*/

#include <Arduino_MKRIoTCarrier.h>
MKRIoTCarrier carrier;

void drawPixelOnDisplay(long unsigned int, unsigned char, unsigned char);
void drawLineOnDisplay(long unsigned int, unsigned char, unsigned char, unsigned char, unsigned char);

// demos
void drawLineOnDisplayDemo(long unsigned int);

void setup() {
  CARRIER_CASE = false;
  carrier.begin();
}

void loop() {
  drawPixelOnDisplay(4000, 120, 180);
  drawLineOnDisplay(1000, 60, 40, 150, 190);

  // TODO test out the functions below
  // void drawFastVLine(uint16_t x0, uint16_t y0, uint16_t length, uint16_t color);
  // void drawFastHLine(uint8_t x0, uint8_t y0, uint8_t length, uint16_t color);

  // drawLineOnDisplayDemo(50);
}

void defaultDisplayConfig() {
  carrier.display.fillScreen(ST77XX_WHITE);
  carrier.display.setTextColor(ST77XX_BLACK);
  carrier.display.setRotation(0);
  carrier.display.setTextSize(1);
}

void printCoordinates(unsigned char x, unsigned char y) {
  carrier.display.setCursor(x, y);
  carrier.display.print("(");
  carrier.display.print(x);
  carrier.display.print("; ");
  carrier.display.print(y);
  carrier.display.print(")");
}

/*
  void drawPixel(uint16_t x, uint16_t y, uint16_t color);
*/
void drawPixelOnDisplay(long unsigned int delayTime, unsigned char x0, unsigned char y0) {
  defaultDisplayConfig();

  printCoordinates(x0, y0);

  carrier.display.drawPixel(x0, y0, ST77XX_GREEN);

  delay(delayTime);
}

/*
  void drawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);
*/
void drawLineOnDisplay(long unsigned int delayTime, unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1) {
  defaultDisplayConfig();

  printCoordinates(x0, y0);
  printCoordinates(x1, y1);

  carrier.display.drawLine(x0, y0, x1, y1, ST77XX_GREEN);

  delay(delayTime);
}

/*
   demos
*/

void drawLineOnDisplayDemo(long unsigned int delayTime) {
  carrier.display.fillScreen(ST77XX_WHITE);

  unsigned char width = carrier.display.width();
  unsigned char height = carrier.display.height();

  for (int i = 0; i < carrier.display.height(); i++) {
    carrier.display.drawLine(width, height, height - i, i, ST77XX_GREEN);
    carrier.display.drawLine(0, 0, i, height - i, ST77XX_RED);
    delay(delayTime);
  }
}
