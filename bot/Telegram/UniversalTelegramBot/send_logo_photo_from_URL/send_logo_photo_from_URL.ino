/*
 * The Send Logo Photo Bot sends a logo photo.  
 * 
 * I planned to code a bot which sends random photo from https://unplash.com
 * The "base URL" is 'https://source.unsplash.com/featured/?KEYWORD'
 * 'KEYWORD' must be replaced with the term to search for: i.e. 'coding', 'nature', 'life' and so on.
 * It will also accept multiple comma-separated values: i.e. 'nature,white'. 
 * It will also accept a "base URL" like 'https://source.unsplash.com/WIDTHxHEIGHT/?KEYWORD'
 * 'WIDTHxHEIGHT' must be replaced with a screen dimension: i.e. '1600x900' or similar.
 * 
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
 * Reference: 
 * https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot
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
  Serial.println("handleNewMessages");
  Serial.println(numNewMessages);

  for (int i = 0; i < numNewMessages; i++) {
    String chat_id = bot.messages[i].chat_id;
    String text = bot.messages[i].text;

    String from_name = bot.messages[i].from_name;
    if (from_name == "")
      from_name = "Guest";

    /// switch statement can only be done with int (or char) value 
    if(text == "/arduino") {
      const String arduinoLogoURL = "https://www.arduino.cc/en/uploads/Trademark/ArduinoCommunityLogo.png";
      
      bot.sendPhoto(chat_id, arduinoLogoURL, "Arduino Community Logo!");
    } else if(text == "/raspberrypi") {
      const String arduinoLogoURL = "https://www.raspberrypi.org/app/uploads/2018/03/RPi-Logo-Reg-SCREEN.png";
      
      bot.sendPhoto(chat_id, arduinoLogoURL, "Arduino Community Logo!");
    } else if(text == "/contribute") {
      String msg = "Contribute to [PitPietro/arduino-mkr-wifi-1010](https://github.com/PitPietro/arduino-mkr-wifi-1010)\n";
      msg += "This bot was made by [PitPietro](https://github.com/PitPietro) using [Universal Telegram Bot](https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot) library.\n";
      msg += "You can fork [this](https://github.com/PitPietro/arduino-mkr-wifi-1010) repository and start coding on your own lapton, then make a **pull request**!\n";
      
      bot.sendMessage(chat_id, msg, "Markdown");
    } else if (text == "/start") {
      String msg = "Welcome " + from_name + "!\n";
      msg += "I was made by **PitPietro** using Universal Telegram Bot library.\n";
      msg += "I am the **LOGO** bot.\n\n";
      msg += "List of actions:\n";
      msg += "/arduino send the `Arduino` logo\n";
      msg += "/raspberrypi send the `Raspberry PI` logo\n";
      msg += "/contribute how to contribute to this series of bot.\n";
      
      bot.sendMessage(chat_id, msg, "Markdown");
    }
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

  Serial.println("\n~~~ Send Logo Photo Bot ~~~\n");
}

void loop() {
  if (millis() - bot_lasttime > BOT_MTBS) {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while (numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    bot_lasttime = millis();
  }
}
