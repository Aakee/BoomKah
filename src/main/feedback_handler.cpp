#include "feedback_handler.h"
#include "Arduino.h"

/*
  Parameters:
    int buz       Arduino pin for the buzzer
    int red       Arduino pin for red led
    int grn       Arduino pin for green led
*/
FeedbackHandler::FeedbackHandler(int buz, int red, int grn) {
  buzPin = buz;
  redPin = red;
  grnPin = grn;
  pinMode(buzPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(grnPin, OUTPUT);
}


FeedbackHandler::~FeedbackHandler() {
}


/*
  Plays a single sound and flash led green for correct action
*/
void FeedbackHandler::correct() {
  tone(buzPin, success_freq, singleSoundLength);
  beepsLeft = 0;
  blinksLeft = 0;
  lastBlinked = millis();
  blinkLength = singleBlinkLength;
  restLength = 0;
  green();
}


/*
  Plays double sound and flashes green twice for deactivated module
*/
void FeedbackHandler::module_deactivated() {
  tone(buzPin, success_freq, doubleSoundLength);
  beepsLeft = 1;
  blinksLeft = 1;
  lastPlayed = millis();
  lastBlinked = millis();
  soundLength = doubleSoundLength;
  blinkLength = doubleBlinkLength;
  restLength = doubleRestLength;
  green();
}


/*
  Plays triple sound and leave green on for defused bomb
*/
void FeedbackHandler::bomb_defused() {
  tone(buzPin, success_freq, tripleSoundLength);
  beepsLeft = 2;
  blinksLeft = 0;
  lastPlayed = millis();
  lastBlinked = millis();
  soundLength = tripleSoundLength;
  blinkLength = tripleBlinkLength;
  restLength = tripleRestLength;
  green();
}


/*
  Plays a single low sound and blink red red for wrong action
*/
void FeedbackHandler::error() {
  madeError = true;
  insertTimestampIntoArray();
  timeout = calculateTimeout();
  tone(buzPin,error_freq,700);
  beepsLeft = 0;
  blinksLeft = 0;
  lastBlinked = millis();
  lastError = millis();
  blinkLength = errorBlinkLength;
  restLength = 0;
  red();
}


/*
  Sets the red LED on
*/
void FeedbackHandler::red() {
  off();
  digitalWrite(redPin, HIGH);
}


/*
  Sets the green LED on
*/
void FeedbackHandler::green() {
  off();
  digitalWrite(grnPin, HIGH);
}


/*
  Sets the RG LED off
*/
void FeedbackHandler::off() {
  digitalWrite(redPin, LOW);
  digitalWrite(grnPin, LOW);
}


/*
  Checks if the next 'queued' sound and light should be played.
  Returns true if the player can continue defusing the bomb, or false if there is still
  cooldown left for wrong actions.
*/
bool FeedbackHandler::tick() {
  // Check double- and triple beeps
  if (beepsLeft > 0 && millis() > lastPlayed + soundLength + restLength) {
    tone(buzPin,success_freq,soundLength);
    beepsLeft -= 1;
    lastPlayed = millis();
  }
  // Turn the green led off if needed
  if (!madeError && millis() > lastBlinked + blinkLength) {
    off();
  }
  // Turn the red led off if needed
  else if (madeError && millis() > lastError + timeout) {
    madeError =  false;
    off();
  }
  // Turn the green led on again if needed
  if (blinksLeft > 0 && millis() > lastBlinked + blinkLength + restLength) {
    green();
    blinksLeft -= 1;
    lastBlinked = millis();
  }
  // Return false, if there is still cooldown for wrong actions; else, return true.
  if (madeError) {return false;}
  return true;
}

/*
  Calculates the timeout for wrong actions
*/
int FeedbackHandler::calculateTimeout() {
  unsigned long currTime = millis();
  int nErrors = 0;
  // Calculate the number of errors in the last 60 seconds
  for (int idx=0; idx < 20; idx++) {
    if (currTime - errorTimestamps[idx] < 60000 && errorTimestamps[idx] > 0) {
      nErrors++;
    }
  }
  // Timeout = 0.5 seconds * nof errors during the last minute
  // (minimum: minTimeout, maximum: maxTimeout)
  int to = nErrors * 500;
  if (to < minTimeout) {to = minTimeout;}
  if (to > maxTimeout) {to = maxTimeout;}
  return to;
}

/*
  Adds the current timestamp to the circular array errorTimestamps
*/
void FeedbackHandler::insertTimestampIntoArray() {
  errorTimestamps[errorTimestampIdx] = millis();
  errorTimestampIdx++;
  if (errorTimestampIdx >= 20) { errorTimestampIdx=0;}  // move the circular index back to 0 if needed
}
