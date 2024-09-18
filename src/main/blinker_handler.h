#ifndef BLINKER_HANDLER
#define BLINKER_HANDLER

#include "rgb_handler.h"

/*
  Class to handle the blinker leds.
*/

class BlinkerHandler {

  public:

    // Creator and destructor
    BlinkerHandler(int rp, int gp, int bp, int yp);
    ~BlinkerHandler();

    // Set the module led as given in the parameter. Either the state of each led
    // as a boolean; or the bit-wise sum of the leds that needs to be set on; or
    // the idx or color of the led to be turned on (others will be set off).
    void set(bool redVal, bool greenVal, bool blueVal, bool yellowVal);
    void set(char ledSum);
    void set(int ledIdx);
    void set(Color c);

    // Turn all blinker leds off.
    void off();


  private:

    // Arduino pins for the LEDs
    int redPin;
    int greenPin;
    int bluePin;
    int yellowPin;

};

#endif
