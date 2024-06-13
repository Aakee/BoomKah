#include "feedback_handler.h"
#include "Arduino.h"

/*
  Parameters:
    int buz       Arduino pin for the buzzer
*/
FeedbackHandler::FeedbackHandler(int buz) {
  buzPin = buz;
  pinMode(buzPin, OUTPUT);
}


FeedbackHandler::~FeedbackHandler() {
}


/*
  Plays a single sound for correct action
*/
void FeedbackHandler::single_correct() {
  tone(buzPin,success_freq,300);
  beepsLeft = 0;
}


/*
  Plays double sound for correct action
*/
void FeedbackHandler::double_correct() {
  tone(buzPin,success_freq,200);
  beepsLeft = 1;
  lastPlayed = millis();
  soundLength = 200;
  restLength = 100;
}


/*
  Plays triple sound for correct action
*/
void FeedbackHandler::triple_correct() {
  soundLength = 300;
  tone(buzPin,success_freq,soundLength);
  beepsLeft = 2;
  lastPlayed = millis();
  restLength = 100;
}


/*
  Plays a single sound for wrong action
*/
void FeedbackHandler::error() {
  tone(buzPin,error_freq,300);
}


/*
  Checks if the next 'queued' sound should be played
*/
void FeedbackHandler::tick() {
  if (beepsLeft > 0 && millis() > lastPlayed + soundLength + restLength) {
    tone(buzPin,success_freq,soundLength);
    beepsLeft -= 1;
    lastPlayed = millis();
  }
}

