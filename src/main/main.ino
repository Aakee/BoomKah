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

#include "button_module.h"
#include "directions_module.h"
#include "memory_module.h"


// Define pins for actuators

// Module LEDs
const int RED_LED_1   = 1;
const int RED_LED_2   = 3;
const int RED_LED_3   = 5;

// Blinker LEDs
const int WHT_LED    = 6;
const int BLU_LED    = 7;
const int YLW_LED    = 8;

// RGB LED
const int RGB_RED   = 9;
const int RGB_BLUE  = 10;
const int RGB_GREEN = 11;

// Buttons
const int BTN1 = 0;
const int BTN2 = 2;
const int BTN3 = 4;
const int BTN4 = 12;

// Buzzer
const int BUZ = 13;

// Potentiometers
const int POT1 = A0;
const int POT2 = A1;


// Setup function (nothing here at the moment)
void setup() {
  //Serial.begin(9600);
}


// The main loop
void loop() {

  // Define static objects (same for each loop)

  // Event and hardware managers
  static const auto switches         = SwitchHandler(BTN1, BTN2, BTN3, BTN4, POT1, POT2);
  static const auto moduleLeds       = ModuleLedHandler(RED_LED_1, RED_LED_2, RED_LED_3);
  static const auto rgb              = RGBHandler(RGB_RED, RGB_GREEN, RGB_BLUE);
  static const auto blinkers         = BlinkerHandler(WHT_LED, BLU_LED, YLW_LED);
  static const auto feedback         = FeedbackHandler(BUZ);

  // Modules, i.e. tasks for the players.
  static const auto firstTask        = ButtonModule();
  static const auto secondTask       = DirectionsModule();
  static const auto thirdTask        = MemoryModule();
  

  // Read and get button and potentiometer states
  switches.read();
  SwitchStates* states = switches.get();

  // Initialize return values for the modules
  int ret = 0;  bool moduleCompleted = false;


  // Idea: Find the first module which isn't still completed. Set its module led on.
  // Call the "run" method on the said module, and collect the return value and the status whether the
  // module has now been deactivated or not.
  // Return value of the "run" methods: 1 if user did something right, -1 if wrong, and 0 otherwise.

  // First task
  if (!firstTask.isCompleted()) {
    moduleLeds.set(1);
    ret = firstTask.run(states, &rgb, &blinkers);
    moduleCompleted = firstTask.isCompleted();
  }

  // Second task
  else if (!secondTask.isCompleted()) {
    moduleLeds.set(2);
    ret = secondTask.run(states, &rgb, &blinkers);
    moduleCompleted = secondTask.isCompleted();
  }

  // Third task
  else if (!thirdTask.isCompleted()) {
    moduleLeds.set(3);
    ret = thirdTask.run(states, &rgb, &blinkers);
    moduleCompleted = thirdTask.isCompleted();
  }

  // If all tasks are done, simply turn off all module leds, blinkers and the RGB led
  else {
    moduleLeds.off();
    rgb.off();
    blinkers.off();
  }

  // Check return value of the module and activate feedback
  if      (ret ==  1 && !moduleCompleted) {feedback.single_correct();}
  else if (ret ==  1 && moduleCompleted && !thirdTask.isCompleted()) {feedback.double_correct();}
  else if (ret ==  1 && thirdTask.isCompleted()) {feedback.triple_correct();}
  else if (ret == -1) {feedback.error();}

  // Tick the feedback, i.e. check if a new sound needs to be played
  feedback.tick();
  //delay(100);

}
