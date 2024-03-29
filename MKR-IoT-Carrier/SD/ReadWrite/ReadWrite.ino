#include <Arduino_MKRIoTCarrier.h>

MKRIoTCarrier carrier;

File myFile;

void setup() {
  CARRIER_CASE = false;
  carrier.begin();

  // Initialize serial communication at 9600 baud rate
  Serial.begin(9600);
  // Wait for serial port to connect. Needed for native USB port only.
  while (!Serial);


  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println(" failed!");
    while (1);
  }
  Serial.println(" done.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("test.txt", FILE_WRITE);

  // if the file opened okay, write to it
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println("Hello, World!");
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error
    Serial.println("error opening test.txt");
  }

  // re-open the file for reading:
  myFile = SD.open("test.txt");
  if (myFile) {
    Serial.println("test.txt:");

    // read from the file until there's nothing else in it
    while (myFile.available()) {
      Serial.write(myFile.read());
    }

    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error
    Serial.println("error opening test.txt");
  }
}

void loop() {
  // nothing happens after setup
}
