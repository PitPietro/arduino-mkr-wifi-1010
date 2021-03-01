/*
 * Play Melody
 *
 * Using all the constants made fot the notes (inside "musical-notes.h"), you
 * can create the melody you want. Please refer to the wiki page linked below if
 * you want to create your own melody
 *
 * Reference: https://www.arduino.cc/en/Tutorial/BuiltInExamples/toneMelody
 * BPM to sec:
 * 1) https://toolstud.io/music/bpm.php
 * 2) https://tomhess.net/Tools/DelayCalculator.aspx
 * Wiki: https://github.com/PitPietro/arduino-mkr-wifi-1010/wiki/output-folder
 */
#include "musical-constants.h"
#include "musical-notes.h"

// global constants
unsigned const short int DEFAULT_BPM = 60;
unsigned const int MAX_NOTES = 100;
unsigned const char ROWS = 2;

// connect the buzzer to pin 3
unsigned const char buzzer = 3;

// notes in the melody
// note durations: 4 = quarter note, 8 = eighth note, etc.

// Please Note: finish the melody with 'END' in both the sub-arrays
double base_melody[ROWS][MAX_NOTES] = {
  {C4, G3, G3, A3, G3, 0, B3, C4, END},
  {QUARTER, EIGHTH, EIGHTH, QUARTER, QUARTER, QUARTER, QUARTER, QUARTER, END}
};

// G3 (3rd string - guidar)
double happyBirthday[ROWS][MAX_NOTES] = {
  {PAUSE, G3, G3, A3,
  G3, C4, B3, G3,
  G3, A3, G3, D4,
  C4, G3, G3, G4,
  E4, C4, B3, A3,
  F4, F4, E4, C4,
  D4, C4, END
  },
  {HALF, D_EIGHTH, SIXTEENTH, QUARTER,
  QUARTER, QUARTER, HALF, D_EIGHTH,
  SIXTEENTH, QUARTER, QUARTER, QUARTER,
  HALF, D_EIGHTH, SIXTEENTH, QUARTER,
  QUARTER, QUARTER, QUARTER, HALF,
  D_EIGHTH, SIXTEENTH, QUARTER, QUARTER,
  QUARTER, HALF, END
  }
};

double count_time[2][MAX_NOTES] = {
  {C3, C3, C3, C3, END},
  {QUARTER, QUARTER, QUARTER, QUARTER, END}
};

/*
 * White Coral Bells from "Berklee Basic Guitar part 1" by William Leavitt
 *
 * The melody's arrays wrap at each bar to allow a better code readability
*/
double white_coral_bells[2][MAX_NOTES]{
  {
    C4, B3, A3,        //  1
    G3, E3,            //  2
    F3, A3, G3, F3,    //  3
    E3,                //  4
    C3, E3, D3, F3,    //  5
    E3, G3, C4, E4,    //  6
    D4, B3,            //  7
    C4, G3, G3, G3,    //  8
    C4, B3, A3,        //  9 = 1
    G3, E3,            // 10 = 2
    F3, A3, G3, F3,    // 11 = 3
    E3,                // 12 = 4
    C3, E3, D3, F3,    // 13 = 5
    E3, G3, C4, E4,    // 14 = 6
    D4, B3,            // 15 = 7
    C4, G4, G4,        // 16
    E4, C4, B3, D4,    // 17
    C4, B3, A3, G3,    // 18
    F3, G3, F3,        // 19
    E3, G3, C3, PAUSE, // 20
    END
  },
  {
    HALF,    QUARTER, QUARTER,          //  1
    D_HALF,  QUARTER,                   //  2
    QUARTER, QUARTER, QUARTER, QUARTER, //  3
    WHOLE,                              //  4
    QUARTER, QUARTER, QUARTER, QUARTER, //  5
    QUARTER, QUARTER, QUARTER, QUARTER, //  6
    HALF,    HALF,                      //  7
    QUARTER, QUARTER, QUARTER, QUARTER, //  8
    HALF,    QUARTER, QUARTER,          //  9 = 1
    D_HALF,  QUARTER,                   // 10 = 2
    QUARTER, QUARTER, QUARTER, QUARTER, // 11 = 3
    WHOLE,                              // 12 = 4
    QUARTER, QUARTER, QUARTER, QUARTER, // 13 = 5
    QUARTER, QUARTER, QUARTER, QUARTER, // 14 = 6
    HALF,    HALF,                      // 15 = 7
    QUARTER, HALF,    QUARTER,          // 16
    QUARTER, QUARTER, QUARTER, QUARTER, // 17
    QUARTER, QUARTER, QUARTER, QUARTER, // 18
    QUARTER, HALF,    QUARTER,          // 19
    QUARTER, QUARTER, QUARTER, PAUSE,   // 20
    END
  }
};


/*
 * Long, Long Ago from "Berklee Basic Guitar part 1" by William Leavitt
 *
 * The melody's arrays wrap at each bar to allow a better code readability
*/
double long_long_ago_third[2][MAX_NOTES]{
  {
    C3, C3, D3,         //  1
    E3, E3, F3,         //  2
    G3, A3, G3,         //  3
    C4, B3, A3, G3,     //  4
    B3, A3, G3,         //  5
    F3,                 //  6
    A3, G3, F3,         //  7
    E3,                 //  8
    E3, E3, F3,         //  9
    G3, A3, B3, C4, D4, // 10
    E4, D4, C4, B3,     // 11
    D4, C4, B3, A3,     // 12
    G3, F3, E3,         // 13
    F3, E3, D3,         // 14
    E3, G3, A3, F3,     // 15
    E3, E3, G3,         // 16
    B3, A3, G3,         // 17
    F3, G3, G3,         // 18
    A3, G3, F3,         // 19
    E3, E4, D4, C4,     // 20
    B3, A3, G3,         // 21
    F3, B3, B3,         // 22
    A3, G3, F3,         // 23
    E3, E3, D3,         // 24
    C3, C3, D3,         // 25 = 1
    E3, E3, F3,         // 26 = 2
    G3, A3, G3,         // 27 = 3
    C4, B3, A3, G3,     // 28 = 4
    B3, A3, G3,         // 29 = 5
    F3, G3, F3,         // 30
    M3, G3, A3, F3,     // 31
    M3, G3, C4,         // 32
    END
  },
  {
    HALF,    QUARTER, QUARTER,                 //  1
    HALF,    QUARTER, QUARTER,                 //  2
    HALF,    QUARTER, QUARTER,                 //  3
    QUARTER, QUARTER, QUARTER, QUARTER,        //  4
    HALF,    QUARTER, QUARTER,                 //  5
    WHOLE,                                     //  6
    HALF,    QUARTER, QUARTER,                 //  7
    WHOLE,                                     //  8
    HALF,    QUARTER, QUARTER,                 //  9
    QUARTER, EIGHTH, EIGHTH, QUARTER, QUARTER, // 10
    QUARTER, QUARTER, QUARTER, QUARTER,        // 11
    QUARTER, QUARTER, QUARTER, QUARTER,        // 12
    HALF,    QUARTER, QUARTER,                 // 13
    HALF,    QUARTER, QUARTER,                 // 14
    QUARTER, QUARTER, QUARTER, QUARTER,        // 15
    HALF,    QUARTER, QUARTER,                 // 16
    HALF,    QUARTER, QUARTER,                 // 17
    HALF,    QUARTER, QUARTER,                 // 18
    HALF,    QUARTER, QUARTER,                 // 19
    QUARTER, QUARTER, QUARTER, QUARTER,        // 20
    HALF,    QUARTER, QUARTER,                 // 21
    HALF,    QUARTER, QUARTER,                 // 22
    HALF,    QUARTER, QUARTER,                 // 23
    HALF,    QUARTER, QUARTER,                 // 24
    HALF,    QUARTER, QUARTER,                 // 25
    HALF,    QUARTER, QUARTER,                 // 26
    HALF,    QUARTER, QUARTER,                 // 27
    QUARTER, QUARTER, QUARTER, QUARTER,        // 28
    HALF,    QUARTER, QUARTER,                 // 29
    HALF,    QUARTER, QUARTER,                 // 30
    QUARTER, QUARTER, QUARTER, QUARTER,        // 31
    QUARTER, QUARTER, HALF,                    // 32
    END
  }
};

/*
 * Translate BPM to the milliseconds of four musical measures
 *
 * i.e. 60 BPM = 1 second * 4 musical measures = 4 seconds = 4'000 ms
 */
double BPMToMillisec(int bpm) {
  float beat_per_sec = (double)bpm / 60;
  float beat_per_millisec = beat_per_sec * 1000;
  return beat_per_millisec * 4;
}

/*
 * Return the number of notes. The melody has MAX_NOTES dimension to fit
 * a large melody, but can be shorter, so it's important dot to play a lot
 * of useless pauses.
 *
 * The melody must have END as the last element, it wouldn't be correct
 * to stop count the melody dimension when there's a PAUSE (or more pauses)
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
    Serial.print(melody[0][thisNote]);
    Serial.print(" --> note duration: ");
    Serial.print(noteDuration);
    Serial.print(" = ");
    Serial.print(timeMillis);
    Serial.print(" * ");
    Serial.println(melody[1][thisNote]);

    // add a pause in milliseconds to avoid listen the melody like an always
    // continuous note that only changes tonality (frequency)
    int pauseBetweenNotes = 10;

    // start the tone playing
    tone(buzzer, melody[0][thisNote]);

    // play the current note for the given duration subtracting
    // 'pauseBetweenNotes'
    delay(noteDuration - pauseBetweenNotes);

    // stop the tone playing
    noTone(buzzer);

    // wait for 'pauseBetweenNotes' to avoid going out of time
    delay(pauseBetweenNotes);
  }
}

void setup() {
  // set buzzer as an output
  pinMode(buzzer, OUTPUT);

  // use the Serial Monitor for debugging purpose
  Serial.begin(9600);
  // wait for serial port to connect. Needed for native USB port only
  while (!Serial)
    ;

  playMelody(count_time);
  playMelody(white_coral_bells);
  // playMelody(base_base);
}

void loop() {
  // playMelody(base_base);
  // no need to repeat the melody
}
