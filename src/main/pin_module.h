#ifndef PIN_MODULE
#define SWITCHES_MODULE

#include "switch_handler.h"
#include "RGB_handler.h"
#include "blinker_handler.h"
#include "feedback_handler.h"

/*
  Game module.
  
*/
class PINModule {

  public:

    // Creator and destructor
    PINModule();
    ~PINModule();

    // Main function
    int run(SwitchStates* switchState, RGBHandler* rgbHandler, BlinkerHandler* blinkerHandler);

    // Returns if this module has been succesfully completed or not
    bool isCompleted() {return completed;}

  
  private:

    // Configuration


    // Member methods to help set the leds correctly
    void setBlinkers(BlinkerHandler*, SwitchStates*);
    void setRGB(RGBHandler*);

    // Member method to see if the current answer has been inserted correctly
    bool checkAnswer(SwitchStates*);

    // Defaults
    int maxSuccessCount = 1;                  // Pelase don't change this, the code doesn't currently allow more rounds

    // Internal variables
    bool completed                      = false;           // Tells if this module has been succcesfully completed or not
    int successCount                    = 0;               // Current number of passed rounds
    bool buttonsPreviouslyPressed[4]    = {false, false, false, false,};         // Was one of the buttons pressed on the previous iteration; for buffering the button
    char currentBlinkers                = 0b0000;          // Current status of the blinkers
    int currentlyPressed[4]             = {0};
    bool shouldReset                    = false;

    const int switches2pin[36] {
        1,3,2,4,
        3,1,2,4,
        2,4,1,3,
        4,1,3,2,
        2,3,4,1,
        3,4,2,1,
        4,3,2,1,
        4,2,3,1,
        2,1,4,2,
    };

    int switches2blinkers[6] {
        0b1010,
        0b0100,
        0b0001,
        0b0101,
        0b0010,
        0b1000,
    };

    /*
    char switches2pin2[9] {
        0b00100111,
        0b10000111,
        0b01110010,
        0b11001001,
        0b01101100,
        0b10110100,
        0b11100100,
        0b11011000,
        0b01001110,
    };
    */

};

#endif
