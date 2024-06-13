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
const int redLed1   = 1;
const int redLed2   = 3;
const int redLed3   = 5;

// Blinker LEDs
const int whtLed    = 6;
const int bluLed    = 7;
const int ylwLed    = 8;

// RGB LED
const int rgb_red   = 9;
const int rgb_blue  = 10;
const int rgb_green = 11;

// Buttons
const int btn1 = 0;
const int btn2 = 2;
const int btn3 = 4;
const int btn4 = 12;

// Buzzer
const int buz = 13;

// Potentiometers
const int pot1 = A0;
const int pot2 = A1;


// Global objects

// Event and hardware managers
auto switches         = SwitchHandler(btn1, btn2, btn3, btn4, pot1, pot2);
auto moduleLeds       = ModuleLedHandler(redLed1, redLed2, redLed3);
auto rgb              = RGBHandler(rgb_red, rgb_green, rgb_blue);
auto blinkers         = BlinkerHandler(whtLed, bluLed, ylwLed);
auto feedback         = FeedbackHandler(buz);

// Modules, i.e. tasks for the players.
auto firstTask        = ButtonModule();
auto secondTask       = DirectionsModule();
auto thirdTask        = MemoryModule();


// Setup function (nothing here at the moment)
void setup() {
  //Serial.begin(9600);
}


// The main loop
void loop() {

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
