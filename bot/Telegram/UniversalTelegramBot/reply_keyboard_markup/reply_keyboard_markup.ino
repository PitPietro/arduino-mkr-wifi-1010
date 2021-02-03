/*
 * The Reply Keyboard Markup Bot sends a keyboard to the specified 'chat_id'.
 * 'parse_mode' can be left blank. Will return true if the message sends successfully.
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
  Serial.println("handleNewMessages");
  Serial.println(numNewMessages);

  for (int i = 0; i < numNewMessages; i++) {
    String chat_id = bot.messages[i].chat_id;
    String text = bot.messages[i].text;

    String from_name = bot.messages[i].from_name;
    if (from_name == "")
      from_name = "Guest";

    /// switch statement can only be done with int (or char) value 
    if(text == "/ledon") {
      digitalWrite(LED_BUILTIN, HIGH);
      bot.sendMessage(chat_id, "Led is ON", "");
    } else if(text == "/ledoff") {
      digitalWrite(LED_BUILTIN, LOW);
      bot.sendMessage(chat_id, "Led is OFF", "");
    } else if(text == "/status") {
      String msg = "Status: the led is ";
      if (digitalRead(LED_BUILTIN)) {
        bot.sendMessage(chat_id, msg + "ON", "");
      }
      else {
        bot.sendMessage(chat_id, msg + "OFF", "");
      }
    } else if(text == "/contribute") {
      String msg = "Contribute to [PitPietro/arduino-mkr-wifi-1010](https://github.com/PitPietro/arduino-mkr-wifi-1010)\n";
      msg += "This bot was made by [PitPietro](https://github.com/PitPietro) using [Universal Telegram Bot](https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot) library.\n";
      msg += "You can fork [this](https://github.com/PitPietro/arduino-mkr-wifi-1010) repository and start coding on your own lapton, then make a **pull request**!\n";
      
      bot.sendMessage(chat_id, msg, "Markdown");
    } else if (text == "/options") {
      String keyboardJson = "[[\"/ledon\", \"/ledoff\"],[\"/status\"],[\"/contribute\"]]";
      
      bot.sendMessageWithReplyKeyboard(chat_id, "Choose from one of the following options", "", keyboardJson, true);
    } else if (text == "/start") {
      String msg = "Welcome " + from_name + "!\n";
      msg += "I was made by **PitPietro** using Universal Telegram Bot library.\n";
      msg += "I am the **LED ON/OFF** bot.\n\n";
      msg += "I guess you're asking youself what can you do with me, here is the list of possible actions:\n";
      msg += "/ledon switch the built-in led ON\n";
      msg += "/ledoff switch the built-in led OFF\n";
      msg += "/status ask current status of the led\n";
      msg += "/options return the reply keyboard\n";
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

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  Serial.println("\n~~~ Reply Keyboard Markup Bot ~~~\n");
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
