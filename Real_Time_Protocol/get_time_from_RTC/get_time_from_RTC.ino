/*
 * Real Time Clock (RTC)
 * 
 * This code access one Time Server on the internet and get from it the correct Time, using the Network Time Protocol (NTP)
 * builtin in the used WiFi module. The time is then used to configure the internal RTC (UTC format) of the board
 * using the linux epoch format.
 * 
 * Press Ctrl + Shift + N and create 'arduino_secrets.h' file as follow:
 * 
 * ```c
 * #define WIFI_SSID "" // place your WiFi name inside the quotes
 * #define WIFI_PWD "" // place your WiFi password inside the quotes
 * ```
 * 
 * Note: I added all the 'arduino_secrets.h' files to '.gitignore' to avoid loose of sensitive data.
 * 
 * <SPI.h> allows you to communicate eith SPI devices (with Arduino as the master device).
 * <RTCZero.h> allows the board to control and use the internal RTC (Real Time Clock).
 * 
 * Doc: https://www.arduino.cc/en/Tutorial/WiFiRTC
 * RTCZero Epoch example: https://raw.githubusercontent.com/arduino-libraries/RTCZero/master/examples/Epoch/Epoch.ino
 * RTCZero Docs: https://www.arduino.cc/reference/en/libraries/rtczero/
*/
#include <SPI.h>
#include <WiFiUdp.h>
#include <RTCZero.h>
#include <WiFiNINA.h>
#include "arduino_secrets.h"

// Wifi radio's status
int status = WL_IDLE_STATUS;

RTCZero rtc;

// change this to adapt it to your time zone: GMT + 1 = CET
const short int GMT = 1;

void printData() {
  Serial.println("Board Information:");

  // print the board's IP address
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  Serial.println();
  Serial.println("Network Information:");
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print the received signal strength
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI): ");
  Serial.println(rssi);

  byte encryption = WiFi.encryptionType();
  Serial.print("Encryption Type:");
  Serial.println(encryption, HEX);
  Serial.println();
}

void print2digits(int number) {
  if (number < 10) {
    Serial.print("0");
  }

  Serial.print(number);
}

void printDate() {
  Serial.print(rtc.getDay());
  Serial.print("/");
  Serial.print(rtc.getMonth());
  Serial.print("/");
  Serial.print(rtc.getYear());
  Serial.print(" ");
}

void printTime() {
  print2digits(rtc.getHours() + GMT);
  Serial.print(":");
  
  print2digits(rtc.getMinutes());
  Serial.print(":");

  print2digits(rtc.getSeconds());
  Serial.println();
}

void setup() {
  // initialize serial communication and wait for port to open
  Serial.begin(9600);
  // wait for serial port to connect. Needed for native USB port only
  while (!Serial);

  // check for the WiFi module
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    while (true); // do not continue
  }

  // attempt to connect to Wifi network
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to network: ");
    Serial.println(WIFI_SSID);

    // connect to WPA/WPA2 network
    status = WiFi.begin(WIFI_SSID, WIFI_PWD);

    // wait for connection
    delay(5000);
  }

  // the board is now connected, print out the data
  Serial.println("You're connected to the network");

  printData();

  // start the RTC communication
  rtc.begin();

  unsigned long epoch;

  short int numberOfTries = 0, maxTries = 6;

  do {
    epoch = WiFi.getTime();
    numberOfTries++;

  }

  while ((epoch == 0) && (numberOfTries < maxTries));

  if (numberOfTries == maxTries) {
    Serial.print("NTP unreachable!!");
    while (1);
  }

  else {

    Serial.print("Epoch received: ");

    Serial.println(epoch);

    rtc.setEpoch(epoch);

    Serial.println();

  }
}

void loop() {
  printDate();
  printTime();

  Serial.println();

  // wait a second before loop again
  delay(1000);
}
