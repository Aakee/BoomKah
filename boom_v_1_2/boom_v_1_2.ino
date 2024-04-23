/*

*/

#include "pitches.h"


// Define pins for actuators

// LEDs
const int redLed1 = 1;
const int redLed2 = 3;
const int redLed3 = 5;
const int whtLed = 6;
const int bluLed = 7;
const int ylwLed = 8;
const int rgbLed1 = 9;
const int rgbLed2 = 10;
const int rgbLed3 = 11;

// Buttons
const int btn1 = 0;
const int btn2 = 2;
const int btn3 = 4;
const int btn4 = 12;

// Buzzer
const int buz = 13;

// Potentiometers
const int pot1 = A0;
const int pot2 = A1;



// Flags to see which tasks are done

bool firstTaskDone = false;
bool secondTaskDone = false;
bool thirdTaskDone = false;


// First task variables and flags: simple button
int firstTask_successCount = 0;
bool firstTask_buttonPressed = false;
unsigned long firstTask_lastSwitch = 0;
int firstTask_currentLight = 0;
int firstTask_correctAnswers[3] = {2,1,1};

// Second task variables and flags: potentiometers
int secondTask_successCount = 0;
int secondTask_currentBlinker = -1;
bool secondTask_buttonBuffer = false;
int secondTask_correctAnswers[2] = {0,1};

// Third task variables and flags: memory game
int thirdTask_successCount = 0;
int thirdTask_buttonPressNumber = 0;
unsigned long thirdTask_lastSwitch = 0;
int thirdTask_blinkOrder[5] = {2,1,0};
int thirdTask_blinkIdx = -2;
int thirdTask_buttonBuffer = false;
int thirdTask_correctAnswers1 = 2;
int thirdTask_correctAnswers2[2] = {0,2};
int thirdTask_correctAnswers3[3] = {1,0,2};


// Buzzer flags and variables
int buzzerBeepsLeft = 0;
unsigned long buzzerLastPlayed = 0;
int buzzerSoundLength = 200;
int buzzerRestLength = 100;
bool errorSound = false;




void setup() {
  // initialize serial communication at 9600 bits per second, for debugging
  //Serial.begin(9600);
  
  // Set pin modes
  pinMode(redLed1, OUTPUT);
  pinMode(redLed2, OUTPUT);
  pinMode(redLed3, OUTPUT);
  
  pinMode(whtLed, OUTPUT);
  pinMode(ylwLed, OUTPUT);
  pinMode(bluLed, OUTPUT);
  
  pinMode(rgbLed1, OUTPUT);
  pinMode(rgbLed2, OUTPUT);
  pinMode(rgbLed3, OUTPUT);
  
  pinMode(buz, OUTPUT);
  
  pinMode(btn1, INPUT);
  pinMode(btn2, INPUT);
  pinMode(btn3, INPUT);
  

  // Set initial states

  digitalWrite(redLed1,LOW);
  digitalWrite(redLed2,LOW);
  digitalWrite(redLed3,LOW);
  digitalWrite(whtLed,LOW);
  digitalWrite(ylwLed,LOW);
  digitalWrite(bluLed,LOW);
  digitalWrite(rgbLed1,LOW);
  digitalWrite(rgbLed2,LOW);
  digitalWrite(rgbLed3,LOW);
  digitalWrite(buz,LOW);
  
}

int getCurrentTask() {
  if (!firstTaskDone) {
    digitalWrite(redLed1,HIGH);
    digitalWrite(redLed2,LOW);
    digitalWrite(redLed3,LOW);
    return 1;
  }
  else if (firstTaskDone && !secondTaskDone) {
    digitalWrite(redLed1,LOW);
    digitalWrite(redLed2,HIGH);
    digitalWrite(redLed3,LOW);
    return 2;
  }
  else if (firstTaskDone && secondTaskDone && !thirdTaskDone) {
    digitalWrite(redLed1,LOW);
    digitalWrite(redLed2,LOW);
    digitalWrite(redLed3,HIGH);
    return 3;
  }
  else {
    digitalWrite(redLed1,LOW);
    digitalWrite(redLed2,LOW);
    digitalWrite(redLed3,LOW);
    return 4;
  }
}

void playErrorSound() {
  tone(buz,NOTE_A3,700);
}

void playSuccessSound() {
  tone(buz,NOTE_A5,300);
}

void playDoubleSuccessSound() {
  tone(buz,NOTE_A5,200);
  buzzerBeepsLeft = 1;
  buzzerLastPlayed = millis();
  buzzerSoundLength = 200;
  buzzerRestLength = 100;
}

void playTripleSuccessSound() {
  tone(buz,NOTE_A5,200);
  buzzerBeepsLeft = 2;
  buzzerLastPlayed = millis();
  buzzerSoundLength = 200;
  buzzerRestLength = 100;
}

void checkBuzzer() {
  if (buzzerBeepsLeft > 0 && millis() > buzzerLastPlayed + buzzerSoundLength + buzzerRestLength) {
    tone(buz,NOTE_A5,buzzerSoundLength);
    buzzerBeepsLeft -= 1;
    buzzerLastPlayed = millis();
  }
}

void setRGBColor(int redValue, int greenValue, int blueValue) {
  analogWrite(rgbLed1, redValue);
  analogWrite(rgbLed2, blueValue);
  analogWrite(rgbLed3, greenValue);
}

void turnOffRGB() {
  setRGBColor(0,0,0);
} 

void firstTask_setRGB(int successes) {
  if (successes == 0) {
    setRGBColor(170,0,255);
  }
  else if (successes == 1) {
    setRGBColor(255,0,0);
  }
  else if (successes == 2) {
    setRGBColor(0,0,255);
  }
  else {
    turnOffRGB();
  }
}

void turnOffBlinkers() {
  digitalWrite(bluLed,LOW);
  digitalWrite(ylwLed,LOW);
  digitalWrite(whtLed,LOW);
}


void firstTask_switchLight() {
  unsigned long currentTime = millis();
  if (currentTime - firstTask_lastSwitch > 1500) {
    firstTask_lastSwitch = currentTime;
    turnOffBlinkers();

    firstTask_currentLight += 1;
    if (firstTask_currentLight > 2) {firstTask_currentLight -= 3;}

    int ledPins[3] = {whtLed, bluLed, ylwLed};
    int ledPin = ledPins[firstTask_currentLight];

    digitalWrite(ledPin,HIGH);
  }
}


// First task: simple button
void firstTask() {

  int btnState = digitalRead(btn4);
  bool successFlag = false;

  // First case: button wasn't pressed
  if (!firstTask_buttonPressed) {
    // ... but it is now
    if (btnState == LOW) {
      firstTask_buttonPressed = true;
      firstTask_lastSwitch = 0;
      firstTask_switchLight();
      firstTask_setRGB(firstTask_successCount);
    }
  }

  else if (firstTask_buttonPressed) {
    // Second case: button was pressed and is still pressed
    if (btnState == LOW) {
      // Check if blinker light needs to be changed
      firstTask_switchLight();
    }

    // Third case: button was pressed but is not anymore
    else {
      firstTask_buttonPressed = false;
      turnOffBlinkers();
      turnOffRGB();

      // Correct answer
      if (firstTask_currentLight == firstTask_correctAnswers[firstTask_successCount]) {
        successFlag = true;
        firstTask_successCount += 1;
      }

      // Wrong answer
      else {
        playErrorSound();
        firstTask_successCount = 0;
      }
    }
  }

  if (firstTask_successCount >= 3) {
    firstTaskDone = true;
    playDoubleSuccessSound();
  }
  else if (successFlag) {
    playSuccessSound();
  }
}

void secondTask_setRGB(int success) {
  if (success == 0) {
    setRGBColor(255,0,0);
  }
  else if (success == 1) {
    setRGBColor(0,0,255);
  }
  else if (success == 2) {
    setRGBColor(0,0,0);
  }
}

void secondTask_setBlinkers(int success) {
  // Find the angle of the first potentiometer
  int angle = analogRead(pot2);
  int dir = -1;
  if (angle < 340) {
    dir = 0;
  } else if (angle < 690) {
    dir = 1;
  } else {
    dir = 2;
  }
  dir += success;
  if (dir >= 3) {
    dir -= 3;
  }

  // Set the correct blinker light
  if (dir != secondTask_currentBlinker) {
    int blinkerPins[3] = {ylwLed,bluLed,whtLed};
    secondTask_currentBlinker = dir;
    turnOffBlinkers();
    digitalWrite(blinkerPins[dir],HIGH);
  }

}

int secondTask_getSecondPotentiometerDirection() {
  int angle = analogRead(pot1);
  int dir = -1;
  if (angle < 340) {
    dir = 0;
  } else if (angle < 740) {
    dir = 1;
  } else {
    dir = 2;
  }
  return dir;
}

void secondTask() {
  secondTask_setRGB(secondTask_successCount);
  secondTask_setBlinkers(secondTask_successCount);
  int direction = secondTask_getSecondPotentiometerDirection();
  int buttonState = digitalRead(btn4);
  bool successFlag = false;

  if (buttonState == LOW && !secondTask_buttonBuffer) {
    secondTask_buttonBuffer = true;
    if (direction == secondTask_correctAnswers[secondTask_successCount]) {
      successFlag = true;
      secondTask_successCount += 1;
    }
    else {
      playErrorSound();
      secondTask_successCount = 0;
    }
  }
  else if (buttonState == HIGH) {
    secondTask_buttonBuffer = false;
  }

  if (secondTask_successCount >= 2) {
    secondTaskDone = true;
    turnOffBlinkers();
    turnOffRGB();
    playDoubleSuccessSound();
  }
  else if (successFlag) {
    playSuccessSound();
  }

}

void thirdTask_switchLight() {
  unsigned long currentTime = millis();
  if (currentTime - thirdTask_lastSwitch > 800) {
    turnOffBlinkers();
    thirdTask_blinkIdx += 1;
    thirdTask_lastSwitch = millis();
    if (thirdTask_blinkIdx > 5 || thirdTask_blinkIdx > thirdTask_successCount) {
      thirdTask_blinkIdx = -2;
    }
    else if (thirdTask_blinkIdx >= 0) {
      int blinkerPins[3] = {bluLed,whtLed,ylwLed};
      int nextLightPinIndex = thirdTask_blinkOrder[thirdTask_blinkIdx];
      int nextLightPin = blinkerPins[nextLightPinIndex];
      digitalWrite(nextLightPin,HIGH);
    }
  }
}

void thirdTask_setRGB(int successes) {
  if (successes == 0) {
    setRGBColor(255,0,0);
  }
  if (successes == 1) {
    setRGBColor(255,255,255);
  }
  if (successes == 2) {
    setRGBColor(0,255,255);
  }
}
 
void thirdTask() {
  thirdTask_switchLight();

  int buttonPressed = -1;
  bool successFlag = false;

  if (digitalRead(btn1) == LOW) {
    buttonPressed = 0;
  }
  else if (digitalRead(btn2) == LOW) {
    buttonPressed = 1;
  }
  else if (digitalRead(btn3) == LOW) {
    buttonPressed = 2;
  }

  if (buttonPressed > -1 && !thirdTask_buttonBuffer) {
    thirdTask_buttonBuffer = true;
    if (thirdTask_successCount == 0 && buttonPressed == thirdTask_correctAnswers1) {
      thirdTask_buttonPressNumber += 1;
    }
    else if (thirdTask_successCount == 1 && buttonPressed == thirdTask_correctAnswers2[thirdTask_buttonPressNumber]) {
      thirdTask_buttonPressNumber += 1;
    }
    else if (thirdTask_successCount == 2 && buttonPressed == thirdTask_correctAnswers3[thirdTask_buttonPressNumber]) {
      thirdTask_buttonPressNumber += 1;
    }
    else {
      playErrorSound();
      thirdTask_successCount = 0;
      thirdTask_buttonPressNumber = 0;
    }
    if (thirdTask_buttonPressNumber > thirdTask_successCount) {
      thirdTask_blinkIdx = -1;
      thirdTask_successCount += 1;
      thirdTask_buttonPressNumber = 0;
      successFlag = true;
    }
  }
  else if (buttonPressed == -1) {
    thirdTask_buttonBuffer = false;
  }

  if (thirdTask_successCount >=3) {
    thirdTaskDone = true;
    turnOffBlinkers();
    playTripleSuccessSound();
  }
  else if (successFlag) {
    playSuccessSound();
  }

}

void loop() {

  int currentTask = getCurrentTask();

  if (currentTask == 1) {firstTask();}
  if (currentTask == 2) {secondTask();}
  if (currentTask == 3) {thirdTask();}
  if (currentTask == 4) {setRGBColor(0,255,0);}

  checkBuzzer();

}
