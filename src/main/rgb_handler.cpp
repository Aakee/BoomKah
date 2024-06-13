#include "rgb_handler.h"
#include "Arduino.h"

/*
  Parameters:
    int rp        Arduino pin of red LED
    int gp        Arduino pin of green LED
    int bp        Arduino pin of blue LED
*/
RGBHandler::RGBHandler(int rp, int gp, int bp) {
  redPin    = rp;
  greenPin  = gp;
  bluePin   = bp;
  pinMode(redPin,   OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin,  OUTPUT);
}


RGBHandler::~RGBHandler() {
}


/*
  Sets the color of the RGB led to be the color given in the parameter.
  Parameters:
    Color c         Desired color of the RGB LED
*/
void RGBHandler::set(Color c) {
  int r = colors[3*c];
  int g = colors[3*c+1];
  int b = colors[3*c+2];
  this->set(r,g,b);
}


/*
  Sets the individual values of red, green and blue LEDs as given in parameters.
  Acceptable values are in range 0--255.
  Parameters:
    int redVal      Brightness of red LED
    int greenVal    Brightness of green LED
    int blueVal     Brightness of blue LED
*/
void RGBHandler::set(int redVal, int greenVal, int blueVal) {
  analogWrite(redPin,   redVal);
  analogWrite(greenPin, greenVal);
  analogWrite(bluePin,  blueVal);
}


/*
  Switches the RGB LED off.
*/
void RGBHandler::off() {
  analogWrite(redPin,   0);
  analogWrite(greenPin, 0);
  analogWrite(bluePin,  0);
}
