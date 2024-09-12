#include "test_module.h"
#include "switch_handler.h"
#include "rgb_handler.h"
#include "blinker_handler.h"
#include "feedback_handler.h"
#include "Arduino.h"

/*
    Parameters:
        bool r      Whether to use randomized mode (true) or not (false)
*/
TestModule::TestModule(bool r = false) {
}


TestModule::~TestModule() {
}


/*
    Main method. Checks the player actions.
    Parameters:
        SwitchStates* switchStates          Struct of button states
        RGBHandler* rgbHandler              RGB manager
        BlinkerHandler* blinkerHandler      Blinker LED manager
    Returns
        int: 1 if user did something right, -1 if wrong, 2 if module was deactivated, and 0 otherwise
*/
int TestModule::run(SwitchStates* switchState, RGBHandler* rgbHandler, BlinkerHandler* blinkerHandler) {
    if (completed) return 0;
    int ret = 0;

    // Set blinkers according to switches
    char blinkers = 0b0000;
    if (switchState->swtch1 == up) {
        blinkers += 0b0001;
    }
    if (switchState->swtch1 == down) {
        blinkers += 0b0010;
    }
    if (switchState->swtch2 == up) {
        blinkers += 0b1000;
    }
    if (switchState->swtch2 == down) {
        blinkers += 0b0100;
    }
    blinkerHandler->set(blinkers);

    // Set indicator and return value according to buttons
    if (switchState->btn1) {
        rgbHandler->set(red);
        ret = 1;
        successCount++;
    }
    if (switchState->btn2) {
        rgbHandler->set(green);
    }
    if (switchState->btn3) {
        rgbHandler->set(blue);
    }
    if (switchState->btn4) {
        ret = -1;
        rgbHandler->set(none);
        successCount = 0;
    }

    // Module completed?
    if (successCount >= maxSuccessCount) {
        ret = 2;
    }

    return ret;
}
