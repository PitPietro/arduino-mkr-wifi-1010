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

void drawLineOnDisplay(long unsigned int);

void setup() {
  CARRIER_CASE = false;
  carrier.begin();
}

void loop() {
  drawLineOnDisplay(50);
}

/*
  void drawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);
*/
void drawLineOnDisplay(long unsigned int delayTime) {
  carrier.display.fillScreen(ST77XX_WHITE);

  uint16_t width = carrier.display.width();
  uint16_t height = carrier.display.height();

  for (int i = 0; i < carrier.display.height(); i++) {
    carrier.display.drawLine(width, height, height - i, i, ST77XX_GREEN);
    carrier.display.drawLine(0, 0, i, height - i, ST77XX_RED);
    delay(delayTime);
  }
}
