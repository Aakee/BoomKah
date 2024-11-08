#ifndef SWITCH_HANDLER
#define SWITCH_HANDLER

/*
  Enum telling the position of a single three-stage switch
*/
enum SwitchPosition {down=0, middle=1, up=2,};


/*
  Struct to combine the current states of buttons and switches. 
*/
struct SwitchStates {
  // Buttons 1-4
  bool btn1;
  bool btn2;
  bool btn3;
  bool btn4;
  // Switches 1 and 2
  SwitchPosition swtch1;
  SwitchPosition swtch2;
};


/*
  Class handles reading and reporting the status of buttons and switches
*/
class SwitchHandler {

  public:

    // Creator and destructor
    SwitchHandler(int b1pin, int b2pin, int b3pin, int b4pin, int s1pin, int s2pin);
    ~SwitchHandler();

    // Reads the button and switch states and saves them to a struct
    void read();

    // Returns the struct telling button statuses
    struct SwitchStates* get(); 
    
  
  private:
    // Holds the buffered states of buttons and switches
    struct SwitchStates currentStates;

    // Arduino pins of buttons and switches
    int btn1_pin;
    int btn2_pin;
    int btn3_pin;
    int btn4_pin;
    int swtch1_pin;
    int swtch2_pin;

    // "Real" button states, that is, states read from pins
    bool buttonRealStates[4] = {false, false, false, false};

    // Timestamps of last registered change of button "real" states
    unsigned long buttonsLastChange[4] = {0,0,0,0};

    // This many milliseconds must pass without the state of button changing so that the change will be registered
    unsigned long buttonStateChangeBuffer = 100; // milliseconds

};

#endif