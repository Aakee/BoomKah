#include "directions_module.h"
#include "switch_handler.h"
#include "RGB_handler.h"
#include "blinker_handler.h"
#include "feedback_handler.h"
#include "Arduino.h"

DirectionsModule::DirectionsModule() {
}

DirectionsModule::~DirectionsModule() {
}


/*
    Main method. Runs through and checks the player actions.
    Parameters:
        SwitchStates* switchStates          Struct of button states
        RGBHandler* rgbHandler              RGB manager
        BlinkerHandler* blinkerHandler      Blinker LED manager
    Returns
        int: 1 if user did something right, -1 if wrong, and 0 otherwise
*/
int DirectionsModule::run(SwitchStates* switchState, RGBHandler* rgbHandler, BlinkerHandler* blinkerHandler) {
    bool btn = switchState->btn4;       // Player presses this button when they lock an answer
    int ret = 0;

    // Check if the answer was right
    if (btn && !buttonPressed) {

        // Player's answer
        SwitchPosition rightSwitch = switchState->swtch1;

        // Correct answer
        if (rightSwitch == correctAnswers[successCount]) {
            successCount += 1;
            ret = 1;
        }

        // Wrong answer
        else {
            successCount = 0;
            ret = -1;
        }
    }

    if (successCount >= maxSuccessCount) {completed=true;}

    // Update button buffer and led states
    buttonPressed = btn;
    setBlinkers(blinkerHandler, switchState);
    setRGB(rgbHandler);

    return ret;
}


/*
    Sets the blinker LEDs as needed for this module
*/
void DirectionsModule::setBlinkers(BlinkerHandler* blnk, SwitchStates* switches) {
    // Switch off if module is completed
    if (successCount >= maxSuccessCount) { blnk->off(); return; }

    // Some semi-arbitrary algorithm to define blinker id
    int offset = 2*successCount;
    SwitchPosition leftSwitch = switches->swtch2;
    currentBlinker = -leftSwitch + offset + 1;
    while (currentBlinker < 0) {currentBlinker += 3;}
    while (currentBlinker > 2) {currentBlinker -= 3;}

    blnk->set(currentBlinker);
}


/*
    Sets the RGB as needed for this module
*/
void DirectionsModule::setRGB(RGBHandler* rgb) {
    if (successCount >= maxSuccessCount) { rgb->off(); return; }
    Color c = rgbColors[successCount];
    rgb->set(c);
}