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
#include <WiFiNINA.h>
#include "arduino_secrets.h"

MKRIoTCarrier carrier;

float temperature = 0;
float humidity = 0;

// Wifi radio's status
int status = WL_IDLE_STATUS;

// local port to listen for UDP packets
const unsigned short int localPort = 2390;

// time.nist.gov NTP server
IPAddress timeServer(129, 6, 15, 28);

// NTP time stamp is in the first 48 bytes of the message
const int NTP_PACKET_SIZE = 48;

// buffer to hold incoming and outgoing packets
byte packetBuffer[NTP_PACKET_SIZE];

// a UDP instance to let us send and receive packets over UDP
WiFiUDP Udp;

bool isOnline = false;

// send an NTP request to the time server at the given address
unsigned long sendNTPpacket(IPAddress& address) {
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);

  // initialize values needed to form NTP request

  // LI, Version, Mode
  packetBuffer[0] = 0b11100011;

  // Stratum, or type of clock
  packetBuffer[1] = 0;

  // Polling Interval
  packetBuffer[2] = 6;

  // Peer Clock Precision
  packetBuffer[3] = 0xEC;

  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;

  // all NTP fields have been given values, now
  // the board can send a packet requesting a timestamp
  // NTP requests are made to port 123
  Udp.beginPacket(address, 123);
  Udp.write(packetBuffer, NTP_PACKET_SIZE);
  Udp.endPacket();
}

void setup() {
  CARRIER_CASE = false;

  // initialize the MKR IoT Carrier and output any errors in the serial monitor
  carrier.begin();
  carrier.display.setRotation(0);

  // check for the WiFi module
  if (WiFi.status() == WL_NO_MODULE) {
    // communication with WiFi module failed!
  }
  
  short int maxAttemps = 5;
  short int attemp = 0;
  
  // attempt to connect to Wifi network
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to network: ");
    Serial.println(WIFI_SSID);

    // connect to WPA/WPA2 network
    status = WiFi.begin(WIFI_SSID, WIFI_PWD);

    carrier.display.fillScreen(ST77XX_BLUE);
    carrier.display.setTextColor(ST77XX_WHITE);
    carrier.display.setTextSize(2);
    carrier.display.setCursor(35, 100);
    carrier.display.print("Connecting");
    carrier.display.setCursor(35, 120);
    carrier.display.println("to server...");

    // wait for connection
    delay(500);
    
    attemp++;

    if (attemp == maxAttemps) {
      break;
    }
  }
  
  if(status == WL_CONNECTED) {
    isOnline = true;
      
    Udp.begin(localPort);
  }
}

void loop() {
  // read values from sensors
  temperature = carrier.Env.readTemperature();
  humidity = carrier.Env.readHumidity();

  // background
  carrier.display.fillScreen(ST77XX_BLUE);
  // white text
  carrier.display.setTextColor(ST77XX_WHITE);
  // medium sized text
  carrier.display.setTextSize(2);
  
  // if (isOnline == true)
  if(isOnline) {
    // send an NTP packet to a time server
    sendNTPpacket(timeServer);

    if (Udp.parsePacket()) {
      // Serial.println("packet received");

      // the board received a packet, read the data from it
      // read the packet into the buffer
      Udp.read(packetBuffer, NTP_PACKET_SIZE);

      // the timestamp starts at byte 40 of the received packet and is four bytes (or two words) long
      // 1) esxtract the two words
      unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
      unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);

      // 2) combine the four bytes (two words) into a long integer
      // this is NTP time (seconds since Jan 1 1900)
      unsigned long secsSince1900 = highWord << 16 | lowWord;

      // 3) convert NTP time into everyday time
      // Unix time starts on Jan 1 1970. In seconds, that's 2208988800
      const unsigned long seventyYears = 2208988800UL;

      // subtract seventy years: Unix time
      unsigned long epoch = secsSince1900 - seventyYears;

      // an hour is 86400 equals secs per day
      unsigned short int hoursUTC = (epoch  % 86400L) / 3600;
      // String strHoursUTC = String(hoursUTC);

      // minutes in UTC time saved as int and String
      // a minute is 3600 equals secs per minute
      unsigned short int minutesUTC = (epoch % 3600) / 60;
      String strMinutesUTC = "";

      // in the first 10 minutes of each hour, we'll want a leading '0' (i.e. '9:5:30' becomes '9:05:30')
      if (minutesUTC < 10) {
        strMinutesUTC.concat("0");
      }

      strMinutesUTC.concat(String(minutesUTC));

      // seconds in UTC time saved as int and String
      unsigned short int secondsUTC = epoch % 60;
      String strSecondsUTC = "";

      // in the first 10 seconds of each minute, the monitor need a leading '0' (i.e. '9:5:6' becomes '9:05:06')
      if (secondsUTC < 10) {
        strSecondsUTC.concat("0");
      }

      strSecondsUTC.concat(String(secondsUTC));

      /*
        UTC is the time at Greenwich Meridian (GMT)
        CET is the time at Central European Time, which is UTC + 1
        CEST is the time at Central European Summer Time, which is UTC + 2

        Please Note: by the time you'll run the script, you'll probably need to add some extra spaces to correctly
        see this table since the 'Seconds since 01/01/1900' could have become larger than a 10 digits number.
      */

      // CET = UTC + 1 hour
      String strHoursCET = "";

      if (hoursUTC + 1 < 10) {
        strHoursCET.concat("0");
      }

      strHoursCET.concat(String(hoursUTC + 1));

      // time is given by: strHoursCET : strMinutesUTC : strSecondsUTC
      printTime(strHoursCET, strMinutesUTC, strSecondsUTC);
    }
  }
  
  // always display weather info, even if the board does not connect to a WiFi network
  printInfo();

  delay(500);
}

void printTime(String hours, String minutes, String seconds) {
  //sets position for printing (x and y)
  carrier.display.setCursor(60, 60);

  carrier.display.print(hours);
  carrier.display.print(":");
  carrier.display.print(minutes);
  carrier.display.print(":");
  carrier.display.print(seconds);
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

void printInfo() {
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
