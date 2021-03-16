// TODO let the user select which song to play by using the buttons (and the SD card to store the songs, if they're too many)

/*
   Play Melody on MKR IoT C arrier

   Using all the constants made fot the notes (inside "musical-notes.h"), you
   can create the melody you want. Please refer to the wiki page linked below if
   you want to create your own melody

   Reference: https://www.arduino.cc/en/Tutorial/BuiltInExamples/toneMelody
   BPM to sec:
   1) https://toolstud.io/music/bpm.php
   2) https://tomhess.net/Tools/DelayCalculator.aspx
   Wiki: https://github.com/PitPietro/arduino-mkr-wifi-1010/wiki/output-folder
*/

#include <Arduino_MKRIoTCarrier.h>
#include "musical-constants.h"
#include "musical-notes.h"
#include "songs.h"

MKRIoTCarrier carrier;

// global constants
unsigned const short int DEFAULT_BPM = 60;

/*
   Translate BPM to the milliseconds of four musical measures

   i.e. 60 BPM = 1 second * 4 musical measures = 4 seconds = 4'000 ms
*/
double BPMToMillisec(int bpm) {
  float beat_per_sec = (double)bpm / 60;
  float beat_per_millisec = beat_per_sec * 1000;
  return beat_per_millisec * 4;
}

/*
   Return the number of notes. The melody has MAX_NOTES dimension to fit
   a large melody, but can be shorter, so it's important dot to play a lot
   of useless pauses.

   The melody must have END as the last element, it wouldn't be correct
   to stop count the melody dimension when there's a PAUSE (or more pauses)
*/
int melodyDimension(double melody[2][MAX_NOTES]) {
  // return the number of notes
  // both the 1st and the 2nd arrays must have the same lenght

  byte i, j;
  byte dims[ROWS] = {0, 0};

  for (i = 0; i < ROWS; i++) {
    j = 0;
    while (melody[i][j] != END) {
      j++;
      dims[i]++;
    }

    // for(j = 0; j < (sizeof(melody[i]) / sizeof(melody[i][0])); j++) {}
  }

  // notes must be as much as the durations
  if (dims[0] != dims[1]) {
    return -1;
  } else {
    return dims[0];
  }
}

void controlNote (double note) {
  // replaced the useless switch-case with an ugly if-else clause
  if (note == WHOLE) {
    // draw the semibreve on the shield screen
  } else if (note == HALF) {
    // draw the minim note on the shield screen
  } else if (note == QUARTER) {
    // draw the crotchet note on the shield screen
  } else if (note == EIGHTH) {
    // draw the quaver note on the shield screen
  } else if (note == SIXTEENTH) {
    // draw the semiquaver note on the shield screen
  } else if (note == THIRTY_SECOND) {
    // draw the demisemiquaver note on the shield screen
  } else if (note == SIXTY_FOURTH) {
    // draw the hemidemisemiquaver note on the shield screen
  } else if (note == D_WHOLE) {
    // draw the dotted semibreve on the shield screen
  } else if (note == D_HALF) {
    // draw the dotted minim note on the shield screen
  } else if (note == D_QUARTER) {
    // draw the dotted crotchet note on the shield screen
  } else if (note == D_EIGHTH) {
    // draw the dotted quaver note on the shield screen
  } else if (note == D_SIXTEENTH) {
    // draw the dotted semiquaver note on the shield screen
  } else if (note == D_THIRTY_SECOND) {
    // draw the dotted demisemiquaver note on the shield screen
  } else if (note == D_SIXTY_FOURTH) {
    // draw the dotted hemidemisemiquaver note on the shield screen
  } else {
    // the note does not exists
  }
}

void playMelody(double melody[2][MAX_NOTES]) {
  // melody contains the notes (in the 1st array) and the notes' duration (in
  // the 2nd array) iterate over the notes of the melody

  int dim = melodyDimension(melody);
  int thisNote;

  for (thisNote = 0; thisNote < dim; thisNote++) {

    // to calculate the note duration, take one second divided by the note type
    // e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.

    // int noteDuration = 1000 / melody[1][thisNote];

    // 4'000 ms = 4 seconds = 1 second * 4 musical measures = 60 BMP
    double timeMillis = BPMToMillisec(DEFAULT_BPM);
    double noteDuration = timeMillis * melody[1][thisNote];

    // some debugging info on the Serial Monitor
    // Serial.print(thisNote);
    // Serial.print(") ");

    // TODO n°1: replace the 'print' statements by displaying the current note on the screen
    // TODO n°2: make a "draw" about the current note using the draw functions

    // exit status 1 - switch quantity not an integer
    // emun do not works: use a Dictionary ?
    controlNote(melody[1][thisNote]);


    // add a pause in milliseconds to avoid listen the melody like an always
    // continuous note that only changes tonality (frequency)
    int pauseBetweenNotes = 10;

    // start the tone playing
    carrier.Buzzer.sound(melody[0][thisNote]);

    // play the current note for the given duration subtracting
    // 'pauseBetweenNotes'
    delay(noteDuration - pauseBetweenNotes);

    // stop the tone playing
    carrier.Buzzer.noSound();

    // wait for 'pauseBetweenNotes' to avoid going out of time
    delay(pauseBetweenNotes);
  }
}

void setup() {
  CARRIER_CASE = false;
  carrier.begin();

  playMelody(count_time);
  // playMelody(white_coral_bells);
  // playMelody(base_base);
  playMelody(chorale_38_first);
}

void loop() {
  // playMelody(base_base);
  // no need to repeat the melody
}
