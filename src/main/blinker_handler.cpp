#include "blinker_handler.h"
#include "Arduino.h"

/*
Parameters:
  int wp        Arduino pin of white led
  int bp        Arduino pin of blue led
  int yp        Arduino pin of yellow led
*/
BlinkerHandler::BlinkerHandler(int rp, int gp, int bp, int yp) {
  redPin        = rp;
  greenPin      = gp;
  bluePin       = bp;
  yellowPin     = yp;
  pinMode(redPin,       OUTPUT);
  pinMode(greenPin,     OUTPUT);
  pinMode(bluePin,      OUTPUT);
  pinMode(yellowPin,    OUTPUT);
}


BlinkerHandler::~BlinkerHandler() { 
}


/*
  Sets the blinker LEDs on or off as given in the method parameters.
  Parameters:
    bool redVal      Whether to set red led on (true) or off (false)
    bool greenVal    Whether to set green led on (true) or off (false)
    bool blueVal     Whether to set blue led on (true) or off (false)
    bool yellowVal   Whether to set yellow led on (true) or off (false)
*/
void BlinkerHandler::set(bool redVal, bool greenVal, bool blueVal, bool yellowVal) {
  if (redVal)     {digitalWrite(redPin,     HIGH);}
  else            {digitalWrite(redPin,     LOW);}

  if (greenVal)   {digitalWrite(greenPin,   HIGH);}
  else            {digitalWrite(greenPin,   LOW);}

  if (blueVal)    {digitalWrite(bluePin,    HIGH);}
  else            {digitalWrite(bluePin,    LOW);}

  if (yellowVal)  {digitalWrite(yellowPin,  HIGH);}
  else            {digitalWrite(yellowPin,  LOW);}
}


/*
  Sets the blinker LEDs according to the bits given as the parameter.
  The state of each LED is taken as a bit of the given parameter: the least significant bit
  denotes red, second green, third blue, and fourth lsb yellow LED.
  E.g. 0x0011 sets red andgreen LEDs on and blue and yellow LEDs off.
  Parameters:
    char ledSum     Bits for the LEDs to be turned on or off
*/
void BlinkerHandler::set(char ledSum) {
  bool r=false; bool g=false; bool b=false; bool y=false;
  ledSum = ledSum % 16;
  if (ledSum & 1 << 0) {r=true;}
  if (ledSum & 1 << 1) {g=true;}
  if (ledSum & 1 << 2) {b=true;}
  if (ledSum & 1 << 3) {y=true;}
  set(r,g,b,y);
}


/*
  Sets the blinker LEDs according to the color given as the parameter.
  Parameters:
    Color c     Color of the LED to be turned off; set other LED's off
*/
void BlinkerHandler::set(Color c) {
  if      (c == red)     {set(0);}
  else if (c == green)   {set(1);}
  else if (c == blue)    {set(2);}
  else if (c == yellow)  {set(3);}
  else {off();}
}


/*
  Sets the LED with the given idx on, and the rest off.
  Indexes: 0=red, 1=green, 2=blue, 3=yellow
  Parameters:
    int ledIdx: Idx of the LED to be turned  on
*/
void BlinkerHandler::set(int ledIdx) {
  if      (ledIdx == 0) {set(true,  false, false, false);}
  else if (ledIdx == 1) {set(false, true,  false, false);}
  else if (ledIdx == 2) {set(false, false, true,  false);}
  else if (ledIdx == 3) {set(false, false, false, true );}
  else {off();}
}


/*
  Turns off all blinker LEDs.
*/
void BlinkerHandler::off() {
  set(false, false, false, false);
}
