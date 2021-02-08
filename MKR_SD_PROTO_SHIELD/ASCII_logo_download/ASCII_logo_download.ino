/*
 * ASCII Logo Download for MKR WiFi 1010
 * 
 * The board uses WiFi to connect to the Arduino website.
 * It downloads the ASCII logo and save as a text file on the SD card.
 * The SD.h library is able to read and write only FAT16 or FAT32 cards.
 * 
 * You can also use the Arduino MKR ETH Shield to connect the MKR board with an Ethernet cable instead of using WiFi.
 * 
 * Hardware required:
 * 1) Arduino MKR WiFi 1010
 * 2) Arduino MKR SD Proto Shield
 * 
 * Software required:
 * 1) SPI.h and SD.h libraries let the board communicate with the SD Card
 * 2) WiFiNINA.h library let the board surf the Internet by connecting to the WiFi
 * 3) ArduinoHttpClient.h library allows the board to parse an HTTP GET request
 *    (under the hood, it separates the header from the body: the code is more readable)
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
 * Logo: https://www.arduino.cc/asciilogo.txt
 * Reference: https://create.arduino.cc/projecthub/Arduino_Genuino/download-and-store-web-data-37ef55
 * SD.h https://www.arduino.cc/en/Reference/SD
 * SD.h notes https://www.arduino.cc/en/Reference/SDCardNotes
 * SPI.h https://www.arduino.cc/en/Reference/SPI
 * Formatting the SD to FAT32: https://ragnyll.gitlab.io/2018/05/22/format-a-sd-card-to-fat-32linux.html
*/
#include <SD.h>
#include <SPI.h>
#include <WiFiNINA.h>
#include <ArduinoHttpClient.h>
#include "arduino_secrets.h"

int status = WL_IDLE_STATUS; // Wifi radio's status

// default SPI's CS pin for Arduino MKR SD Proto Shield
const short int chipSelect = 4;

// initialize the WiFi client library
WiFiSSLClient wifi;
HttpClient client = HttpClient(wifi, "www.arduino.cc", 443);
String response;
int statusCode = 0;

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

void saveToSD() {
  File dataFile = SD.open("logo.txt", FILE_WRITE);

  Serial.println("\nSaving on SD");

  if (dataFile) {
    dataFile.print(response);
  } else {
    Serial.println("Error while opening the file");
  }

  dataFile.close();
  client.stop();
  
  Serial.println("\nDone saving on SD");
}

void readFromSD() {
  File dataFile = SD.open("logo.txt", FILE_READ);
  
  Serial.println("\nReading from SD");
  
  while (dataFile.available()) {
    char c = dataFile.read();
    Serial.write(c);
  }
  
  dataFile.close();
  
  Serial.println("\nDone reading from SD");
}

void setup() {
  // initialize serial communication and wait for port to open
  Serial.begin(9600);
  // wait for serial port to connect. Needed for native USB port only
  while (!Serial);

  Serial.println("Initializing SD card");

  // check if the card is present and can be initialized
  if (!SD.begin(chipSelect)) {
    Serial.println("SD Card failed, or not present");
    // don't do anything more
    while (true);
  }
  Serial.println("Done: SD Card initialized");

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
}

void loop() {
  Serial.println("~~~ Make GET request ~~~");

  client.get("/asciilogo.txt");

  statusCode = client.responseStatusCode();

  // 2xx codes means success
  // 200 means OK: the request has succeded
  if(statusCode == 200) {
    // read the response
    response = client.responseBody();

    saveToSD();
    readFromSD();
  } else {
    Serial.println("Failed to get data from the website");
  }

  // do nothing forever
  while (true);
}
