/*
 * Play Melody
 * 
 * Using all the constants made fot the notes (inside "pitches.h"), you can create the melody you want.
 * 
 * Reference: https://www.arduino.cc/en/Tutorial/BuiltInExamples/toneMelody
 */
#include "pitches.h"

// global variables
unsigned const int MAX_NOTES = 100;
unsigned const char ROWS = 2;
// connect the buzzer to pin 3
unsigned const char buzzer = 3;

// notes in the melody
// note durations: 4 = quarter note, 8 = eighth note, etc.

// Please Note: finish the melody with 'END' in both the sub-arrays
int base_melody[2][MAX_NOTES] = {
  {NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4, END},
  {4, 8, 8, 4, 4, 4, 4, 4, END}
};

int melodyDimension(int melody[2][MAX_NOTES]) {
  // return the number of notes
  // both the 1st and the 2nd arrays must have the same lenght

  byte i, j;
  byte dims[ROWS] = {0, 0};
  
  for(i = 0; i < ROWS; i++) {
    j = 0;
    while(melody[i][j] != -1) {
      j++;
      dims[i]++;
      Serial.print(dims[i]);
      Serial.print(" - ");
      Serial.print(melody[i][j]);
      Serial.print("\n");
    }
    
    // for(j = 0; j < (sizeof(melody[i]) / sizeof(melody[i][0])); j++) {}
  }

  Serial.print("The dimension are ");
  Serial.print(dims[0]);
  Serial.print(" and ");
  Serial.print(dims[1]);

  // notes must be as much as the durations
  if(dims[0] != dims[1]) {
    return -1;
  } else {
    return dims[0];
  }
}

void playMelody(int melody[2][MAX_NOTES]) {
  // melody contains the notes (in the 1st array) and the notes' duration (in the 2nd array)
  // iterate over the notes of the melody

  int dim = melodyDimension(melody);
  int thisNote;
  
  for (thisNote = 0; thisNote < dim; thisNote++) {
    
    // to calculate the note duration, take one second divided by the note type
    // e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.

    int noteDuration = 1000 / melody[1][thisNote];

    tone(buzzer, melody[0][thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them
    // the note's duration + 30% seems to work well
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);

    // stop the tone playing
    noTone(buzzer);
  }
}

void setup() {
  // initialize serial communication and wait for port to open
  Serial.begin(9600);
  // wait for serial port to connect. Needed for native USB port only
  while (!Serial);
  
  // set buzzer as an output
  pinMode(buzzer, OUTPUT);
  
  playMelody(base_melody);
}

void loop() {
  // no need to repeat the melody.
}
