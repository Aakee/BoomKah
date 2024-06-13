#include "module_led_handler.h"
#include "Arduino.h"


ModuleLedHandler::ModuleLedHandler(int p1, int p2, int p3) {
  pin1 = p1; pin2 = p2; pin3 = p3;
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
}


ModuleLedHandler::~ModuleLedHandler() { }


void ModuleLedHandler::set(int moduleNumber) {
  if (moduleNumber == 1) {
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
    digitalWrite(pin3, LOW);
  }
  if (moduleNumber == 2) {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, HIGH);
    digitalWrite(pin3, LOW);
  }
  if (moduleNumber == 3) {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
    digitalWrite(pin3, HIGH);
  }
}


void ModuleLedHandler::off() {
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);
  digitalWrite(pin3, LOW);
}

