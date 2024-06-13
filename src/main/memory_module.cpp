#include "memory_module.h"
#include "switch_handler.h"
#include "RGB_handler.h"
#include "blinker_handler.h"
#include "feedback_handler.h"
#include "Arduino.h"

MemoryModule::MemoryModule() {
}

MemoryModule::~MemoryModule() {
}


/*
    Retrieves the current "right answer index", that is, how manyth button from correctAnswers should
    be pushed next.
    Parameters:
        int successCount                Number of passed rounds
        int buttonPressNumber           Number of successes this round
    Returns:
        int, idx of the next answer
*/
int getNextAnswerIndex(int successCount, int buttonPressNumber) {
    int ans = 0;
    for (int i = 0; i <= successCount; i++) { ans += i; }
    return ans + buttonPressNumber;
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
int MemoryModule::run(SwitchStates* switchState, RGBHandler* rgbHandler, BlinkerHandler* blinkerHandler) {
    int btn = -1;
    int ret = 0;

    // Retrieve which button was pressed; if multiple, choose highest index
    if (switchState->btn1) {btn = 0;}
    if (switchState->btn2) {btn = 1;}
    if (switchState->btn3) {btn = 2;}

    // If button was played --> attempt was made
    if (!buttonBuffer && btn >= 0) {

        // Which button should have been pressed (correct answer)
        int correctAns = correctAnswers[getNextAnswerIndex(successCount, buttonPressNumber)];

        // Correct answer
        if (btn == correctAns) {
            buttonPressNumber += 1;
            if (buttonPressNumber > successCount) {
                ret = 1;
                successCount += 1;
                buttonPressNumber = 0;
            }
        }

        // Wrong answer
        else {
            successCount = 0;
            buttonPressNumber = 0;
            lastSwitch = 0;
            blinkIdx = -2;
            ret = -1;
        }
    }

    if (successCount >= maxSuccessCount) {completed=true;}

    buttonBuffer = btn >= 0;
    setBlinkers(blinkerHandler);

    return ret;

}

/*
    Sets the blinker LEDs as needed for this module
*/
void MemoryModule::setBlinkers(BlinkerHandler* blnk) {
    if (successCount >= maxSuccessCount) { blnk->off(); return; }

    // Switch blinker LED if blinkTime milliseconds has passed
    unsigned long currentTime = millis();
    if (currentTime - lastSwitch > blinkTime) {
        blinkIdx += 1;
        blnk->off();
        lastSwitch = millis();

        // if currently over the numer of succcesses, wrap back to beginning
        if (blinkIdx > successCount) {
            blinkIdx = -2;
        }
        // switch light
        else if (blinkIdx >= 0) {
            int ledIdx = blinkOrder[blinkIdx];
            blnk->set(ledIdx);
        }
    }
}
