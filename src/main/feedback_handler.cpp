#include "feedback_handler.h"
#include "Arduino.h"


FeedbackHandler::FeedbackHandler(int buz) {
  buzPin = buz;
  pinMode(buzPin, OUTPUT);
}

FeedbackHandler::~FeedbackHandler() {  }


void FeedbackHandler::single_correct() {
  tone(buzPin,success_freq,300);
  beepsLeft = 0;
}

void FeedbackHandler::double_correct() {
  tone(buzPin,success_freq,200);
  beepsLeft = 1;
  lastPlayed = millis();
  soundLength = 200;
  restLength = 100;
}

void FeedbackHandler::triple_correct() {
  soundLength = 300;
  tone(buzPin,success_freq,soundLength);
  beepsLeft = 2;
  lastPlayed = millis();
  restLength = 100;
}

void FeedbackHandler::error() {
  tone(buzPin,error_freq,220);
}

void FeedbackHandler::tick() {
  if (beepsLeft > 0 && millis() > lastPlayed + soundLength + restLength) {
    tone(buzPin,success_freq,soundLength);
    beepsLeft -= 1;
    lastPlayed = millis();
  }
}

