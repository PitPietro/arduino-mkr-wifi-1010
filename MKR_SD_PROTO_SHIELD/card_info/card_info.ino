/*
 * SD card info
 * 
 * This example shows how use the utility libraries on which the
 * SD library is based in order to get info about your SD card.
 * It's very useful for testing a card when you're not sure
 * whether its working or not.
 * 
 * Pin numbers reflect the default SPI pins for a couple of important boards:
 * 1) SDO (MOSI) pin 8 on Arduino MKR WiFi 1010 ~~~ pin 11 on Arduino Uno
 * 2) SDI (MISO) pin 10 on Arduino MKR WiFi 1010 ~~~ pin 12 on Arduino Uno
 * 3) CLK pin 9 on Arduino MKR WiFi 1010 ~~~ pin 13 on Arduino Uno
 * 4) CS - 4 on Arduino MKR WiFi 1010 (Make sure you call 'SD.begin(4)')
 * 
 * Docs:
 * <SD.h> https://www.arduino.cc/en/Reference/SD
 * <SD.h> notes https://www.arduino.cc/en/Reference/SDCardNotes
 * <SPI.h> https://www.arduino.cc/en/Reference/SPI
*/

#include <SPI.h>
#include <SD.h>

// set up variables using the SD utility library functions:

Sd2Card card;

SdVolume volume;

SdFile root;

const int chipSelect = 4;

void setup() {
  // initialize serial communication and wait for port to open
  Serial.begin(9600);
  // wait for serial port to connect. Needed for native USB port only
  while (!Serial);

  Serial.print("\nInitializing SD card...");

  if (!card.init(SPI_HALF_SPEED, chipSelect)) {
    Serial.println("initialization failed. Things to check:");
    Serial.println("* is a card inserted?");
    Serial.println("* is your wiring correct?");
    Serial.println("* did you change the chipSelect pin to match your shield or module?");
    while (1);
  } else {
    Serial.println("Wiring is correct and a card is present.");
  }

  // print the type of card
  Serial.print("\nCard type:\t");
  
  switch (card.type()) {
    case SD_CARD_TYPE_SD1: {
      Serial.println("SD1");
      break;
    }
    case SD_CARD_TYPE_SD2: {
      Serial.println("SD2");
      break;
    }
    case SD_CARD_TYPE_SDHC: {
      Serial.println("SDHC");
      break;
    }
    default:
      Serial.println("Unknown");
  }

  // try to open the 'volume'/'partition' - it should be FAT16 or FAT32
  if (!volume.init(card)) {
    Serial.println("Could not find FAT16/FAT32 partition.\nMake sure you've formatted the card");
    while (1);
  }

  Serial.print("Clusters:\t");
  Serial.println(volume.clusterCount());
  Serial.print("Blocks x Cluster:\t");
  Serial.println(volume.blocksPerCluster());
  Serial.print("Total Blocks:\t");
  Serial.println(volume.blocksPerCluster() * volume.clusterCount());

  // print the type and size of the first FAT-type volume
  uint32_t volumesize;

  Serial.print("\nVolume type is: FAT");
  Serial.println(volume.fatType(), DEC);

  // clusters are collections of blocks
  volumesize = volume.blocksPerCluster();

  // you'll have a lot of clusters
  volumesize *= volume.clusterCount();

  // SD card blocks are always 512 bytes (2 blocks are 1KB)
  volumesize /= 2;
  
  Serial.print("Volume size (Kb):\t");
  Serial.println(volumesize);
  Serial.print("Volume size (Mb):\t");
  
  volumesize /= 1024;
  
  Serial.println(volumesize);
  Serial.print("Volume size (Gb):\t");
  Serial.println((float)volumesize / 1024.0);
  
  Serial.println("\nFiles found on the card (name, date and size in bytes): ");
  root.openRoot(volume);

  // list all files in the card with date and size
  root.ls(LS_R | LS_DATE | LS_SIZE);
  root.close();
}

void loop(void) {
}
