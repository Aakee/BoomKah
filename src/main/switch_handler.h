#ifndef SWITCH_HANDLER
#define SWITCH_HANDLER

// Struct to describe the current state of all the buttons and switches
struct SwitchStates {
  // Buttons 1-4
  bool btn1;
  bool btn2;
  bool btn3;
  bool btn4;
  // Switches 1 and 2
  int swtch1;
  int swtch2;
};


// Class to handle reading and reporting the button and switch states

class SwitchHandler {

  public:

    // Creator and destructor
    SwitchHandler(int b1pin, int b2pin, int b3pin, int b4pin, int s1pin, int s2pin);
    ~SwitchHandler();

    // Reads the button and switch states and saves them to a struct
    void read();
    struct SwitchStates* get(); 
    
  
  private:
    struct SwitchStates currentStates;

    int btn1_pin;
    int btn2_pin;
    int btn3_pin;
    int btn4_pin;
    int swtch1_pin;
    int swtch2_pin;

};

#endif