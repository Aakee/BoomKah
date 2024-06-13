// Class to handle the feedback to the user: sound and rg led

#ifndef FEEDBACK_HANDLER
#define FEEDBACK_HANDLER

class FeedbackHandler {

  public:

    // Creator and destructor
    FeedbackHandler(int buz);
    ~FeedbackHandler();

    // Functionalities for correct behaviour
    void single_correct();
    void double_correct();
    void triple_correct();

    // Functionality for error
    void error();

    void tick();

  
  private:
    int buzPin;

    // Frequencies for the sounds
    int error_freq = 220;
    int success_freq = 880;

    int beepsLeft = 0;
    unsigned long lastPlayed = 0;

    int soundLength = 0;
    int restLength = 0;

};

#endif