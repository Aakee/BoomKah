#include "switches_module.h"
#include "switch_handler.h"
#include "RGB_handler.h"
#include "blinker_handler.h"
#include "feedback_handler.h"
#include "Arduino.h"

SwitchesModule::SwitchesModule() {
}

SwitchesModule::~SwitchesModule() {
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
int SwitchesModule::run(SwitchStates* switchState, RGBHandler* rgbHandler, BlinkerHandler* blinkerHandler) {
    int ret = 0;
    bool buttonPressed = switchState->btn1 || switchState->btn2 || switchState->btn3 || switchState->btn4 ;

    // If button is pressed now but wasn't on the previous iteration
    if (buttonPressed && !buttonPreviouslyPressed) {

        // Check the answer (switch and button states) and do actions based on if the answer was right or wrong
        if (checkAnswer(switchState)) {
            successCount++;
            ret = 1;
        } else {
            successCount = 0;
            ret = -1;
        }
    }

    // Save the button state (whether atleas one button was pressed)
    buttonPreviouslyPressed = buttonPressed;

    // Check if the module has been deactivated
    if (successCount >= maxSuccessCount) {ret=2, completed = true;}

    // Set the lights correctly
    setBlinkers(blinkerHandler);
    setRGB(rgbHandler, switchState);
    return ret;
}


/*
    Sets the blinker LEDs as needed for this module
*/
void SwitchesModule::setBlinkers(BlinkerHandler* blnk) {
    if (completed) {blnk->off(); return;}
    currentBlinkers = blinkerColors[successCount];
    blnk->set(currentBlinkers);
}


/*
    Sets the RGB as needed for this module
*/
void SwitchesModule::setRGB(RGBHandler* rgb, SwitchStates* switches) {
    if (completed) {rgb->off(); return;}

    int sw1 = switches->swtch1;
    int sw2 = switches->swtch2;

    // This line can be changed to alternate the relation of switch state and RGB color
    currentRGB = (sw1 + 3*sw2 + successCount) % 8;
    rgb->set(currentRGB);
}


/*
    Checks if the current combination of switches and pressed button is correct for current
    combination of blinkers and rgb
*/
bool SwitchesModule::checkAnswer(SwitchStates* switches) {
    // Check switches
    int sw1 = switches->swtch1;
    int sw2 = switches->swtch2;
    if (sw1 + 3*sw2 != blinkers2switches[currentBlinkers]) {return false;}

    // Check button
    int btn = 0;
    if (switches->btn1) {btn = 1;}
    if (switches->btn2) {btn = 2;}
    if (switches->btn3) {btn = 3;}
    if (switches->btn4) {btn = 4;}
    if (btn == 0) {return false;}
    if (btn != rgb2button[currentRGB]) {return false;}

    // Both checks were a success -> return true
    return true;
}
