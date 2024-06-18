#include "module_led_handler.h"
#include "Arduino.h"

/*
  Parameters:
    int p1        Arduino pin of the first module LED
    int p2        Arduino pin of the second module LED
    int p3        Arduino pin of the third module LED
    int p4        Arduino pin of the fourth module LED
*/
ModuleLedHandler::ModuleLedHandler(int p1, int p2, int p3, int p4) {
  pin1 = p1; pin2 = p2; pin3 = p3; pin4  = p4;
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);
}


ModuleLedHandler::~ModuleLedHandler() {
}


/*
  Sets the given module LED on and the rest off.
  Parameters:
    int moduleNumber        Which module LED to be turned on (1, 2 or 3)
*/
void ModuleLedHandler::set(int moduleNumber) {
  off();
  if (moduleNumber == 1) {
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
    digitalWrite(pin3, LOW);
    digitalWrite(pin4, LOW);
  }
  if (moduleNumber == 2) {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, HIGH);
    digitalWrite(pin3, LOW);
    digitalWrite(pin4, LOW);
  }
  if (moduleNumber == 3) {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
    digitalWrite(pin3, HIGH);
    digitalWrite(pin4, LOW);
  }
  if (moduleNumber == 4) {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
    digitalWrite(pin3, LOW);
    digitalWrite(pin4, HIGH);
  }
}


/*
  Switches all module LEDs off.
*/
void ModuleLedHandler::off() {
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);
  digitalWrite(pin3, LOW);
  digitalWrite(pin4, LOW);
}

