#ifndef RGB_HANDLER
#define RGB_HANDLER

/*
  Enumeration of the possible RGB colors
*/
enum Color{
  red,
  green,
  blue,
  yellow,
  purple,
  cyan,
  white,
};


/*
  Class to handle the RGB LED.
*/
class RGBHandler {

  public:

    // Creator and destructor
    RGBHandler(int rp, int gp, int bp);
    ~RGBHandler();

    // Set the color of the LED as given in the parameter
    void set(Color c);

    // Set the individual values of LEDs directly as given in the arguments
    void set(int redVal, int greenVal, int blueVal);

    // Switch the RGB off
    void off();

  
  private:
    // LED pins
    int redPin;
    int greenPin;
    int bluePin;

    // LED color schemes (red-green--blue)
    int colors[21] = {10,  0,    0,      // red
                      0,    10,  0,      // green
                      0,    0,    10,    // blue
                      20,  5,  0,      // yellow
                      10,  0,    20,    // purple
                      0,    15,  10,    // cyan
                      20,  20,  20     // white
                      };

};

#endif