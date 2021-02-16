/*
 * Web Server Hello World
 * 
 * Reference: https://flaviocopes.com/arduino-webserver/
*/
#include <SPI.h>
#include <WiFiNINA.h>
#include "arduino_secrets.h"

// Wifi radio's status
int status = WL_IDLE_STATUS;

WiFiServer server(80);

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

  server.begin();
}

void loop() {
  WiFiClient client = server.available();

  if(client) {
    char one;
    char two;

    while(client.connected()) {
      if(client.available() {
        char c = client.read();
        Serial.write(c);

        if(one == '\n' && two == '\r' c == '\n') {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.println("<h1>Hello World</h1>");
          client.println("</html>");
          break;
        }

        one = two;
        two = c;
      }
    }

    client.stop();
  }
}
