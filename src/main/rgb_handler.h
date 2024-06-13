// Class to handle the RGB led

#ifndef RGB_HANDLER
#define RGB_HANDLER

class RGBHandler {

  public:

    // Creator and destructor
    RGBHandler(int rp, int gp, int bp);
    ~RGBHandler();

    // Set the module led as given in the parameter
    void set(int redVal, int greenVal, int blueVal);
    void off();

  
  private:
    int redPin;
    int greenPin;
    int bluePin;

};

#endif