/*
 * Web Server Hello World
 * 
 * The code shows the easiest way to interact with the board using HTTP.
 * The server uses TCP, but since HTTP is build on top of TCP, it can render HTML pages.
 * 
 * Each line in the HTTP request is terminated by a CR, carriage return, character ('\r') and
 * a LF, line feed, character ('\n'). The end of the request can be determined by 2 sets of
 * those sequences: '\r\n\r\n'.
 * 
 * The 'client' methods are:
 * - client.connected()
 * check if the data is connected, and there is data to read
 * 
 * - client.available()
 * get the number of bytes available for reading (so there must be data to read)
 * 
 * - client.read()
 * read one byte from the incoming data (the HTTP request sent by the client)
 * 
 * - client.print() & client.println()
 * send data to the client, building a proper HTTP response
 *  
 * - client.stop()
 * end the connection
 * 
 * Reference: https://flaviocopes.com/arduino-webserver/
 * Docs:
 * - CR: https://www.asciihex.com/character/control/13/0x0D/cr-carriage-return
 * - LF: https://www.asciihex.com/character/control/10/0x0A/lf-line-feed
*/
#include <SPI.h>
#include <WiFiNINA.h>
#include "arduino_secrets.h"

// Wifi radio's status
int status = WL_IDLE_STATUS;

// TCP server on port 80
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

  
  // initialize the TCP server (on port 80)
  server.begin();
}

void loop() {
  // listen for client connections
  // 'available()' method of 'server' listens for incoming clients
  WiFiClient client = server.available();

  if (client) {
    // if you reach this point, it means there is an HTTP client connected
    
    String line = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);

        if (c != '\n' && c != '\r') {
          line += c;
        }

        if (c == '\n') {
          if (line.length() == 0) {
            // the HTML page you want to show to the client
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("Connection: close");
            client.println();
            client.println("<!DOCTYPE HTML>");
            client.println("<html>");
            client.println("<h1>Hello World</h1>");
            client.println("</html>");
            break;
          } else {
            line = "";
          }
        }
      }
    }

    client.stop();
  }
}
