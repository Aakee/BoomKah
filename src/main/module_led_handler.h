// Class to handle the module leds

#ifndef MODULE_LED_HANDLER
#define MODULE_LED_HANDLER

class ModuleLedHandler {

  public:

    // Creator and destructor
    ModuleLedHandler(int p1, int p2, int p3);
    ~ModuleLedHandler();

    // Set the module led as given in the parameter
    void set(int moduleNumber);
    void off();


  private:
    int pin1;
    int pin2;
    int pin3;

};

#endif
