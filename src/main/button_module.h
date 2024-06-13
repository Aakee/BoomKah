#include "switch_handler.h"
#include "RGB_handler.h"
#include "blinker_handler.h"
#include "Arduino.h"

class ButtonModule {

  public:

    // Creator and destructor
    ButtonModule();
    ~ButtonModule();

    // Main function: runs through
    bool run(SwitchState* switchState, RGBHandler* rgbHandler, BlinkerHandler* blinkerHandler);

    bool isCompleted() {return completed;}

  
  private:

    // If the module has been successfully completed
    bool completed = false;

    // How many successes this module currently holds, and how many are needed to complete the module
    int successCount = 0;
    const int maxSuccessCount = 3;

    bool buttonPressed = false;
    unsigned long lastSwitch = 0;


    int firstTask_currentLight = 0;
    int firstTask_correctAnswers[3] = {2,1,1};

};