/*
 * The Echo Bot will send you back every text message or emoji you send to the bot.
 * Press Ctrl + Shift + N and create 'arduino_secrets.h' file as follow:
 * 
 * ```c
 * #define WIFI_SSID "" // place your WiFi name inside the quotes
 * #define WIFI_PWD "" // place your WiFi password inside the quotes
 * #define BOT_TOKEN "" // place your bot token inside the quotes
 * ```
 * 
 * Note: I added all the 'arduino_secrets.h' files to '.gitignore' to avoid loose of sensitive data.
 * 
 * Reference: https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot
*/
#include <SPI.h>
#include <WiFiNINA.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h> // parsing Json from the API responses
#include "arduino_secrets.h"

const unsigned long BOT_MTBS = 1000; // mean time between scan messages
int status = WL_IDLE_STATUS;

WiFiSSLClient client;
UniversalTelegramBot bot(BOT_TOKEN, client);
unsigned long bot_lasttime; // last time messages' scan has been done

void handleNewMessages(int numNewMessages) {
  // if the user sends an emoji, it won't be written on the Serial Monitor
  // if the user sends an emoji, it won't be written on the Serial Monitor
  
  int i;
  for (i = 0; i < numNewMessages; i++) {
    String chatID = bot.messages[i].chat_id;
    String msgText = bot.messages[i].text;
    
    Serial.print("chat ID: ");
    Serial.print(chatID);
    Serial.print("\tmsg: ");
    Serial.println(msgText);
    
    bot.sendMessage(chatID, msgText, "");
  }
}

void printWiFiStatus() {
  // print the SSID of the network you're attached to
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
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

  String fv = WiFi.firmwareVersion();
  if (fv < "1.0.0") {
    Serial.println("Please upgrade the firmware");
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
  
  printWiFiStatus();

  Serial.println("\n~~~ Echo Bot ~~~\n");
}

void loop() {
  if (millis() - bot_lasttime > BOT_MTBS) {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while (numNewMessages) {
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    bot_lasttime = millis();
  }
}
