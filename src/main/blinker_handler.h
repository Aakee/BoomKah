// Class to handle the blinker leds

#ifndef BLINKER_HANDLER
#define BLINKER_HANDLER

class BlinkerHandler {

  public:

    // Creator and destructor
    BlinkerHandler(int rp, int gp, int bp);
    ~BlinkerHandler();

    // Set the module led as given in the parameter
    void set(bool redVal, bool greenVal, bool blueVal);
    void off();


  private:
    int redPin;
    int greenPin;
    int bluePin;
    //int yellowPin;

};

#endif