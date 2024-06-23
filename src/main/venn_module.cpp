#include "venn_module.h"
#include "switch_handler.h"
#include "RGB_handler.h"
#include "blinker_handler.h"
#include "feedback_handler.h"
#include "Arduino.h"

/*
    Parameters:
        bool r      Whether to use randomized mode (true) or not (false)
*/
VennModule::VennModule(bool r = false) {
    // Check whether using randomized mode or not
    if (!r) { maxSuccessCount = 3; randomize = false; }
    else { randomize = true; }
    // Set the blinker sequence and rgb color
    randomizeState();
}


VennModule::~VennModule() {
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
int VennModule::run(SwitchStates* switchState, RGBHandler* rgbHandler, BlinkerHandler* blinkerHandler) {
    if (completed) return 0;
    int ret = 0;

    // Whether a button is pressed
    bool buttonPressed = switchState->btn1 || switchState->btn2 || switchState->btn3 || switchState->btn4 ;

    if (buttonPressed && !buttonPreviouslyPressed) {

        // Correct answer
        if (checkAnswer(switchState)) {
            successCount++;
            ret = 1;
        }
        
        // Wrong answer
        else {
            successCount = 0;
            ret = -1;
        }

        // In both cases, set next  state
        randomizeState();
    }

    // Save the status whether button was pressed
    buttonPreviouslyPressed = buttonPressed;

    // Check if module completed
    if (successCount >= maxSuccessCount) {
        completed = true;
        ret = 2;
    }

    // Set RGB and blinkers
    setRGB(rgbHandler);
    setBlinkers(blinkerHandler);

    return ret;
}


/*
    Sets the blinker LEDs as needed for this module
*/
void VennModule::setBlinkers(BlinkerHandler* blnk) {
    blnk->set(currentBlinkers);
}


/*
    Sets the RGB as needed for this module
*/
void VennModule::setRGB(RGBHandler* rgb) {
    rgb->set(currentRgbColor);
}


bool VennModule::checkAnswer(SwitchStates* switches) {
    // Determine what button was pressed
    int btnNumber = 0;
    if (switches->btn1) {btnNumber = 1;}
    if (switches->btn2) {btnNumber = 2;}
    if (switches->btn3) {btnNumber = 3;}
    if (switches->btn4) {btnNumber = 4;}

    // Determine switch states
    int sw1 = switches->swtch1;
    int sw2 = switches->swtch2;

    // Check which of the three conditions currently hold
    int correctCondition = 0b0000;

    // Condition 1: at least one blue light
    if ( currentRgbColor == blue || (currentBlinkers & 0b0100) == 0b0100 ) {
        correctCondition = correctCondition | 0b0001;
    }

    // Condition 2: at least three blinkers
    if (currentBlinkers == 0b0111 || currentBlinkers == 0b1011 || currentBlinkers == 0b1101 || currentBlinkers == 0b1110 || currentBlinkers== 0b1111 ) {
        correctCondition = correctCondition | 0b0010;
    }

    // Condition 3: RGB on but not red
    if (currentRgbColor != red && currentRgbColor != none) {
        correctCondition = correctCondition | 0b0100;
    }

    // Check if the switches are in correct position
    if ( 3*sw1 + sw2 != switches2condition[2*correctCondition] ) {
        return false;
    }

    // Check if the button is correct
    if ( btnNumber != switches2condition[2*correctCondition+1] ) {
        return false;
    }

    // Otherwise, return true
    return true;

}


/*
    Randomizes the blinker combination and rgb color if using randomized mode, or sets the correct
    deterministic state if not using randomized mode.
*/
void VennModule::randomizeState() {
    // Randomized mode
    if (randomize) {
        int chosenCombination = random(8);
        //Serial.println(chosenCombination);

        // A: None of the conditions fulfilled
        
        if (chosenCombination == 0) {
            // Possible blinkers: Max two blinkers, no blue
            char possibleBlinkersA[7] = {0b0000, 0b0001, 0b0010, 0b1000, 0b0011, 0b1001, 0b1010};
            currentBlinkers = possibleBlinkersA[random(7)];
            // Possible RGBs: Off or red
            Color possibleRgbsA[2] = {red, none};
            currentRgbColor = possibleRgbsA[random(2)];
        }

        // B: Condition 1 fulfilled, 2 and 3 not --> at least one blue, at most two blinkers, rgb off or red
        if (chosenCombination == 1) {
            // First, determine blinkers (max 2 on), must include blue (as rgb cannot be blue)
            char possibleBlinkersB[4] = {0b0100, 0b0101, 0b0110, 0b1100};
            currentBlinkers = possibleBlinkersB[random(4)];
            // Possible RGBs: Off or red
            Color possibleRgbsB[2] = {red, none};
            currentRgbColor = possibleRgbsB[random(2)];
        }

        // C: Conditions 1 and 2, not 3 --> at least one blue, at least three blinkers, rgb off or red
        if (chosenCombination == 2) {
            // First, determine blinkers (min 3 on, blue must be on as indicator cannot be blue)
            char possibleBlinkersC[5] = {0b0111, 0b1101, 0b1110, 0b1111};
            currentBlinkers = possibleBlinkersC[random(5)];
            // Possible RGBs: Off or red
            Color possibleRgbsC[2] = {red, none};
            currentRgbColor = possibleRgbsC[random(2)];
        }

        // D: All conditions: at least one blue, at least three blinkers, rgb not red or off
        if (chosenCombination == 3) {
            // First, determine blinkers (min 3 on)
            char possibleBlinkersD[5] = {0b0111, 0b1011, 0b1101, 0b1110, 0b1111};
            currentBlinkers = possibleBlinkersD[random(5)];
            // RGB must be blue if blue blinker is not on; otherwise, it can be whatever but red or off
            if ( (currentBlinkers & 0b0100) != 0b0100 ) {
                currentRgbColor = blue;
            } else {
                Color possibleRgbsD[2] = {blue, green};
                currentRgbColor = possibleRgbsD[random(2)];
            }
        }

        // E: At least one blue, at most two blinkers, rgb not off or red
        if (chosenCombination == 4) {
            // Determine blinkers (max 3 on)
            char possibleBlinkersE[11] = {0b0000, 0b0001, 0b0010, 0b0100, 0b1000, 0b0011, 0b0101, 0b0110, 0b1001, 0b1010, 0b1100};
            currentBlinkers = possibleBlinkersE[random(11)];
            // RGB must be blue if blue blinker is not on; otherwise, it can be whatever but red or off
            if ( (currentBlinkers & 0b0100) != 0b0100 ) {
                currentRgbColor = blue;
            } else {
                Color possibleRgbsE[2] = {blue, green};
                currentRgbColor = possibleRgbsE[random(2)];
            }
        }

        // F: At least three blinkers, no blue, rgb off or red
        if (chosenCombination == 5) {
            // Only one possibility for blinkers
            currentBlinkers = 0b1011;
            // Possible RGBs: Off or red
            Color possibleRgbsF[2] = {red, none};
            currentRgbColor = possibleRgbsF[random(2)];
        }

        // G: No blue, at least three blinkers, rgb not off or red
        if (chosenCombination == 6) {
            // Only one possibility for blinkers
            currentBlinkers = 0b1011;
            // Possible RGBs: must be green
            currentRgbColor = green;
        }

        // H: No blues, at most two blinkers, rgb not off or red
        if (chosenCombination == 7) {
            // Possible blinkers: Max two blinkers, no blue
            char possibleBlinkersH[7] = {0b0000, 0b0001, 0b0010, 0b1000, 0b0011, 0b1001, 0b1010};
            currentBlinkers = possibleBlinkersH[random(7)];
            // Possible RGBs: must be green
            currentRgbColor = green;
        }
    }

    // Deterministic mode
    else {
        currentBlinkers = defaultBlinkerStates[successCount];
        currentRgbColor = defaultRgbColors[successCount];
    }
}
