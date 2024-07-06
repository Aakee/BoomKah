#ifndef VENN_MODULE
#define VENN_MODULE

#include "switch_handler.h"
#include "rgb_handler.h"
#include "blinker_handler.h"
#include "feedback_handler.h"

/*
  Game module.
  Blinkers and RGB show some combination (state). Player has to determine which of three pre-determined
  conditions are currently satisfied, and based on that set switches to correct position and press correct
  button.
*/


class VennModule {

  public:

    // Creator and destructor
    VennModule(bool r = false);
    ~VennModule();

    // Main function
    int run(SwitchStates* switchState, RGBHandler* rgbHandler, BlinkerHandler* blinkerHandler);

    // Returns if this module has been succesfully completed or not
    bool isCompleted() {return completed;}

  
  private:

    // Member methods to help set the leds correctly
    void setBlinkers(BlinkerHandler*);
    void setRGB(RGBHandler*);

    // Randomizes the switches-blinkers-relationship if using randomized mode. (Does nothing if not using randomized mode.)
    void randomizeState();

    bool checkAnswer(SwitchStates*);

    // Defaults
    int maxSuccessCount = 3;          // Changing this only applies to randomized mode

    // Internal variables
    bool completed                      = false;           // Tells if this module has been succcesfully completed or not
    int successCount                    = 0;               // Current number of passed rounds
    bool buttonPreviouslyPressed        = true;
    Color rgbColors[8]                  = {red, blue, green, purple, yellow, cyan, white, none}; // Possible RGB values
    Color currentRgbColor               = none;
    char currentBlinkers                = 0b0000;
    bool randomize;                                        // Whether to use randomized mode or not (set in initializer)

    // Default values for deterministic mode, for the three rounds
    char defaultBlinkerStates[3]        = {0b1100,  0b0011, 0b1011 }; // B A G
    Color defaultRgbColors[3]           = {none,    red,    green }; 

    // Maps the switches and buttons to the conditions.
    // 0b0ZYX, where X is cond 1, Y is cond 2, and Z is cond 3
    int switches2condition[8*4] {
        3*down  +   up,     3,      // 0b0000       A
        3*middle+   down,   2,      // 0b0001       B
        3*down  +   middle, 4,      // 0b0010       F
        3*middle+   up,     3,      // 0b0011       C
        3*up    +   down,   1,      // 0b0100       H
        3*up    +   up,     4,      // 0b0101       E
        3*down  +   down,   2,      // 0b0110       G
        3*up    +   middle, 1,      // 0b0111       D    
    };


};

#endif
