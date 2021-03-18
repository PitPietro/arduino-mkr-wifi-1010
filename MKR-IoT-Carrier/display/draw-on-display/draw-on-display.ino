/*
   Draw on display

   the display is controller using the Adafruit-ST7735-Library with a resolution of 240x240

   Which colors can be displayed?
   Colors : every color with the prefix 'ST77XX_' (i.e. 'ST77XX_BLACK').
   Colors available from the library are BLACK, WHITE, RED, GREEN, BLUE, CYAN, MAGENTA, YELLOW, ORANGE.
   In order to turn on the screen you will need to add those commands inside the 'setup()', or just call call the 'begin()' function

   ```c
   display.init(240, 240);
   pinMode(TFT_BLACKLIGHT, OUTPUT);
   digitalWrite(TFT_BLACKLIGHT,HIGH);
   ```

  https://github.com/adafruit/Adafruit-ST7735-Library/blob/master/Adafruit_ST77xx.h
  ```c
   // Some ready-made 16-bit ('565') color settings:
  #define ST77XX_BLACK 0x0000
  #define ST77XX_WHITE 0xFFFF
  #define ST77XX_RED 0xF800
  #define ST77XX_GREEN 0x07E0
  #define ST77XX_BLUE 0x001F
  #define ST77XX_CYAN 0x07FF
  #define ST77XX_MAGENTA 0xF81F
  #define ST77XX_YELLOW 0xFFE0
  #define ST77XX_ORANGE 0xFC00
  ```
   Docs: https://www.arduino.cc/reference/en/libraries/arduino_mkriotcarrier/
   Adafruit-ST7735-Library: https://github.com/adafruit/Adafruit-ST7735-Library/
*/

#include <Arduino_MKRIoTCarrier.h>
#define C 9
MKRIoTCarrier carrier;

void drawGeneral(long unsigned int delayMillis) {
  uint16_t colors[C] = {ST77XX_BLACK, ST77XX_WHITE, ST77XX_RED, ST77XX_GREEN, ST77XX_BLUE, ST77XX_CYAN, ST77XX_MAGENTA, ST77XX_YELLOW, ST77XX_ORANGE};

  for (int i = 0; i < C; i++) {

    carrier.display.fillScreen(colors[i]);
    delay(delayMillis);
  }
}

void setup() {
  CARRIER_CASE = false;
  carrier.begin();
}

void loop() {
  drawGeneral(1000);
}
