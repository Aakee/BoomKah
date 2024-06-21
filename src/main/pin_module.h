#ifndef PIN_MODULE
#define PIN_MODULE

#include "switch_handler.h"
#include "RGB_handler.h"
#include "blinker_handler.h"
#include "feedback_handler.h"

/*
  Game module.
  Player finds a combination of left and right switch in which all four blinkers are lit, and based on
  the positions inserts a four-digit PIN code.
*/
class PINModule {

  public:

    // Creator and destructor
    PINModule(bool r = false);
    ~PINModule();

    // Main function
    int run(SwitchStates* switchState, RGBHandler* rgbHandler, BlinkerHandler* blinkerHandler);

    // Returns if this module has been succesfully completed or not
    bool isCompleted() {return completed;}

  
  private:

    // Member methods to help set the leds correctly
    void setBlinkers(BlinkerHandler*, SwitchStates*);
    void setRGB(RGBHandler*);

    // Member method to see if the current answer has been inserted correctly
    bool checkAnswer(SwitchStates*);

    // Randomizes the switches-blinkers-relationship if using randomized mode. (Does nothing if not using randomized mode.)
    void randomizeBlinkers();

    // Defaults
    int maxSuccessCount = 1;          // Changing this only applies to randomized mode

    // Internal variables
    bool completed                      = false;           // Tells if this module has been succcesfully completed or not
    int successCount                    = 0;               // Current number of passed rounds
    bool buttonsPreviouslyPressed[4]    = {false, false, false, false,}; // Button statuses of the previous iteration
    char currentBlinkers                = 0b0000;          // Current status of the blinkers
    int currentlyPressed[4]             = {0};             // Order in which the buttons were pressed
    bool shouldReset                    = false;           // true -> does not accept new presses until all buttons are released
    bool randomize;                                        // Whether to use randomized mode or not (set in initializer)

    // Maps the switch states to the correct pin codes. Every 4-integer sequence describes one such code.
    // Do not change! Otherwise the correct PIN codes from manual do not work.
    const int switches2pin[36] {
        1,3,2,4,    // down, down
        3,1,2,4,    // down, middle
        2,4,1,3,    // down, up
        4,1,3,2,    // middle, down
        2,3,4,1,    // middle, middle
        3,4,2,1,    // middle, up
        4,3,2,1,    // up, down
        4,2,3,1,    // up, middle
        2,1,4,3,    // up, up
    };

    // Maps the switcch positions to blinker statuses: first three values are for first switch (down-middle-up),
    // and last three for the second switch (down-middle-up). The final blinkers are set with first + second.
    // The values here are also the default values, but they arae changed during the runtime, if using randomized mode.
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
