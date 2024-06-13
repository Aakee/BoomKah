#ifndef BLINKER_HANDLER
#define BLINKER_HANDLER


/*
  Class to handle the blinker leds.
*/

class BlinkerHandler {

  public:

    // Creator and destructor
    BlinkerHandler(int wp, int bp, int yp);
    ~BlinkerHandler();

    // Set the module led as given in the parameter. Either the state of each led
    // as a boolean; or the bit-wise sum of the leds that needs to be set on; or
    // the idx of the led to be turned on (others will be set off).
    void set(bool whiteVal, bool blueVal, bool yellowVal);
    void set(char ledSum);
    void set(int ledIdx);

    // Turn all blinker leds off.
    void off();


  private:

    // Arduino pins for the LEDs
    int whitePin;
    int bluePin;
    int yellowPin;

};

#endif
