#include "button_module.h"
#include "switch_handler.h"
#include "RGB_handler.h"
#include "blinker_handler.h"
#include "feedback_handler.h"
#include "Arduino.h"

ButtonModule::ButtonModule() {
}

ButtonModule::~ButtonModule() {
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
int ButtonModule::run(SwitchStates* switchStates, RGBHandler* rgbHandler, BlinkerHandler* blinkerHandler) {
    int ret = 0;
    bool btn = switchStates->btn4;

    // First case: Button wasn't pressed but it is now
    if (!buttonPressed && btn) {
        lastSwitch      = millis();
        currentLight   += 1;
    }

    // Second case: Button was pressed but isn't anymore --> player made an attempt
    else if (buttonPressed && !btn) {

        // Correct answer
        if (currentLight == correctAnswers[successCount]) {
            successCount += 1;
            ret = 1;
        }

        // Wrong answers
        else {
            successCount = 0;
            ret = -1;
            Serial.println(ret);
        }
    }

    if (successCount >= maxSuccessCount) {completed=true;}

    // Update the button state and the leds
    buttonPressed = btn;
    setBlinkers(blinkerHandler);
    setRGB(rgbHandler);
    Serial.println(ret);

    return ret;
}


/*
    Sets the blinker LEDs as needed for this module
*/
void ButtonModule::setBlinkers(BlinkerHandler* blnk) {
    // Set blinker off if the button isn't pressed
    if (!buttonPressed) {
        blnk->off();
        return;
    }

    unsigned long currentTime = millis();
    // Check if enough time has passed since the last switch
    if (currentTime - lastSwitch > switchDuration) {
        lastSwitch = currentTime;
        currentLight += 1;
    }
    if (currentLight > 2) {currentLight -= 3;}
    // Show the desired color
    blnk->set(currentLight);
}


/*
    Sets the RGB as needed for this module
*/
void ButtonModule::setRGB(RGBHandler* rgb) {
    // Set RGB off if the button isn't pressed
    if (!buttonPressed) {
        rgb->off();
        return;
    }

    Color c = rgbColors[successCount];
    rgb->set(c);
}