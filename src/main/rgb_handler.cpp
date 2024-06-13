#include "rgb_handler.h"
#include "Arduino.h"


RGBHandler::RGBHandler(int rp, int gp, int bp) {
  redPin    = rp;
  greenPin  = gp;
  bluePin   = bp;
  pinMode(redPin,   OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin,  OUTPUT);
}


RGBHandler::~RGBHandler() {  }


void RGBHandler::set(int redVal, int greenVal, int blueVal) {
  analogWrite(redPin,   redVal);
  analogWrite(greenPin, greenVal);
  analogWrite(bluePin,  blueVal);
}


void RGBHandler::off() {
  analogWrite(redPin,   0);
  analogWrite(greenPin, 0);
  analogWrite(bluePin,  0);
}
