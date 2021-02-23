/*
 * Play Melody
 * 
 * Using all the constants made fot the notes (inside "musical-notes.h"), you can create the melody you want.
 * Please refer to the wiki page linked below if you want to create your own melody
 * 
 * Reference: https://www.arduino.cc/en/Tutorial/BuiltInExamples/toneMelody
 * BPM to sec:
 * 1) https://toolstud.io/music/bpm.php
 * 2) https://tomhess.net/Tools/DelayCalculator.aspx
 * Wiki: https://github.com/PitPietro/arduino-mkr-wifi-1010/wiki/output-folder
 */
#include "musical-notes.h"

// global constants
unsigned const short int DEFAULT_BPM = 60;
unsigned const int MAX_NOTES = 100;
unsigned const char ROWS = 2;

// connect the buzzer to pin 3
unsigned const char buzzer = 3;

// notes constants
const float WHOLE = 1;
const float HALF = 0.5; 
const float QUARTER = 0.25;
const float EIGHTH = 0.125;
const float SIXTEENTH = 0.0625;
const float THIRTY_SECOND = 0.03125;
const float SIXTY_FOURTH = 0.015625;

// dotted constants starts with capital 'D'
const float D_WHOLE = 1.5;
const float D_HALF = 0.75; 
const float D_QUARTER = 0.375;
const float D_EIGHTH = 0.1875;
const float D_SIXTEENTH = 0.09375;
const float D_THIRTY_SECOND = 0.046875;
const float D_SIXTY_FOURTH = 0.023438;

// notes in the melody
// note durations: 4 = quarter note, 8 = eighth note, etc.

// Please Note: finish the melody with 'END' in both the sub-arrays
int base_melody[ROWS][MAX_NOTES] = {
  {C4, G3, G3, A3, G3, 0, B3, C4, END},
  {QUARTER, EIGHTH, EIGHTH, QUARTER, QUARTER, QUARTER, QUARTER, QUARTER, END}
};

// G3 (3rd string - guidar)
float happyBirthday[ROWS][MAX_NOTES] = {
  {PAUSE, G3, G3, A3, G3, C4, B3, G3, G3, A3, G3, D4, C4, G3, G3, G4, E4, C4, B3, A3, F4, F4, E4, C4, D4, C4, END},
  {HALF, D_EIGHTH, SIXTEENTH, QUARTER, QUARTER, QUARTER, HALF, D_EIGHTH, SIXTEENTH, QUARTER, QUARTER, QUARTER, HALF, D_EIGHTH, SIXTEENTH, QUARTER, QUARTER, QUARTER, QUARTER, HALF, D_EIGHTH, SIXTEENTH, QUARTER, QUARTER, QUARTER, HALF, END}
};

float base_base[2][MAX_NOTES] = {
  {C3, D3, E3, F3, G3, A3, B3, C4, C4, B3, A3, G3, F3, E3, D3, C3, END},
  {QUARTER, QUARTER, QUARTER, QUARTER, QUARTER, QUARTER, QUARTER, QUARTER, QUARTER, QUARTER, QUARTER, QUARTER, QUARTER, QUARTER, QUARTER, QUARTER, END}
};

/*
 * Translate BPM to the milliseconds of four musical measures
 *
 * i.e. 60 BPM = 1 second * 4 musical measures = 4 seconds = 4'000 ms 
*/
float BPMToMillisec(int bpm) {
    float beat_per_sec = (float)bpm / 60;
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
int melodyDimension(float melody[2][MAX_NOTES]) {
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

void playMelody(float melody[2][MAX_NOTES]) {
  // melody contains the notes (in the 1st array) and the notes' duration (in the 2nd array)
  // iterate over the notes of the melody

  int dim = melodyDimension(melody);
  int thisNote;
  
  for (thisNote = 0; thisNote < dim; thisNote++) {
    
    // to calculate the note duration, take one second divided by the note type
    // e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.

    // int noteDuration = 1000 / melody[1][thisNote];

    // 4'000 ms = 4 seconds = 1 second * 4 musical measures = 60 BMP
    float timeMillis = BPMToMillisec(DEFAULT_BPM);
    float noteDuration = timeMillis * melody[1][thisNote];

    // some debugging info on the Serial Monitor
    Serial.print(thisNote);
    Serial.print(") ");
    Serial.print(melody[0][thisNote]);
    Serial.print(" --> note duration: ");
    Serial.print(noteDuration);
    Serial.print(" = ");
    Serial.print(timeMillis);
    Serial.print(" * ");
    Serial.println(melody[1][thisNote]);
    
    tone(buzzer, melody[0][thisNote]);
    
    delay(noteDuration);

    // stop the tone playing
    noTone(buzzer);
  }
}

void setup() {  
  // set buzzer as an output
  pinMode(buzzer, OUTPUT);

  // use the Serial Monitor for debugging purpose
  Serial.begin(9600);
  // wait for serial port to connect. Needed for native USB port only
  while (!Serial);
  
  // playMelody(base_melody);
  playMelody(happyBirthday);
  // playMelody(base_base);
}

void loop() {
  // playMelody(base_base);
  // no need to repeat the melody
}
