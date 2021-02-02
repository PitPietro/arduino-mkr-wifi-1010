/*
 * Reading a serial ASCII-encoded string and light-up an RBG LED
 * 
 * This sketch demonstrates the Serial parseInt() function.
 * It looks for an ASCII string of comma-separated values.
 * It parses them into integers, and uses those to fade the Arduino MKR's build-in RGB LED.
 * 
 * Insert the values separated by a comma: i.e.
 * 1) 0, 0, 0 (black, no colors)
 * 2) 255, 255, 255 (white, all colors)
 * 3) 0, 50, 96
 * 4) 100, 150, 40
 * ...
 * 
 * Inspired by: https://www.arduino.cc/en/Tutorial/BuiltInExamples/ReadASCIIString
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
}

void loop() {
  
  // if there's any serial available, read it

  while (Serial.available() > 0) {
    // look for the next valid integer in the incoming serial stream
    int red = Serial.parseInt();

    // do it again
    int green = Serial.parseInt();

    // do it again
    int blue = Serial.parseInt();

    // look for the newline. That's the end of your sentence:

    if (Serial.read() == '\n') {
      /*
       * 'constrain()' function keeps the values in an acceptable range for PWM LED.
       * if the value was outside the range of what PWM can send, it will be limited to a valid number.
       * It behaves in a strange way so I commented it out, just for now
       * 
       * red = 255 - constrain(red, 0, 255);
       * green = 255 - constrain(green, 0, 255);
       * blue = 255 - constrain(blue, 0, 255);
      */

      // fade the LED
      WiFiDrv::analogWrite(RED_PIN, red); //Red
      WiFiDrv::analogWrite(GREEN_PIN, green); //Green
      WiFiDrv::analogWrite(BLUE_PIN, blue);  //Blue

      // print the three numbers in one string as hexadecimal:

      Serial.print("#");
      Serial.print(red, HEX);
      Serial.print(green, HEX);
      Serial.println(blue, HEX);
    }
  }
}
