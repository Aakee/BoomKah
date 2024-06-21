#include "simon_module.h"
#include "switch_handler.h"
#include "RGB_handler.h"
#include "blinker_handler.h"
#include "feedback_handler.h"
#include "Arduino.h"

/*
    Parameters:
        bool r      Whether to use randomized mode (true) or not (false)
*/
SimonModule::SimonModule(bool r = false) {
    // Check whether using randomized mode or not
    if (!r) { maxSuccessCount = 4; randomize = false; }
    else { 
        randomize = true;
        if (maxSuccessCount > MAX_NOF_ROUDS) { maxSuccessCount = MAX_NOF_ROUDS; }
    }
    // Set the blinker sequence and rgb color
    randomizeSequence();
}


SimonModule::~SimonModule() {
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
int SimonModule::run(SwitchStates* switchState, RGBHandler* rgbHandler, BlinkerHandler* blinkerHandler) {
    if (completed) return 0;
    int ret = 0;

    // Whether a button is pressed
    bool buttonPressed = switchState->btn1 || switchState->btn2 || switchState->btn3 || switchState->btn4 ;

    if (buttonPressed && !buttonPreviouslyPressed) {

        // Find which button is pressed
        int btnNumber = 0;
        if (switchState->btn1) {btnNumber = 0;}
        if (switchState->btn2) {btnNumber = 1;}
        if (switchState->btn3) {btnNumber = 2;}
        if (switchState->btn4) {btnNumber = 3;}

        // Player's answer, and correct answer
        Color answer        = button2blinker[4*currentRgbIndex + btnNumber];
        Color correctAnswer = blinkerOrder[currentPressIdx];

        // Correct answer
        if (answer == correctAnswer) {
            currentPressIdx++;
        }
        
        // Wrong answer
        else {
            successCount = 0;
            currentPressIdx = 0;
            ret = -1;
            randomizeSequence();
        }
    }

    // Save the status whether button was pressed
    buttonPreviouslyPressed = buttonPressed;

    // Check if advances to next round
    if (currentPressIdx > successCount) {
        successCount++;
        currentPressIdx = 0;
        currentBlinkIndex = -1;
        ret = 1;
    }

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
void SimonModule::setBlinkers(BlinkerHandler* blnk) {
    unsigned long currentTime = millis();
    bool rest = false;

    // Set the blinkers to rest
    if ( currentTime > lastSwitch + blinkDuration ) { rest =  true; }

    // Advance to next blinker
    if ( currentTime > lastSwitch + blinkDuration + restDuration ) {
        currentBlinkIndex++;
        lastSwitch =  millis();
    }

    // Loop back to the beginning
    if ( currentBlinkIndex > successCount ) { currentBlinkIndex = -2; }

    // Put the blinkers off if a) rest period or b) idx is < 0
    if (rest || currentBlinkIndex < 0) { blnk->off(); }

    // Switch the correct blinker on
    else {
        Color c = blinkerOrder[currentBlinkIndex];
        blnk->set(c);
    }
}


/*
    Sets the RGB as needed for this module
*/
void SimonModule::setRGB(RGBHandler* rgb) {
    Color c = rgbColors[currentRgbIndex];
    rgb->set(c);
}


/*
    Randomizes the blinker sequence and rgb color if using randomized mode.
    Does nothing if not using randomized mode.
*/
void SimonModule::randomizeSequence() {
    // Do nothing if not using randomized mode
    if (!randomize) {return;}

    // Up until the maximum number of lights (maxSucessCount), randomize the individual blinker colors
    Color colors[4] = {red, blue, green, yellow};
    for ( int idx = 0; idx < maxSuccessCount; idx++ ) {
        blinkerOrder[idx] = colors[random(4)];
    }

    // Randomize RGB color
    currentRgbIndex = random(3);

}
