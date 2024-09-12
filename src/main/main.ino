/*
    Main code for the Boom Kah - Keep Talking and Nobody Explodes -type game
    for Arduino Hardware.

    Refer for other documentation for wiring diagram and game rules.


    Author: Akseli Konttas 2024
*/

#include "switch_handler.h"
#include "module_led_handler.h"
#include "rgb_handler.h"
#include "blinker_handler.h"
#include "feedback_handler.h"
#include "Arduino.h"

#include "test_module.h"
#include "switches_module.h"
#include "pin_module.h"
#include "simon_module.h"
#include "venn_module.h"


// false --> always the same answers. true --> randomizes the proceedings
const bool RANDOMIZE = false;

const bool EASYMODE = true;

// Define pins for actuators

// Module LEDs
const int MOD_LED_1   = 1;
const int MOD_LED_2   = 0;
const int MOD_LED_3   = 2;
const int MOD_LED_4   = 3;

// Blinker LEDs
const int RED_LED    = 4;
const int GRN_LED    = 6;
const int BLU_LED    = 7;
const int YLW_LED    = 11;

// Buzzer
const int BUZ        = 8;

// RGB LED
const int RGB_RED    = 5;
const int RGB_BLUE   = 10;
const int RGB_GREEN  = 9;

// RG LED
const int RG_RED     = 13;
const int RG_GREEN   = 12;

// Buttons
const int BTN1       = A0;
const int BTN2       = A1;
const int BTN3       = A2;
const int BTN4       = A3;

// Switches
const int SWTCH1     = A4;
const int SWTCH2     = A5;


// Setup function (nothing here at the moment)
void setup() {
  //Serial.begin(9600);
}


// The main loop
void loop() {

  // Define static objects (same for each loop)

  // Event and hardware managers
  static const auto switches         = SwitchHandler(BTN1, BTN2, BTN3, BTN4, SWTCH1, SWTCH2);
  static const auto moduleLeds       = ModuleLedHandler(MOD_LED_1, MOD_LED_2, MOD_LED_3, MOD_LED_4);
  static const auto rgb              = RGBHandler(RGB_RED, RGB_GREEN, RGB_BLUE);
  static const auto blinkers         = BlinkerHandler(RED_LED, GRN_LED, BLU_LED, YLW_LED);
  static const auto feedback         = FeedbackHandler(BUZ, RG_RED, RG_GREEN);

  // Modules, i.e. tasks for the players.
  //static const auto firstTask         = TestModule(RANDOMIZE);
  static const auto firstTask         = SwitchesModule(RANDOMIZE);
  static const auto secondTask        = SimonModule(RANDOMIZE);
  static const auto thirdTask         = VennModule(RANDOMIZE, EASYMODE);
  static const auto fourthTask        = PINModule(RANDOMIZE);

  // Tick the feedback light and sound, and see if the player is on cooldown
  bool canContinue = feedback.tick();
  if (!canContinue) {
    rgb.off(); blinkers.off(); return;
  }

  // Read and get button and switch states
  switches.read();
  SwitchStates* states = switches.get();

  // Initialize module return value
  int success = 0;


  // Run through the first not-yet-completed task
  if (!firstTask.isCompleted()) {
    moduleLeds.set(1);
    success = firstTask.run(states, &rgb, &blinkers);
  }
  else if (!secondTask.isCompleted()) {
    moduleLeds.set(2);
    success = secondTask.run(states, &rgb, &blinkers);
  }
  else if (!thirdTask.isCompleted()) {
    moduleLeds.set(3);
    success = thirdTask.run(states, &rgb, &blinkers);
  }
  else if (!fourthTask.isCompleted()) {
    moduleLeds.set(4);
    success = fourthTask.run(states, &rgb, &blinkers);
  }
  
  // If the last module was just completed --> bomb defused, set blinkers off and send feedback
  if (success == 2 && fourthTask.isCompleted()) {
    rgb.off();
    blinkers.off();
    moduleLeds.off();
    feedback.bomb_defused();
  }

  // Otherwise, do actions based on the return value of the module
  else if (success ==  1) {feedback.correct();}
  else if (success ==  2) {feedback.module_deactivated();}
  else if (success == -1) {feedback.error();}

  // Advance the pseudo random number generator
  random();

}
