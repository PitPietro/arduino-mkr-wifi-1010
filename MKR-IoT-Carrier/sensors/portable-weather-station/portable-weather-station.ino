/*
   Portable Weather Station with MKR IoT Carrier

   The boolean 'CARRIER_CASE' can be set to either 'true' or 'false' (by default has been set to 'false').
   This refers to the plastic casing in the kit and the capacitive buttons on the carrier.
   If you use the plastic casing, set it to 'true' and if not, set it to 'false'.

   Docs: https://opla.arduino.cc/opla/module/carrier/lesson/get-to-know-the-carrier

   +

   Real Time Clock (RTC)

   This code access one Time Server on the internet and get from it the correct Time, using the Network Time Protocol (NTP)
   builtin in the used WiFi module. The time is then used to configure the internal RTC (UTC format) of the board
   using the linux epoch format.

   Press Ctrl + Shift + N and create 'arduino_secrets.h' file as follow:

   ```c
   #define WIFI_SSID "" // place your WiFi name inside the quotes
   #define WIFI_PWD "" // place your WiFi password inside the quotes
   ```

   Note: I added all the 'arduino_secrets.h' files to '.gitignore' to avoid loose of sensitive data.

   <SPI.h> allows you to communicate eith SPI devices (with Arduino as the master device).
   <RTCZero.h> allows the board to control and use the internal RTC (Real Time Clock).

   Doc: https://www.arduino.cc/en/Tutorial/WiFiRTC
   RTCZero Epoch example: https://raw.githubusercontent.com/arduino-libraries/RTCZero/master/examples/Epoch/Epoch.ino
   RTCZero Docs: https://www.arduino.cc/reference/en/libraries/rtczero/
*/
#include <Arduino_MKRIoTCarrier.h>
#include <SPI.h>
#include <WiFiUdp.h>
#include <RTCZero.h>
#include <WiFiNINA.h>
#include "arduino_secrets.h"

MKRIoTCarrier carrier;

float temperature = 0;
float humidity = 0;

// Wifi radio's status
int status = WL_IDLE_STATUS;

RTCZero rtc;

// change this to adapt it to your time zone: GMT + 1 = CET (Central European Time)
const short int TIME = 0;

void setup() {
  CARRIER_CASE = false;

  // initialize the MKR IoT Carrier and output any errors in the serial monitor
  carrier.begin();
  carrier.display.setRotation(0);

  // check for the WiFi module
  if (WiFi.status() == WL_NO_MODULE) {
    // communication with WiFi module failed!
  }

  short int attemps = 0;

  // attempt to connect to Wifi network
  while (status != WL_CONNECTED && attemps <= 10) {
    // attempting to connect to network:
    // WIFI_SSID
    
    // connect to WPA/WPA2 network
    status = WiFi.begin(WIFI_SSID, WIFI_PWD);

    carrier.display.fillScreen(ST77XX_BLUE);
    carrier.display.setTextColor(ST77XX_WHITE);
    carrier.display.setTextSize(2);
    carrier.display.setCursor(35, 100);
    carrier.display.print("Connecting to");
    carrier.display.setCursor(35, 120);
    carrier.display.println(WIFI_SSID);

    // wait for connection
    delay(500);
    attemps++;
  }

  if (status != WL_CONNECTED) {
    carrier.display.fillScreen(ST77XX_RED);
    carrier.display.setTextColor(ST77XX_WHITE);
    carrier.display.setTextSize(2);
    // sets position for printing (x and y)
    carrier.display.setCursor(35, 100);
    carrier.display.print("WiFi connection");
    carrier.display.setCursor(80, 120);
    carrier.display.print("failed ");
  }

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
    // NTP unreachable
    carrier.display.fillScreen(ST77XX_RED);
    carrier.display.setTextColor(ST77XX_WHITE);
    carrier.display.setTextSize(2);
    carrier.display.setCursor(35, 100);
    carrier.display.print("NTP unreachable");
    /*

    */
    delay(5000);
  } else {
    // epoch received
    rtc.setEpoch(epoch);
    carrier.display.fillScreen(ST77XX_GREEN);
    carrier.display.setTextColor(ST77XX_WHITE);
    carrier.display.setTextSize(2);
    // sets position for printing (x and y)
    carrier.display.setCursor(35, 100);
    carrier.display.print("epoch received ");
    carrier.display.print(epoch);
  }

  // add the TIME constant to the hours
  // with TIME = 1, it will become CET: GTM + 1
  // with TIME = 2, it will become CEST: GTM + 2
  rtc.setHours(rtc.getHours() + TIME);

  // the board ask the hours in GTM and then add the TIME constant
  // if this new value is major than 23, evaluate the right hours value (from 0 to 23)
  /*
    if(rtc.getHours() > 23) {
    rtc.setHours(rtc.getHours() - 24);
    rtc.setDay(rtc.getDay() + 1);
    } else if (rtc.getHours() < 0) {
    // all rtc's methods only accepts 'byte' as parameter(s), which are equal to 'unsigned char'
    // it is no possible to have negative time (GTM - TIME = negative number)

    // rtc.setHours(24 - TIME);
    // you could also check for the day not to be 0th of the month
    // rtc.setDay(rtc.getDay() - 1);
    }
  */
}

void loop() {
  // read values from sensors
  temperature = carrier.Env.readTemperature();
  humidity = carrier.Env.readHumidity();

  printInfo();
  // printDate();
  // printTime();

  delay(500);
}

void printData() {
  // board information

  // print the board's IP address
  IPAddress ip = WiFi.localIP();
  // IP Address
  // ip

  // network information
  // SSID
  // WiFi.SSID()

  // print the received signal strength
  long rssi = WiFi.RSSI();
  // signal strength (RSSI)
  // rssi

  byte encryption = WiFi.encryptionType();
  // encryption type
  // println(encryption, HEX);
}

void print2digits(int number) {
  if (number < 10) {
    Serial.print("0");
  }

  Serial.print(number);
}

void printDate() {
  /*
    print2digits(rtc.getDay());
    Serial.print("/");

    print2digits(rtc.getMonth());
    Serial.print("/");

    Serial.print(rtc.getYear());
    Serial.print(" ");
  */
}

void printTime() {
  /*
    print2digits(rtc.getHours());
    Serial.print(":");

    print2digits(rtc.getMinutes());
    Serial.print(":");

    print2digits(rtc.getSeconds());
    Serial.println();
  */
}

void printInfo() {
  // background
  carrier.display.fillScreen(ST77XX_BLUE);
  // white text
  carrier.display.setTextColor(ST77XX_WHITE);
  // medium sized text
  carrier.display.setTextSize(2);

  //sets position for printing (x and y)
  carrier.display.setCursor(30, 110);

  carrier.display.print("TEMP ");
  carrier.display.print(temperature);
  carrier.display.print(" ");
  // since ° cannot be printed with a simple 'print()', let's create it
  carrier.display.drawCircle(156, 112, 2, ST77XX_WHITE);
  carrier.display.println("C");

  //sets new position for printing (x and y)
  carrier.display.setCursor(30, 130);

  carrier.display.print("HUM  ");
  carrier.display.print(humidity);
  carrier.display.println(" %");
}
