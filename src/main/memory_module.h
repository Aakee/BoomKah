#ifndef MEMORY_MODULE
#define MEMORY_MODULE

#include "switch_handler.h"
#include "RGB_handler.h"
#include "blinker_handler.h"
#include "feedback_handler.h"

/*
  Game module.
  Player sees blinking LEDs, checks which button corresponds to them, and presses the buttons in correct order.
*/
class MemoryModule {

  public:

    // Creator and destructor
    MemoryModule();
    ~MemoryModule();

    // Main function
    int run(SwitchStates* switchState, RGBHandler* rgbHandler, BlinkerHandler* blinkerHandler);

    // Returns if this module has been succesfully completed or not
    bool isCompleted() {return completed;}

  
  private:

    // Configuration
    unsigned long blinkTime = 800;

    // Member methods to help set the LEDs correctly
    void setBlinkers(BlinkerHandler*);

    // Defaults
    int maxSuccessCount = 3;              // Pelase don't change this, the code doesn't currently allow more rounds
    int blinkOrder[5] = {2,1,0};          // Color of RGB in the three rounds
    int correctAnswers[6] = {2,           // Correct LED indexes to release the button 
                             0, 2,
                             1, 0, 2};

    // Internal variables
    bool completed            = false;    // Tells if this module has been succcesfully completed or not
    int successCount          = 0;        // Current number of passed rounds
    bool buttonBuffer         = false;    // Was the button pressed on the previous iteration
    int buttonPressNumber     = 0;        // How many correct answers the player has inputted on this round
    unsigned long lastSwitch  = 0;        // Timestamp when the blinker LED was last changed
    int blinkIdx              = -2;       // Index of the current blinker LED (or <0 if off)

};

#endif
