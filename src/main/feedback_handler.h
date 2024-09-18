#ifndef FEEDBACK_HANDLER
#define FEEDBACK_HANDLER

/*
  Class to handle the feedback back to the user: sound and visual cues.
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

    // Functionality to give feedback for wrong actions
    void error();

    // Red-green LED operation
    void red();
    void green();
    void off();

    // Check and update the current feedback state
    bool tick();

  
  private:

    // Functions, constants and variables to determine timeout on errors
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
    int buzPin;   // Buzzer (piezo loudspeaker)
    int redPin;   // Red led pin
    int grnPin;   // Green led pin

    // Frequencies for the sounds
    const int error_freq = 110;
    const int success_freq = 880;


    // Sound and blink lengths

    // Single beep for one correct action
    const int singleSoundLength = 300;
    const int singleBlinkLength = 300;

    // Double beep for deactivated module
    const int doubleSoundLength = 200;
    const int doubleBlinkLength = 200;
    const int doubleRestLength = 200;   // Time between the blinks / beeps

    // Triple beep for defused bomb
    const int tripleSoundLength = 300;
    const int tripleBlinkLength = 20000;
    const int tripleRestLength = 100;

    // Low beep for wrong actions
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