#ifndef SIMON_MODULE
#define SIMON_MODULE

#include "switch_handler.h"
#include "rgb_handler.h"
#include "blinker_handler.h"
#include "feedback_handler.h"

/*
  Game module.
  Player plays 'Simon Says' with the module: bomb blinks blinkers in some order, and player presses
  corresponding buttons in the same order.
*/

// Absolute maximum number of rounds for this module
const int MAX_NOF_ROUDS = 16;

class SimonModule {

  public:

    // Creator and destructor
    SimonModule(bool r = false);
    ~SimonModule();

    // Main function
    int run(SwitchStates* switchState, RGBHandler* rgbHandler, BlinkerHandler* blinkerHandler);

    // Returns if this module has been succesfully completed or not
    bool isCompleted() {return completed;}

  
  private:

    // Member methods to help set the leds correctly
    void setBlinkers(BlinkerHandler*);
    void setRGB(RGBHandler*);

    // Randomizes the blink sequence and rgb if using randomized mode. (Does nothing if not using randomized mode.)
    void randomizeSequence();

    // Defaults
    int maxSuccessCount = 4;          // Changing this only applies to randomized mode
    Color blinkerOrder[MAX_NOF_ROUDS]     = {blue, green, blue, yellow}; // Order in which the blinkers blink
    long blinkDuration                  = 700;
    long restDuration                   = 300;

    // Internal variables
    bool completed                      = false;           // Tells if this module has been succcesfully completed or not
    int successCount                    = 0;               // Current number of passed rounds
    int currentPressIdx                 = 0;
    bool buttonPreviouslyPressed        = true;
    bool shouldReset                    = false;           // true -> does not accept new presses until all buttons are released
    Color rgbColors[3]                  = {red, blue, green}; // Possible RGB values
    int currentRgbIndex                 = 1;
    int currentBlinkIndex               = -1;
    unsigned long lastSwitch            = 0;
    bool randomize;                                        // Whether to use randomized mode or not (set in initializer)

    // Maps the four buttons to corresponding four blinkers, for eacch possible RGB color.
    // Do not change! Otherwise the correct button sequences from manual won't work.
    const Color button2blinker[12] {
        green,  red,    blue,   yellow,     // Red RGB
        red,    yellow, green,  blue,       // Blue RGB
        blue,   green,  yellow, red,        // Green RGB
    };

};

#endif
