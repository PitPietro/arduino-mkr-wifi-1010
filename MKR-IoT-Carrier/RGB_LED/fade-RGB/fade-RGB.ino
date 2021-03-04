/*
* Fade RBG LEDs
*/

#include <Arduino_MKRIoTCarrier.h>
MKRIoTCarrier carrier;

#define MAX 4

void setup() {
  Serial.begin(9600);
  CARRIER_CASE = false;
  carrier.begin();

  uint16_t time = millis();
  carrier.display.fillScreen(ST77XX_BLACK);
  time = millis() - time;
}

int i = 0;
int ledC = 0;
int ledA = 0;

void loop() {
  uint32_t red = carrier.leds.Color(0, 255, 0);
  uint32_t green = carrier.leds.Color(255, 0, 0);
  uint32_t blue = carrier.leds.Color(0, 0, 255);
  uint32_t orange = carrier.leds.Color(50, 242, 0);  
  
  uint32_t colors[MAX] = {red, green, blue, orange};

  int c;
  for(c = 0; c < MAX; c++) {
    fadeLoop(colors[c]);
  }
}

// Fading a given color loop
void fadeLoop(uint32_t color) {

  carrier.leds.fill(color, ledA, ledC);
  for ( i = 0; i < 125; i++) {
    carrier.leds.setBrightness(i);
    carrier.leds.show();
    delay(10);
  }

  for ( i = 125; i > -1; i--) {
    carrier.leds.setBrightness(i);
    carrier.leds.show();
    delay(10);
  }
  
  carrier.leds.clear();
  delay(500);
}