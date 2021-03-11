#define MAX_NOTES 150
#define ROWS 2

// G3 (3rd string - guidar)
double happyBirthday[ROWS][MAX_NOTES] = {
  { PAUSE, G3, G3, A3,
    G3, C4, B3, G3,
    G3, A3, G3, D4,
    C4, G3, G3, G4,
    E4, C4, B3, A3,
    F4, F4, E4, C4,
    D4, C4, END
  },
  { HALF, D_EIGHTH, SIXTEENTH, QUARTER,
    QUARTER, QUARTER, HALF, D_EIGHTH,
    SIXTEENTH, QUARTER, QUARTER, QUARTER,
    HALF, D_EIGHTH, SIXTEENTH, QUARTER,
    QUARTER, QUARTER, QUARTER, HALF,
    D_EIGHTH, SIXTEENTH, QUARTER, QUARTER,
    QUARTER, HALF, END
  }
};

// Please Note: finish the melody with 'END' in both the sub-arrays
double base_melody[ROWS][MAX_NOTES] = {
  {C4, G3, G3, A3, G3, 0, B3, C4, END},
  {QUARTER, EIGHTH, EIGHTH, QUARTER, QUARTER, QUARTER, QUARTER, QUARTER, END}
};

double count_time[2][MAX_NOTES] = {
  {C3, C3, C3, C3, END},
  {QUARTER, QUARTER, QUARTER, QUARTER, END}
};

/*
   White Coral Bells from "Berklee Basic Guitar part 1" by William Leavitt

   The melody's arrays wrap at each bar to allow a better code readability
*/
double white_coral_bells[2][MAX_NOTES] {
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
   Long, Long Ago from "Berklee Basic Guitar part 1" by William Leavitt

   The melody's arrays wrap at each bar to allow a better code readability
*/
double long_long_ago_third[2][MAX_NOTES] {
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
    E3, G3, A3, F3,     // 31
    E3, G3, C4,         // 32
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
