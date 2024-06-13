#ifndef DIRECTIONS_MODULE
#define DIRECTIONS_MODULE

#include "switch_handler.h"
#include "RGB_handler.h"
#include "blinker_handler.h"
#include "feedback_handler.h"

/*
  Game module.
  Player reads RGB color, turns one switch according to that, turns another switch according to blinker color, and presses button. 
*/
class DirectionsModule {

  public:

    // Creator and destructor
    DirectionsModule();
    ~DirectionsModule();

    // Main function
    int run(SwitchStates* switchState, RGBHandler* rgbHandler, BlinkerHandler* blinkerHandler);

    // Returns if this module has been succesfully completed or not
    bool isCompleted() {return completed;}

  
  private:

    // Configuration


    // Member methods to help set the leds correctly
    void setBlinkers(BlinkerHandler*, SwitchStates*);
    void setRGB(RGBHandler* rgb);

    // Defaults
    int maxSuccessCount = 2;              // Pelase don't change this, the code doesn't currently allow more rounds
    Color rgbColors[2] = {yellow,blue};   // Color of RGB in the two rounds
    int correctAnswers[2] = {-1,0};       // Correct switch positions for the two rounds


    // Internal variables
    bool completed = false;               // Tells if this module has been succcesfully completed or not
    int successCount = 0;                 // Current number of passed rounds
    bool buttonPressed = false;           // Was the button pressed on the previous iteration; for buffering the button
    int currentBlinker = 0;               // Index of the current blinker LED

};

#endif
