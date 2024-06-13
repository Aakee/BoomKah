#include "blinker_handler.h"
#include "Arduino.h"

/*
Parameters:
  int wp        Arduino pin of white led
  int bp        Arduino pin of blue led
  int yp        Arduino pin of yellow led
*/
BlinkerHandler::BlinkerHandler(int wp, int bp, int yp) {
  whitePin      = wp;
  bluePin       = bp;
  yellowPin     = yp;
  pinMode(whitePin,     OUTPUT);
  pinMode(bluePin,      OUTPUT);
  pinMode(yellowPin,    OUTPUT);
}


BlinkerHandler::~BlinkerHandler() { 
}


/*
  Sets the blinker LEDs on or off as given in the method parameters.
  Parameters:
    bool whiteVal    Whether to set white led on (true) or off (false)
    bool blueVal     Whether to set blue led on (true) or off (false)
    bool yellowVal   Whether to set yellow led on (true) or off (false)
*/
void BlinkerHandler::set(bool whiteVal, bool blueVal, bool yellowVal) {
  if (whiteVal)   {digitalWrite(whitePin,   HIGH);}
  else            {digitalWrite(whitePin,   LOW);}

  if (blueVal)    {digitalWrite(bluePin,    HIGH);}
  else            {digitalWrite(bluePin,    LOW);}

  if (yellowVal)  {digitalWrite(yellowPin,  HIGH);}
  else            {digitalWrite(yellowPin,  LOW);}
}


/*
  Sets the blinker LEDs according to the bits given as the parameter.
  The state of each LED is taken as a bit of the given parameter: the least significant bit
  denotes white, second blue, and third lsb yellow LED.
  E.g. 0x0011 sets white and blue LEDs on and yellow LED off.
  Parameters:
    char ledSum     Bits for the LEDs to be turned on or off
*/
void BlinkerHandler::set(char ledSum) {
  int r=false; int g=false; int b=false;
  if (ledSum & 1 << 0) {r=true;}
  if (ledSum & 1 << 1) {g=true;}
  if (ledSum & 1 << 2) {b=true;}
  set(r,g,b);
}


/*
  Sets the LED with the given idx on, and the rest off.
  Indexes: 0=white, 1=blue, 2=yellow
  Parameters:
    int ledIdx: Idx of the LED to be turned  on
*/
void BlinkerHandler::set(int ledIdx) {
  off();
  if (ledIdx == 0) {this->set(true,  false, false);}
  if (ledIdx == 1) {this->set(false, true,  false);}
  if (ledIdx == 2) {this->set(false, false, true );}
}


/*
  Turns off all blinker LEDs.
*/
void BlinkerHandler::off() {
  digitalWrite(whitePin,    LOW);
  digitalWrite(bluePin,     LOW);
  digitalWrite(yellowPin,   LOW);
}
