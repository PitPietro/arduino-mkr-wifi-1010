/*
 * Taking inspiration from Drew Alden's https://github.com/ReanimationXP/MKR_WiFi_1010/blob/master/examples/RainbowRGB/RainbowRGB.ino
 * Check each color of the RBG LED: from 0 to 255 foreach color (red, green and blue).
*/
#include <SPI.h>
#include <WiFiNINA.h> //https://github.com/arduino-libraries/WiFiNINA
#include <utility/wifi_drv.h> //included with WiFiNINA

// RGB LED pin definitions for Arduino MKR WiFi 1010
#define GREEN_PIN 25
#define RED_PIN 26
#define BLUE_PIN 27

// maximum value for each color of the RBG
#define MAX 255

void setup() {
  //set ESP32 wifi module RGB led pins to output
  WiFiDrv::pinMode(RED_PIN, OUTPUT); // RED
  WiFiDrv::pinMode(GREEN_PIN, OUTPUT); // GREEN
  WiFiDrv::pinMode(BLUE_PIN, OUTPUT); // BLUE

  //turn off ESP32 wifi module RGB led
  // values are uint8_t
  WiFiDrv::digitalWrite(RED_PIN, LOW); 
  WiFiDrv::digitalWrite(GREEN_PIN, LOW);
  WiFiDrv::digitalWrite(BLUE_PIN, LOW);

  // initialize serial communication and wait for port to open
  Serial.begin(9600);
  // wait for serial port to connect. Needed for native USB port only
  while (!Serial);

  /*
  char c = 48; // ASCII --> 0
  for(c = 48; c < 58; c++) {
    Serial.print("number = ");
    Serial.println(c);
  }
  */
}

void loop() {
  short int timeToWait = 50;
  makeStair('R', timeToWait);
  makeStair('G', timeToWait);
  makeStair('B', timeToWait);
  makeStair('x', timeToWait);
}

void setLEDColor(uint8_t R, uint8_t G, uint8_t B) {
  //R, G, and B values should not exceed 255 or be lower than 0.
  WiFiDrv::analogWrite(RED_PIN, R); //Red
  WiFiDrv::analogWrite(GREEN_PIN, G); //Green
  WiFiDrv::analogWrite(BLUE_PIN, B);  //Blue

  Serial.print("red: ");
  Serial.print(R);
  Serial.print("  green: ");
  Serial.print(G);
  Serial.print("  blue: ");
  Serial.println(B);
}

void makeStair(char color, int stepTime) {
  /*
   * Select a color (red, green or blue) and increase the value (from 0 to 255). 
   * Each step waits for 'stepTime' milliseconds.
   */

   switch(color) {
    case 'R': {
      Serial.println("\n~~~ RED stair");
      
      short int i;
      for(i = 0; i <= MAX; i++) {
        setLEDColor(i, 0, 0);        
        delay(stepTime);
      }
      break;
    };
    case 'G': {
      Serial.println("\n~~~ GREEN stair");

      short int i;
      for(i = 0; i <= MAX; i++) {
        setLEDColor(0, i, 0);        
        delay(stepTime);
      }
      break;
    };
    case 'B': {
      Serial.println("\n~~~ BLUE stair");

      short int i;
      for(i = 0; i <= MAX; i++) {
        setLEDColor(0, 0, i);        
        delay(stepTime);
      }
      break;
    };
    default: {
      Serial.println("\n~~~ DEFAULT");
      setLEDColor(0, 0, 0);
      break;
    }
   }
}
