#ifndef TEST_MODULE
#define TEST_MODULE

#include "switch_handler.h"
#include "rgb_handler.h"
#include "blinker_handler.h"
#include "feedback_handler.h"

/*
  Test game module.
  Used to test operation of the hardware.
*/


class TestModule {

  public:

    // Creator and destructor
    TestModule(bool r = false);
    ~TestModule();

    // Main function
    int run(SwitchStates* switchState, RGBHandler* rgbHandler, BlinkerHandler* blinkerHandler);

    // Returns if this module has been succesfully completed or not
    bool isCompleted() {return completed;}

  
  private:
    // Defaults
    int maxSuccessCount = 3;

    // Internal variables
    bool completed                      = false;           // Tells if this module has been succcesfully completed or not
    int successCount                    = 0;               // Current number of passed rounds

};

#endif
