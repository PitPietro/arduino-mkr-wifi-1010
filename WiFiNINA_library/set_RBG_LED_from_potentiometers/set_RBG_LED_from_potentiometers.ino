/*
 * Use tree potentiometers to light up the tree cores of an RBG LED.
 * Use the 'map()' function to map the values from 10 bits (0-1023) to 8 bits (0-255) so that
 * tree potentiometers can light up an RGB LED.
*/
#include <SPI.h>
#include <WiFiNINA.h> //https://github.com/arduino-libraries/WiFiNINA
#include <utility/wifi_drv.h> //included with WiFiNINA

// RGB LED pin definitions for Arduino MKR WiFi 1010
#define GREEN_PIN 25
#define RED_PIN 26
#define BLUE_PIN 27

const int potRed = A0;
const int potGreen = A1;
const int potBlue = A2;

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
  // map the potentiometers
  unsigned short int mappedRed = map(analogRead(potRed), 0, 1023, 0, 255);
  unsigned short int mappedGreen = map(analogRead(potGreen), 0, 1023, 0, 255);
  unsigned short int mappedBlue = map(analogRead(potBlue), 0, 1023, 0, 255);

  // fill the RBG LED with the mapped values
  WiFiDrv::analogWrite(RED_PIN, mappedRed); // red
  WiFiDrv::analogWrite(GREEN_PIN, mappedGreen); // green
  WiFiDrv::analogWrite(BLUE_PIN, mappedBlue); // blue

  // print the three numbers in one string as hexadecimal
  Serial.print("#");
  Serial.print(mappedRed, HEX);
  Serial.print(mappedGreen, HEX);
  Serial.println(mappedBlue, HEX);

  // wait for 50 milliseconds
  delay(50);
}
