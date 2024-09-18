#include "switch_handler.h"
#include "Arduino.h"

/*
  Refer to the wiring diagram for the switch and button wiring.
  Parameters:
    int b1pin         Arduino pin for button 1
    int b2pin         Arduino pin for button 2
    int b3pin         Arduino pin for button 3
    int b4pin         Arduino pin for button 4
    int s1pin         Arduino pin for switch 1
    int s2pin         Arduino pin for switch 2
*/
SwitchHandler::SwitchHandler(int b1pin, int b2pin, int b3pin, int b4pin, int s1pin, int s2pin) {
  btn1_pin = b1pin;
  btn2_pin = b2pin;
  btn3_pin = b3pin;
  btn4_pin = b4pin;
  swtch1_pin = s1pin;
  swtch2_pin = s2pin;

  pinMode(btn1_pin, INPUT);
  pinMode(btn2_pin, INPUT);
  pinMode(btn3_pin, INPUT);
  pinMode(btn4_pin, INPUT);
  pinMode(swtch1_pin, INPUT);
  pinMode(swtch2_pin, INPUT);
}


SwitchHandler::~SwitchHandler() {
}


/*
  Reads and saves the current statuses of the buttons and switches.
*/
void SwitchHandler::read() {
  unsigned long currentTime = millis();

  // Read "real" statuses of buttons
  int pins[4] = {btn1_pin, btn2_pin, btn3_pin, btn4_pin};
  bool bufferedStates[4] = {currentStates.btn1, currentStates.btn2, currentStates.btn3, currentStates.btn4};

  // Buffer button statuses such that the changes are registered if the current status has persisted
  // constantly at least a pre-determined amount of time. This is to reduce effect of static noise
  // or annoyance of barely-closed buttons, etc.
  for (int idx=0; idx < 4; idx++) {
    bool currentState = digitalRead(pins[idx]);
    if (currentState != buttonRealStates[idx]) { buttonsLastChange[idx] = currentTime; }
    if (currentTime - buttonsLastChange[idx] > buttonStateChangeBuffer) {bufferedStates[idx] = currentState;}
    buttonRealStates[idx] = digitalRead(pins[idx]);
  }

  currentStates.btn1 = bufferedStates[0];
  currentStates.btn2 = bufferedStates[1];
  currentStates.btn3 = bufferedStates[2];
  currentStates.btn4 = bufferedStates[3];

  // Read and save switch positions (no buffering is needed here)
  // Change the voltage limits and/or order of the states if needed (if the switch is wired differently from the diagram)
  int sw1pos = analogRead(swtch1_pin);
  if      (sw1pos < 250) {currentStates.swtch1 = down;}
  else if (sw1pos < 750) {currentStates.swtch1 = up;}
  else                   {currentStates.swtch1 = middle;}

  int sw2pos = analogRead(swtch2_pin);
  if      (sw2pos < 250) {currentStates.swtch2 = down;}
  else if (sw2pos < 750) {currentStates.swtch2 = up;}
  else                   {currentStates.swtch2 = middle;}
}


/*
  Returns:
    SwitchStates* telling the current (last saved) status of buttons and switches
*/
struct SwitchStates* SwitchHandler::get() {
  return &currentStates;
}
