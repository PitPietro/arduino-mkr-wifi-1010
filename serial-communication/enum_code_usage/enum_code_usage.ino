/*
  Enum

  forum: https://forum.arduino.cc/index.php?topic=70906.0
*/
#include "enum_control.h"


void setup() {
  // initialize serial communication and wait for port to open
  Serial.begin(9600);
  // wait for serial port to connect. Needed for native USB port only
  while (!Serial);

  controlState(Unknown);
  controlState(True);
  controlState(False);
}

void loop() {
}

void controlState(state value) {

  // this if-else statement can be replaced by a switch-case because an enum always return an integer
  // and switch-case only works with integer values

  Serial.println("~~~~~~~~~~~~~~~~~~~~~~");

  if (value == True) {
    Serial.println("if-else/ state set to true");
  }
  else if (value == False) {
    Serial.println("if-else/ state set to false");
  }
  else if (value == Unknown) {
    Serial.println("if-else/ state set to unknown");
  }

  Serial.print("if-else/ value: ");
  Serial.println(value);

  Serial.println("~~~~~~~~~~~~~~~~~~~~~~");

  switch (value) {
    case True: {
        Serial.println("switch-case/ state set to true");
        Serial.print("switch-case/ value: ");
        Serial.println(value);
      }
      break;
    case False: {
        Serial.println("switch-case/ state set to false");
        Serial.print("switch-case/ value: ");
        Serial.println(value);
      }
      break;
    case Unknown: {
        Serial.println("switch-case/ state set to unknown");
        Serial.print("switch-case/ value: ");
        Serial.println(value);
      }
      break;
    default: // this case won't really never reached since a value different from the three above would lead to a compiling error
      Serial.println("switch-case/ default");
  }
}
