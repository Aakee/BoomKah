/*

*/

//#include "pitches.h"
//#include "button_module.h"
#include "switch_handler.h"
#include "module_led_handler.h"
#include "rgb_handler.h"
#include "blinker_handler.h"
#include "feedback_handler.h"
#include "Arduino.h"


// Define pins for actuators

// LEDs
const int redLed1 = 1;
const int redLed2 = 3;
const int redLed3 = 5;
const int whtLed = 6;
const int bluLed = 7;
const int ylwLed = 8;
const int rgbLed1 = 9;
const int rgbLed2 = 10;
const int rgbLed3 = 11;

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


SwitchHandler switches        = SwitchHandler(btn1, btn2, btn3, btn4, pot1, pot2);
ModuleLedHandler moduleLeds   = ModuleLedHandler(redLed1, redLed2, redLed3);
RGBHandler rgb                = RGBHandler(rgbLed1, rgbLed2, rgbLed3);
BlinkerHandler blinkers       = BlinkerHandler(whtLed, bluLed, ylwLed);
FeedbackHandler buzzer        = FeedbackHandler(buz);


void setup() {
  // initialize serial communication at 9600 bits per second, for debugging
  Serial.begin(9600);

  pinMode(buz, OUTPUT);


  
}



void loop() {
  switches.read();
  SwitchStates* states = switches.get();
  
  if (states->swtch1 == -1) {moduleLeds.set(1);}
  if (states->swtch1 ==  0) {moduleLeds.set(2);}
  if (states->swtch1 ==  1) {moduleLeds.set(3);}

  if (states->swtch2 == -1) {blinkers.set(true, false, false);}
  if (states->swtch2 ==  0) {blinkers.set(false, true, false);}
  if (states->swtch2 ==  1) {blinkers.set(false, false, true);}

  if      (states->btn1) {rgb.set(255,0,0);}
  else if (states->btn2) {rgb.set(0,255,0);}
  else if (states->btn3) {rgb.set(0,0,255);}
  else if (states->btn4) {buzzer.triple_correct();}
  else {rgb.off();}

  buzzer.tick();
  delay(10);

}
