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

  width and height are defined in the same header file as above
  ```
  #define ST7735_TFTWIDTH_128 128  // for 1.44 and mini
  #define ST7735_TFTWIDTH_80 80    // for mini
  #define ST7735_TFTHEIGHT_128 128 // for 1.44" display
  #define ST7735_TFTHEIGHT_160 160 // for 1.8" and mini display

  ```

  And are setted in https://github.com/adafruit/Adafruit-ST7735-Library/blob/master/Adafruit_ST7735.cpp


  Docs: https://www.arduino.cc/reference/en/libraries/arduino_mkriotcarrier/
  Adafruit-ST7735-Library: https://github.com/adafruit/Adafruit-ST7735-Library/
*/

#include <Arduino_MKRIoTCarrier.h>
#define C 9
MKRIoTCarrier carrier;

void fillScreenAllColors(long unsigned int delayTime) {
  uint16_t colors[C] = {ST77XX_BLACK, ST77XX_WHITE, ST77XX_RED, ST77XX_GREEN, ST77XX_BLUE, ST77XX_CYAN, ST77XX_MAGENTA, ST77XX_YELLOW, ST77XX_ORANGE};

  for (int i = 0; i < C; i++) {
    carrier.display.fillScreen(colors[i]);
    delay(delayTime);
  }
}

void getScreenDim(long unsigned int delayTime, int screenX, short int screenY) {
  short int screenWidth = carrier.display.width();
  short int screenHeight = carrier.display.height();

  // what's the type for this argoments?
  carrier.display.setCursor(screenX, screenY);
  carrier.display.setTextSize(2);

  carrier.display.print(screenWidth);
  carrier.display.print(" x ");
  carrier.display.print(screenHeight);

  delay(delayTime);
}

void rotateScreen(long unsigned int delayTime) {
  // rotate the coordinate system with a number from 0 to 3

  short int center = carrier.display.width() / 2;

  for (int i = 0; i < 4; i++) {
    carrier.display.fillScreen(ST77XX_BLACK);
    carrier.display.setCursor(center - 8, center - 8);
    carrier.display.setTextSize(4);
    carrier.display.setRotation(i);
    carrier.display.print(i);
    
    delay(delayTime);
  }
}

void setup() {
  CARRIER_CASE = false;
  carrier.begin();
}

void loop() {
  // general
  // fillScreenAllColors(1000);

  // display the screen dimensions
  // getScreenDim(5000, 65, 120);

  // rotate the screen (0-3)
  rotateScreen(2000);
}
