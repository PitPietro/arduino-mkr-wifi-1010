/*
 * Play Melody
 * 
 * Using all the constants made fot the notes (inside "pitches.h"), you can create the melody you want.
 * 
 * Reference: https://www.arduino.cc/en/Tutorial/BuiltInExamples/toneMelody
 */
#include "pitches.h"

// notes in the melody
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

// connect the buzzer to pin 3
unsigned const char buzzer = 3;

void setup() {
  // set buzzer as an output
  pinMode(buzzer, OUTPUT);
  
  // iterate over the notes of the melody
  
  for (int thisNote = 0; thisNote < 8; thisNote++) {
    
    // to calculate the note duration, take one second divided by the note type
    // e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.

    int noteDuration = 1000 / noteDurations[thisNote];

    tone(buzzer, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them
    // the note's duration + 30% seems to work well
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);

    // stop the tone playing
    noTone(buzzer);
  }
}

void loop() {
  // no need to repeat the melody.
}
