#include "pin_module.h"
#include "switch_handler.h"
#include "rgb_handler.h"
#include "blinker_handler.h"
#include "feedback_handler.h"
#include "Arduino.h"

/*
    Parameters:
        bool r      Whether to use randomized mode (true) or not (false)
*/
PINModule::PINModule(bool r = false) {
    // Check whether using randomized mode or not
    if (!r) { maxSuccessCount = 1; randomize = false; }
    else { randomize = true; }
    // Set the blinker status
    randomizeBlinkers();
}

PINModule::~PINModule() {
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
int PINModule::run(SwitchStates* switchState, RGBHandler* rgbHandler, BlinkerHandler* blinkerHandler) {
    if (completed) return 0;
    int ret = 0;

    // Array of currently pressed buttons
    bool buttonsPressed[4] = { switchState->btn1, switchState->btn2, switchState->btn3, switchState->btn4 };
    int differingButton = 0; int nofPressedButtons = 0; int nofPreviouslyPressedButtons = 0;

    // Loops trough the button statuses of current and last iterations to find out 
    // a) how many buttons are currently pressed,
    // b) how many buttons were previously pressed, and
    // c) what was the newly pressed button if there is one
    for (int idx = 0; idx < 4; idx++) {
        // Count the number of currently pressed buttons
        if (buttonsPressed[idx]) {nofPressedButtons++;}
        // Count the number of previously pressed buttons
        if (buttonsPreviouslyPressed[idx]) {nofPreviouslyPressedButtons++;}
        // Save the button number if it is pressed now but wasn't before
        if (buttonsPressed[idx] && !buttonsPreviouslyPressed[idx]) {differingButton = idx+1;}
        // Save current state to be used on next iterations
        buttonsPreviouslyPressed[idx] = buttonsPressed[idx];
    }

    // Multiple new buttons -> panic and reset
    if (nofPressedButtons > nofPreviouslyPressedButtons + 1) {shouldReset = true;}

    // If a button is pressed now but wasn't on the previous iteration
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
                randomizeBlinkers();
            }
        }     
    }

    // Reset the 'reset' flag if no buttons are currently pressed
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
    rgb->off();     // RGB not needed (in the current version)
}


bool PINModule::checkAnswer(SwitchStates* switches) {
    // Fail if all blinkers are not lit
    if (currentBlinkers != 0b1111) {return false;}

    int sw1 = switches->swtch1;
    int sw2 = switches->swtch2;
    int ansIdx = 3*sw1 + sw2;

    // Fail if the inserted PIN code is not correct (check digit by digit)
    for (int i = 0; i < 4; i++) {
        if ( currentlyPressed[i] != switches2pin[4*ansIdx + i] ) {
            return false;
        }
    }

    // Otherwise, return true
    return true;
}


/*
    Randomizes the switches-blinkers relationship if using randomized mode. Guarantees that there exists
    exactly one combination of switch positions in where all blinkers are lit.
    Does nothing if not using randomized mode.
*/
void PINModule::randomizeBlinkers() {
    // Return if not using randomized mode (use the fixed values instead)
    if (!randomize) {return;}
    
    // All possible pairs of two blinkers (as bit masks)
    int blinkerPairs[6] = {0b0011, 0b0101, 0b0110, 0b1001, 0b1010, 0b1100};

    // Individually lit blinker bit masks
    int individualBlinkers[4] = {0b0001, 0b0010, 0b0100, 0b1000};

    // Select a pair for the first switch as random
    int idx = random(6);
    int firstPair = blinkerPairs[idx];

    // Select the pair for the second switch as the complement of the first switch
    int secondPair = ~firstPair & 0b1111;

    // Shuffle individual blinker array
    for (int firstIdx = 0; firstIdx < 4; firstIdx++) {
        int secondIdx = random(4);
        int tmp = individualBlinkers[firstIdx];
        individualBlinkers[firstIdx] = individualBlinkers[secondIdx];
        individualBlinkers[secondIdx] = tmp;
    }

    // Set the values to array switches2blinkers: one pair and two individual blinkers for each switch
    switches2blinkers[0] = firstPair;
    switches2blinkers[1] = individualBlinkers[0];
    switches2blinkers[2] = individualBlinkers[1];
    switches2blinkers[3] = secondPair;
    switches2blinkers[4] = individualBlinkers[2];
    switches2blinkers[5] = individualBlinkers[3];

    // Shuffle first half of switches2blinkers
    for (int firstIdx = 0; firstIdx < 3; firstIdx++) {
        int secondIdx = random(3);
        int tmp = switches2blinkers[firstIdx];
        switches2blinkers[firstIdx] = switches2blinkers[secondIdx];
        switches2blinkers[secondIdx] = tmp;
    }

    // Shuffle second half of switches2blinkers
    for (int firstIdx = 3; firstIdx < 6; firstIdx++) {
        int secondIdx = random(3,6);
        int tmp = switches2blinkers[firstIdx];
        switches2blinkers[firstIdx] = switches2blinkers[secondIdx];
        switches2blinkers[secondIdx] = tmp;
    }

    // Final result:
    // - Each switch has in their three positions the following: one pair of two blinkers
    //   and two individual blinkers
    // - This set is randomly assigned to the three switch positions
    // - The 'pairs' of the two switches are complementary: if one switch has blinkers 1 and 2,
    //   the other switch has blinkers 3 and 4
    // Thus, when both switches are set to the position in which the pair is assigned, all blinkers
    // are lit. In all other positions at least one blinker is off.
}
