#ifndef BUTTON_MODULE
#define BUTTON_MODULE

#include "switch_handler.h"
#include "RGB_handler.h"
#include "blinker_handler.h"
#include "feedback_handler.h"
#include "button_module.h"


/*
  Game module.
  Player holds down button 4, reads the ccolor of RGB led, and releases the button when a correct blinker LED is on.
*/
class ButtonModule {

  public:

    // Creator and destructor
    ButtonModule();
    ~ButtonModule();

    // Main function
    int run(SwitchStates* switchState, RGBHandler* rgbHandler, BlinkerHandler* blinkerHandler);

    // Returns if this module has been succesfully completed or not
    bool isCompleted() {return completed;}

  
  private:

    // Configuration
    unsigned long switchDuration = 1200;  // Duration a single LED stays on before changing

    // Member methods to help set the LEDs correctly
    void setBlinkers(BlinkerHandler* blnk);
    void setRGB(RGBHandler* rgb);

    // Defaults
    int maxSuccessCount   = 3;                 // Pelase don't change this, the code doesn't currently allow more rounds
    Color rgbColors[3]    = {purple,red,blue}; // Color of RGB in the three rounds
    int correctAnswers[3] = {2,1,1};           // Correct LED indexes to release the button 


    // Internal variables
    bool completed            = false;         // Tells if this module has been succcesfully completed or not
    int successCount          = 0;             // Current number of passed rounds
    bool buttonPressed        = false;         // Was the button pressed on the previous iteration
    unsigned long lastSwitch  = 0;             // Timestamp when the blinker LED was last changed
    int currentLight          = 0;             // Index of the current blinker LED

};

#endif
