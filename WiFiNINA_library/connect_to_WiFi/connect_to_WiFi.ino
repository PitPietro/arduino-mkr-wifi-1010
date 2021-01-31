#include <WiFiNINA.h>
#include "arduino_secrets.h"
#define DIV "----------------------------------------"

int status = WL_IDLE_STATUS; // Wifi radio's status

// set a custom delay for the 'loop()' function
// since are milliseconds, you can express them in seconds * 1000
const unsigned int custom_delay = 5 * 1000;

void setup() {
  // initialize serial communication and wait for port to open
  Serial.begin(9600);
  while (!Serial);

  // attempt to connect to Wifi network
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to network: ");
    Serial.println(WIFI_SSID);

    // connect to WPA/WPA2 network
    status = WiFi.begin(WIFI_SSID, WIFI_PWD);

    // wait for connection
    delay(custom_delay);
  }

  // the board is now connected, print out the data
  Serial.println("You're connected to the network");

  Serial.println(DIV);
  printData();
  Serial.println(DIV);
}

void loop() {
  // check the network connection once every 'custom_delay' seconds
  delay(custom_delay);
  printData();
  Serial.println(DIV);
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

/*
  Press Ctrl + Shift + N and create 'arduino_secrets.h' file as follow:

  ```c
  #define WIFI_SSID "" // place your WiFi name inside the quotes
  #define WIFI_PWD "" // place your WiFi password inside the quotes
  ```

  Note: I added all the 'arduino_secrets.h' files to '.gitignore' to avoid loose of sensitive data.

  The official tutorial is available at:
  Connecting MKR WiFi 1010 to a Wi-Fi network
  https://www.arduino.cc/en/Guide/MKRWiFi1010/connecting-to-wifi-network

  https://www.arduino.cc/en/Reference/WiFiNINA
*/
