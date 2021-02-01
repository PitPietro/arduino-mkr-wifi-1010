/*
 * Discord Bot Hello World
 * 
 * You need to create a Webhook:
 * Press on the Discord server's name and click to 'Server Settings' > 'Integrations' > 'Webhooks'
 * Create your Discord Bot (change name, avatar picture, ...) and press on 'Copy Webhook URL'
 * Create the 'arduino_secrets.h' file whit the following variables:
 * 
 * 1. Webhook URL without the starting 'https://discordapp.com'
 * #define SECRET_WEBHOOK "/api/webhooks/..." // replace all the content between the quotes
 * 
 * 2. enable ("true") or disable ("false") text on speech
 * #define SECRET_TTS "true"
 * 
 * 3. WiFi name of the network the Arduino MKR have to connect to surf the Internet
 * #define WIFI_SSID "" // put it inside the quotes
 * 
 * 4. WiFi password of the network the Arduino MKR have to connect to surf the Internet
 * #define WIFI_PWD "" // put it inside the quotes
*/
#include <WiFiNINA.h>
#include <ArduinoHttpClient.h>
#include "arduino_secrets.h"

const char server[] = "discordapp.com";

// its type could just be 'const int' but, this way, it take up less space
unsigned const short int port = 443;
int status = WL_IDLE_STATUS;

// delay is expressed in milliseconds, so you can express it in seconds * 1000
const unsigned int custom_delay = 5 * 1000;

WiFiSSLClient client;
HttpClient http_client = HttpClient(client, server, port);

void setup() {
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
  
  discord_send("Hello World");
}

void loop() {
}

void discord_send(String content) {
  Serial.println("Connecting to Discord");
  Serial.println("Message: " + content);
  Serial.print("TTS: ");
  Serial.println(SECRET_TTS);
  
  http_client.post(SECRET_WEBHOOK, "application/json", "{\"content\":\"" + content + "\", \"tts\":" + SECRET_TTS + "}");
  // read the status code and body of the response
  int statusCode = http_client.responseStatusCode();
  String response = http_client.responseBody();

  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.print("Response: ");
  Serial.println(response);
}
