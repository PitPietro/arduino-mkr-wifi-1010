/*
 * Play Melody
 * 
 * Using all the constants made fot the notes (inside "pitches.h"), you can create the melody you want.
 * Assuming the base time of 4/4, the notes are:
 * - whole note -------> 1000 / 1 = 1000
 * - half note --------> 1000 / 2 = 500
 * - quarter note -----> 1000 / 4 = 250
 * - eighth note ------> 1000 / 8 = 125
 * - sixteenth note ---> 1000 / 16 = 62.5
 * - thirty-two note --> 1000 / 32 = 32.25
 * 
 * Notes with dot:
 * - dotted whole note ------> 3/2 <---> (1000 / 1) + (1000 / 2) = 1000 / (2/3) = 1500
 * - dotted half note -------> 4/3 <---> (1000 / 2) + (1000 / 4) = 1000 / (4/3) = 750
 * - dotted quarter note ----> 6/16 <---> (1000 / 4) + (1000 / 8) = 1000 / (8/3) = 375
 * - dotted eighth note -----> 6/32 <---> (1000 / 8) + (1000 / 16) = 1000 / (16/3) = 187.5 
 * - dotted sixteenth note --> 3/32 <---> (1000 / 16) + (1000 / 32) = 1000 / x = 93.75
 * 
 * Note: 1000 ms = 1 sec = 60 BPM (Beats per Minutes)
 * 
 * Reference: https://www.arduino.cc/en/Tutorial/BuiltInExamples/toneMelody
 * BPM to sec: https://toolstud.io/music/bpm.php
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
  {C4, G3, G3, A3, G3, 0, B3, C4, END},
  {4, 8, 8, 4, 4, 4, 4, 4, END}
};

// https://external-content.duckduckgo.com/iu/?u=http%3A%2F%2Fwww.appybirthday.org%2Fwp-content%2Fuploads%2F2014%2F08%2Fhappy-birthday-guitar-chrods-tabs.gif&f=1&nofb=1

// G3 (3rd string - guidar)
// e.g. quarter note = 1000 / 4 (250), eighth note = 1000/8 (125), etc.


int happyBirthday[2][MAX_NOTES] = {
  {PAUSE, G3, G3, A3, G3, C4, B3, G3, G3, A3, G3, D4, C4, G3, G3, G4, E4, C4, B3, A3, F4, F4, E4, C4, D4, C4, END},
  {2, 8/3, 8, 4, 4, 4, 2, 8/3, 8, 4, 4, 4, 2, 8/3, 8, 4, 4, 4, 4, 2, 8/3, 8, 4, 4, 4, 2, END}
};

int melodyDimension(int melody[2][MAX_NOTES]) {
  // return the number of notes
  // both the 1st and the 2nd arrays must have the same lenght

  byte i, j;
  byte dims[ROWS] = {0, 0};
  
  for(i = 0; i < ROWS; i++) {
    j = 0;
    while(melody[i][j] != END) {
      j++;
      dims[i]++;
    }
    
    // for(j = 0; j < (sizeof(melody[i]) / sizeof(melody[i][0])); j++) {}
  }

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
  // set buzzer as an output
  pinMode(buzzer, OUTPUT);
  
  // playMelody(base_melody);
  playMelody(happyBirthday);
}

void loop() {
  // no need to repeat the melody
}
