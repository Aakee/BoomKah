#ifndef FEEDBACK_HANDLER
#define FEEDBACK_HANDLER


/*
  Class to handle the feedback back to the user: sound and visual cues.
  (Currently only sound cues.)
*/
class FeedbackHandler {

  public:

    // Creator and destructor
    FeedbackHandler(int buz, int red, int grn);
    ~FeedbackHandler();

    // Functionalities to give feedback for correct actions
    void correct();
    void module_deactivated();
    void bomb_defused();

    // Functionality to give feedback for erroneous actions
    void error();

    // RG LED operation
    void red();
    void green();
    void off();

    // Check the que for next feedbacks to play
    bool tick();

  
  private:

    //  Functions, constants and variables to determine timeout on errors
    int calculateTimeout();
    void insertTimestampIntoArray();
    unsigned long errorTimestamps[20] = {0};
    int errorTimestampIdx = 0;
    bool madeError = false;
    unsigned long lastError = 0;
    int timeout = 1000;
    const int maxTimeout = 10000;
    const int minTimeout = 1000;

    // Arduino pins
    int buzPin;
    int redPin;
    int grnPin;

    // Frequencies for the sounds
    const int error_freq = 110;
    const int success_freq = 880;

    // Sound and blink lengths
    const int singleSoundLength = 300;
    const int singleBlinkLength = 300;

    const int doubleSoundLength = 200;
    const int doubleBlinkLength = 200;
    const int doubleRestLength = 200;

    const int tripleSoundLength = 300;
    const int tripleBlinkLength = 20000;
    const int tripleRestLength = 100;

    const int errorSoundLength = 700;
    const int defaultErrorBlinkLength = 1000;
    const int errorBlinkLength = 1000;

    // For the double and triple beep: how many beeps there are still left, and when was the last beep played
    int beepsLeft = 0;
    int blinksLeft = 0;
    unsigned long lastPlayed = 0;
    unsigned long lastBlinked = 0;

    // Length of the current sound and the rest coming after that, in milliseconds
    int soundLength = 0;
    int blinkLength = 0;
    int restLength = 0;

};

#endif