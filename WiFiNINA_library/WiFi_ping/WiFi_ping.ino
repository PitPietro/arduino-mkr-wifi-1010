/*
 * Inspired by: https://www.arduino.cc/en/Tutorial/LibraryExamples/WiFiNINAWiFiPing
*/
#include <SPI.h>
#include <WiFiNINA.h>
#include "arduino_secrets.h"

int status = WL_IDLE_STATUS;

// delay is expressed in milliseconds, so you can express it in seconds * 1000
const unsigned int custom_delay = 5 * 1000;

// specify IP address or hostname
const String hostName = "www.google.com";
int pingResult;

void setup() {

  // initialize serial and wait for port to open
  // wait for serial port to connect. Needed for native USB port only
  Serial.begin(9600);
  while (!Serial); 
  
  // check for the WiFi module
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    
    // do not continue
    while (true);

  }

  String fv = WiFi.firmwareVersion();

  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to WiFi network
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(WIFI_SSID);

    // connect to WPA/WPA2 network
    status = WiFi.begin(WIFI_SSID, WIFI_PWD);

    // wait 5 seconds for connection:
    delay(custom_delay);
  }

  Serial.println("You're connected to the network");
  printCurrentNet();
  printWiFiData();
}

void loop() {
  Serial.print("Pinging ");
  Serial.print(hostName);
  Serial.print(": ");

  pingResult = WiFi.ping(hostName);

  if (pingResult >= 0) {
    Serial.print("SUCCESS! RTT = ");
    Serial.print(pingResult);
    Serial.println(" ms");
  } else {
    Serial.print("FAILED! Error code: ");
    Serial.println(pingResult);
  }

  delay(custom_delay);
}

void printWiFiData() {
  // print your board's IP address
  IPAddress ip = WiFi.localIP();

  Serial.print("IP address : ");
  Serial.println(ip);
  Serial.print("Subnet mask: ");
  Serial.println((IPAddress)WiFi.subnetMask());
  Serial.print("Gateway IP : ");
  Serial.println((IPAddress)WiFi.gatewayIP());

  // print the board's MAC address
  byte mac[6];
  WiFi.macAddress(mac);
  Serial.print("MAC address: ");
  printMacAddress(mac);
}

void printCurrentNet() {
  // print the SSID of the network the board is attached to
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print the MAC address of the router the board attached to
  byte bssid[6];
  WiFi.BSSID(bssid);
  Serial.print("BSSID: ");
  printMacAddress(bssid);

  // print the received signal strength
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI): ");
  Serial.println(rssi);

  // print the encryption type
  byte encryption = WiFi.encryptionType();
  Serial.print("Encryption Type: ");
  Serial.println(encryption, HEX);
  Serial.println();
}

void printMacAddress(byte mac[]) {
  int i;
  for (i = 5; i >= 0; i--) {
    if (mac[i] < 16) {
      Serial.print("0");
    }

    Serial.print(mac[i], HEX);

    if (i > 0) {
      Serial.print(":");
    }
  }

  Serial.println();
}
