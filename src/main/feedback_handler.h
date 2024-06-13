#ifndef FEEDBACK_HANDLER
#define FEEDBACK_HANDLER


/*
  Class to handle the feedback back to the user: sound and visual cues.
  (Currently only sound cues.)
*/
class FeedbackHandler {

  public:

    // Creator and destructor
    FeedbackHandler(int buz);
    ~FeedbackHandler();

    // Functionalities to give feedback for correct actions
    void single_correct();
    void double_correct();
    void triple_correct();

    // Functionality to give feedback for erroneous actions
    void error();

    // Check the que for next feedbacks to play
    void tick();

  
  private:

    // Arduino pin of the buzzer
    int buzPin;

    // Frequencies for the sounds
    int error_freq = 220;
    int success_freq = 880;

    // For the double and triple beep: how many beeps there are still left, and when was the last beep played
    int beepsLeft = 0;
    unsigned long lastPlayed = 0;

    // Length of the current sound and the rest coming after that, in milliseconds
    int soundLength = 0;
    int restLength = 0;

};

#endif