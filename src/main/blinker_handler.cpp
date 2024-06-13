#include "blinker_handler.h"
#include "Arduino.h"


BlinkerHandler::BlinkerHandler(int rp, int gp, int bp) {
  redPin    = rp;
  greenPin  = gp;
  bluePin   = bp;
  pinMode(redPin,   OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin,  OUTPUT);
}


BlinkerHandler::~BlinkerHandler() {  }


void BlinkerHandler::set(bool redVal, bool greenVal, bool blueVal) {
  if (redVal)   {digitalWrite(redPin,   HIGH);}
  else          {digitalWrite(redPin,   LOW);}

  if (greenVal) {digitalWrite(greenPin, HIGH);}
  else          {digitalWrite(greenPin, LOW);}

  if (blueVal)  {digitalWrite(bluePin,  HIGH);}
  else          {digitalWrite(bluePin,  LOW);}
}


void BlinkerHandler::off() {
  digitalWrite(redPin,   LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin,  LOW);
}

