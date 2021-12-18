#include <ArduinoBLE.h>

// creating the service
BLEService newService("180A");

// creating the Analog Value characteristic
BLEUnsignedCharCharacteristic randomReading("2A58", BLERead | BLENotify);

// creating the LED characteristic
BLEByteCharacteristic switchChar("2A57", BLERead | BLEWrite);

#define CONTROL_LED_PIN LED_BUILTIN
#define RED_PIN 2
#define GREEN_PIN 3
#define BLUE_PIN 4

long previousMillis = 0;

/**
   Original tutorial: https://docs.arduino.cc/tutorials/mkr-wifi-1010/enabling-ble
*/
void setup() {
  // initialize serial communication
  Serial.begin(9600);
  //starts the program if we open the serial monitor
  while (!Serial);

  // initialize 'controlLedPin' pin to indicate when a central is connected
  pinMode(CONTROL_LED_PIN, OUTPUT);

  // initialize RGB LED pins
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  // initialize BLE library
  if (!BLE.begin()) {
    Serial.println("starting BLE failed!");
    while (1);
  }

  // set the name that will appear when scanning for bluetooth devices
  BLE.setLocalName("MKR WiFi 1010");
  BLE.setAdvertisedService(newService);

  // add characteristics to a service
  newService.addCharacteristic(switchChar);
  newService.addCharacteristic(randomReading);

  // add the service
  BLE.addService(newService);

  // set initial value for characteristics
  switchChar.writeValue(0);
  randomReading.writeValue(0);

  // start advertising the service
  BLE.advertise();
  Serial.println("Bluetooth device active, waiting for connections...");
}

void loop() {
  // wait for a BLE central
  BLEDevice central = BLE.central();

  // if a central is connected to the peripheral
  if (central) {
    Serial.print("Connected to central: ");

    // print central's BT address
    Serial.println(central.address());

    // turn on the "control" LED to indicate the connection
    digitalWrite(CONTROL_LED_PIN, HIGH);

    // check the battery level every 200ms while the central is connected:
    while (central.connected()) {
      long currentMillis = millis();

      // if 200ms have passed, check the battery level
      if (currentMillis - previousMillis >= 200) {
        previousMillis = currentMillis;

        // int randomValue = analogRead(A1);
        // randomReading.writeValue(randomValue);

        if (switchChar.written()) {
          const int numericValue = switchChar.value();
          const String hexValue = String(numericValue, HEX);
          
          Serial.print(numericValue);
          Serial.print("\t");
          Serial.println(hexValue);

          // it only handles 1 component from the RGB LED
          // i.e. given 'ffccbb' as input, it prints: 'ff' on the Serial Monitor
        }
      }
    }

    // when the central disconnects, turn off the control LED
    digitalWrite(CONTROL_LED_PIN, LOW);
    Serial.print("Disconnected from central: ");
    Serial.println(central.address());
  }
}
