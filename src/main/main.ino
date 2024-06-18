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
const int MOD_LED_1   = 0;
const int MOD_LED_2   = 1;
const int MOD_LED_3   = 2;
const int MOD_LED_4   = 3;

// Blinker LEDs
const int RED_LED    = 4;
const int GRN_LED    = 5;
const int BLU_LED    = 6;
const int YLW_LED    = 7;

// Buzzer
const int BUZ        = 8;

// RGB LED
const int RGB_RED    = 9;
const int RGB_BLUE   = 10;
const int RGB_GREEN  = 11;

// RG LED
const int RG_RED     = 12;
const int RG_GREEN   = 13;

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
  //static const auto firstTask        = ButtonModule();
  //static const auto secondTask       = DirectionsModule();
  //static const auto thirdTask        = MemoryModule();
  

  // Read and get button and potentiometer states
  switches.read();
  SwitchStates* states = switches.get();


  bool canContinue = feedback.tick();
  if (!canContinue) {return;}

  char ledValue = 0;
  if (states->btn1) {ledValue += 0b0001;}
  if (states->btn2) {ledValue += 0b0010;}
  if (states->btn3) {ledValue += 0b0100;}
  if (states->btn4) {ledValue += 0b1000;}
  blinkers.set(ledValue);

  int redval = 0;  int bluval=0;  int grnval = 0;
  if (states->swtch1 < 0) {redval = 10;}
  if (states->swtch1 > 0) {bluval = 10;}
  if (states->swtch2 < 0) {redval = 10;}
  if (states->swtch2 > 0) {grnval = 10;}
  rgb.set(redval, grnval, bluval);

  if (states->btn1) {feedback.correct();}
  if (states->btn2) {feedback.module_deactivated();}
  if (states->btn3) {feedback.bomb_defused();}
  if (states->btn4) {feedback.error();}

}
