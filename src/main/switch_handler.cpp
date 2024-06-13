#include "switch_handler.h"
#include "Arduino.h"

/*
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
  // Read statuses of buttons

  if (digitalRead(btn1_pin) == LOW) {currentStates.btn1 = true;}
  else {currentStates.btn1 = false;}

  if (digitalRead(btn2_pin) == LOW) {currentStates.btn2 = true;}
  else {currentStates.btn2 = false;}

  if (digitalRead(btn3_pin) == LOW) {currentStates.btn3 = true;}
  else {currentStates.btn3 = false;}

  if (digitalRead(btn4_pin) == LOW) {currentStates.btn4 = true;}
  else {currentStates.btn4 = false;}

  
  // Read statuses of potentiometers, and translate the analog reading to discrete position

  int pot1angle = analogRead(swtch1_pin);
  if      (pot1angle < 340) {currentStates.swtch1 = -1;}
  else if (pot1angle < 740) {currentStates.swtch1 =  0;}
  else                      {currentStates.swtch1 =  1;}

  int pot2angle = analogRead(swtch2_pin);
  if      (pot2angle < 340) {currentStates.swtch2 = -1;}
  else if (pot2angle < 740) {currentStates.swtch2 =  0;}
  else                      {currentStates.swtch2 =  1;}
}


/*
  Returns:
    SwitchStates* telling the current (last saved) status of buttons and switches
*/
struct SwitchStates* SwitchHandler::get() {
  return &currentStates;
}
