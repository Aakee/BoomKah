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
  off();
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
  set(r,g,b);
}


/*
  Sets the color of the RGB led according to index given in the parameter.
  Parameters:
    int idx         Index of the color
*/
void RGBHandler::set(int idx) {
  while (idx > 7) {idx -= 8;}
  while (idx < 0) {idx += 8;}
  Color c = idx;
  set(c);
}


/*
  Sets the individual values of red, green and blue LEDs as given in parameters.
  Acceptable values are in range 0-255.
  Parameters:
    int redVal      Brightness of red LED
    int greenVal    Brightness of green LED
    int blueVal     Brightness of blue LED
*/
void RGBHandler::set(int redVal, int greenVal, int blueVal) {
  // The chosen RGB is common anode, meaning that high voltage to a rgb pin is off and low is on!
  // Remove the "255-" part in the following if using common cathode rgb
  analogWrite(redPin,   255-redVal);
  analogWrite(greenPin, 255-greenVal);
  analogWrite(bluePin,  255-blueVal);
}


/*
  Switches the RGB LED off.
*/
void RGBHandler::off() {
  analogWrite(redPin,   255);
  analogWrite(greenPin, 255);
  analogWrite(bluePin,  255);
}
