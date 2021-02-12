/*
 * NTP Client (Network Time Protocol)
 * 
 * This code will query a Network Time Protocol (NTP) server so that the board can get the time from the Internet.
 * 
 * Press Ctrl + Shift + N and create 'arduino_secrets.h' file as follow:
 * 
 * ```c
 * #define WIFI_SSID "" // place your WiFi name inside the quotes
 * #define WIFI_PWD "" // place your WiFi password inside the quotes
 * ```
 * 
 * Note: I added all the 'arduino_secrets.h' files to '.gitignore' to avoid loose of sensitive data.
 * Doc: https://www.arduino.cc/en/Tutorial/LibraryExamples/WiFiNINAUdpNTPClient
 * NTP: http://en.wikipedia.org/wiki/Network_Time_Protocol
*/
#include <WiFiNINA.h>
#include <WiFiUdp.h>
#include <SPI.h>
#include "arduino_secrets.h"

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
  Serial.print("signal strength (RSSI):");
  Serial.println(rssi);

  byte encryption = WiFi.encryptionType();
  Serial.print("Encryption Type:");
  Serial.println(encryption, HEX);
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
  
  Serial.println("\nStarting connection to server...");
  Udp.begin(localPort);
}

void loop() {
  // send an NTP packet to a time server
  sendNTPpacket(timeServer);

  // wait a second to see if a reply is available
  delay(1000);

  if (Udp.parsePacket()) {
    Serial.println("packet received");
    
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
    
    Serial.print("Seconds since Jan 1 1900 = ");
    Serial.println(secsSince1900);

    // 3) convert NTP time into everyday time
    Serial.print("Unix time = ");
    
    // Unix time starts on Jan 1 1970. In seconds, that's 2208988800
    const unsigned long seventyYears = 2208988800UL;

    // subtract seventy years
    unsigned long epoch = secsSince1900 - seventyYears;

    // print Unix time
    Serial.println(epoch);
    
    // print the hour, minute and second
    // UTC is the time at Greenwich Meridian (GMT)
    Serial.print("The UTC time is ");
    
    // print the hour (86400 equals secs per day)
    Serial.print((epoch  % 86400L) / 3600);
    Serial.print(':');

    if (((epoch % 3600) / 60) < 10) {
      // in the first 10 minutes of each hour, we'll want a leading '0' (i.e. '9:5:30' becomes '9:05:30')
      
      Serial.print('0');
    }

    // print the minute (3600 equals secs per minute)
    Serial.print((epoch  % 3600) / 60);
    Serial.print(':');

    if ((epoch % 60) < 10) {
      // in the first 10 seconds of each minute, we'll want a leading '0' (i.e. '9:5:6' becomes '9:05:06'
      
      Serial.print('0');
    }

    // print the second
    Serial.println(epoch % 60); 
  }

  // wait ten seconds before asking for the time again
  delay(10000);
}
