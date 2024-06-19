#include "pin_module.h"
#include "switch_handler.h"
#include "RGB_handler.h"
#include "blinker_handler.h"
#include "feedback_handler.h"
#include "Arduino.h"

PINModule::PINModule() {
}

PINModule::~PINModule() {
}


/*
    Main method. Runs through and checks the player actions.
    Parameters:
        SwitchStates* switchStates          Struct of button states
        RGBHandler* rgbHandler              RGB manager
        BlinkerHandler* blinkerHandler      Blinker LED manager
    Returns
        int: 1 if user did something right, -1 if wrong, 2 if module was deactivated, and 0 otherwise
*/
int PINModule::run(SwitchStates* switchState, RGBHandler* rgbHandler, BlinkerHandler* blinkerHandler) {
    if (completed) return 0;
    int ret = 0;

    // Array of currently pressed buttons
    bool buttonsPressed[4] = { switchState->btn1, switchState->btn2, switchState->btn3, switchState->btn4 };
    int differingButton = 0; int nofPressedButtons = 0; int nofPreviouslyPressedButtons = 0;

    // Find out a) how many buttons are currently pressed, and b) if there is some new button pressed compaared to last iteration
    for (int idx = 0; idx < 4; idx++) {
        if (buttonsPressed[idx]) {
            nofPressedButtons++;
        }
        if (buttonsPreviouslyPressed[idx]) {
            nofPreviouslyPressedButtons++;
        }
        if (buttonsPressed[idx] != buttonsPreviouslyPressed[idx]) {
            differingButton = idx+1;
        }
        buttonsPreviouslyPressed[idx] = buttonsPressed[idx];
    }

    if (nofPressedButtons > nofPreviouslyPressedButtons + 1) {shouldReset = true;}

    // If button is pressed now but wasn't on the previous iteration
    if (!shouldReset && nofPressedButtons == nofPreviouslyPressedButtons + 1) {

        // Save the new button
        currentlyPressed[nofPreviouslyPressedButtons] = differingButton;

        // If all four buttons are pressed: check the answer
        if (nofPressedButtons == 4) {
            if (checkAnswer(switchState)) {
                successCount++;
                ret = 1;
            } else {
                successCount = 0;
                ret = -1;
                shouldReset = true;
            }
        }     
    }

    // Reset the 'reset' flag :D
    if (nofPressedButtons == 0) {shouldReset = false;}

    // Check if the module has been deactivated
    if (successCount >= maxSuccessCount) {ret=2, completed = true;}

    // Set the lights correctly
    setBlinkers(blinkerHandler, switchState);
    setRGB(rgbHandler);

    return ret;
}


/*
    Sets the blinker LEDs as needed for this module
*/
void PINModule::setBlinkers(BlinkerHandler* blnk, SwitchStates* switches) {
    if (completed) {blnk->off(); return;}
    int sw1 = switches->swtch1;
    int sw2 = switches->swtch2;
    currentBlinkers = switches2blinkers[sw1] + switches2blinkers[3+sw2];
    blnk->set(currentBlinkers);
}


/*
    Sets the RGB as needed for this module
*/
void PINModule::setRGB(RGBHandler* rgb) {
    rgb->off();
}


bool PINModule::checkAnswer(SwitchStates* switches) {
    // Fail if all blinkers are not lit
    if (currentBlinkers != 0b1111) {return false;}

    int sw1 = switches->swtch1;
    int sw2 = switches->swtch2;
    int ansIdx = 3*sw1 + sw2;

    // Fail if the inserted pin is not correct
    for (int i = 0; i < 4; i++) {
        if ( currentlyPressed[i] != switches2pin[4*ansIdx + i] ) {
            Serial.println(10*currentlyPressed[i] + switches2pin[4*ansIdx + i] );
            return false;
        }
    }

    // Otherwise, return true
    return true;
}