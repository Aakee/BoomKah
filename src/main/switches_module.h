#ifndef SWITCHES_MODULE
#define SWITCHES_MODULE

#include "switch_handler.h"
#include "RGB_handler.h"
#include "blinker_handler.h"
#include "feedback_handler.h"

/*
  Game module.
  Player reads blinker colors, turns switches according to them, reads rgb color, and presses correct button. 
*/
class SwitchesModule {

  public:

    // Creator and destructor
    SwitchesModule(bool randomize = false);
    ~SwitchesModule();

    // Main function
    int run(SwitchStates* switchState, RGBHandler* rgbHandler, BlinkerHandler* blinkerHandler);

    // Returns if this module has been succesfully completed or not
    bool isCompleted() {return completed;}

  
  private:

    // Configuration


    // Member methods to help set the leds correctly
    void setBlinkers(BlinkerHandler*);
    void setRGB(RGBHandler*, SwitchStates*);

    // Member method to see if the current answer has been inserted correctly
    bool checkAnswer(SwitchStates*);

    // Gets new combination of blinkers
    void randomizeBlinkers();

    // Defaults
    int maxSuccessCount = 3;                  // Only matters if using randomized mode, otherwise hard-coded 3
    int defaultBlinkerColors[3] = {7,3,2};     // Default colors (indexes for possibleBlinkerValues)

    // Internal variables
    bool completed                = false;           // Tells if this module has been succcesfully completed or not
    bool randomize;
    int successCount              = 0;               // Current number of passed rounds
    bool buttonPreviouslyPressed  = false;           // Was one of the buttons pressed on the previous iteration; for buffering the button
    char currentBlinkers          = 0b0000;          // Current status of the blinkers
    char offset                   = 0;               // Random value for RGB calculation
    int currentRGB                = 0;               // Current color index of RGB


    // Lists all possible blinker combinations
    char possibleBlinkerValues[10] = {
      0b0001,
      0b0010,
      0b0011,
      0b0100,
      0b0101,
      0b0110,
      0b1000,
      0b1001,
      0b1010,
      0b1100,
  };

    // Maps blinker state to correct switch positions
    int blinkers2switches[16] {
        -1,                     // 0b0000
        up      + 3*up,         // 0b0001       red
        middle  + 3*down,       // 0b0010       green
        middle  + 3*up,         // 0b0011       red + green
        down    + 3*up,         // 0b0100       blue
        up      + 3*middle,     // 0b0101       red + blue
        down    + 3*down,       // 0b0110       green + blue
        -1,                     // 0b0111
        down    + 3*down,       // 0b1000       yellow
        down    + 3*middle,     // 0b1001       red + yellow
        up      + 3*down,       // 0b1010       green + yellow
        -1,                     // 0b1011
        middle  + 3*middle,     // 0b1100       blue + yellow
        -1,                     // 0b1101
        -1,                     // 0b1110
        -1,                     // 0b1111
    };

    // Maps RGB color to correct button
    int rgb2button[8] {
        3,      // red
        1,      // green
        1,      // blue
        2,      // yellow
        4,      // purple
        3,      // cyan
        4,      // white
        2,      // none
    };

};

#endif
