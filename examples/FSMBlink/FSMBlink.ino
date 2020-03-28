/*
@file FSMBlink.ino
@version 2.0
@author Alex Palmese
@contact alex.palmese@gmail.com
@description
"BLINK" FINITE STATE MACHINE SAMPLE
This basic Finite State Machine will simply flash the 
builtin LED for a fixed time.

It has only two states: 
* START turns the LED on and pauses for the amount of time 
contained in the parameter, then switches to LED state
* LED turns the LED off and pauses for the amount of time 
contained in the parameter, then switches back to START 
*/
#include <FiniteState.h>

// ***********************************************
// FINITE STATE MACHINE
// ***********************************************
FiniteState fsm;
// States
#define S_START 1
#define S_LED 2
#define S_PAUSE 3
// Conditions
#define C_TIMER 0
// Actions
#define A_LED_OFF 0
#define A_LED_ON 1

// ***********************************************
// SYMBOLS
// ***********************************************
#define LED 13

// ***********************************************
// GLOBALS
// ***********************************************
long millis0;
bool btnPressed = false;
int prevState = 0;

// ***********************************************
void setup() {
  Serial.begin(115200);

  pinMode(LED, OUTPUT);

  // State definitions
  fsm.Write(S_START, C_TIMER, A_LED_ON, 1000, S_LED);
  fsm.Write(S_LED, C_TIMER, A_LED_OFF, 1000, S_START);

  // Set the callback functions
  fsm.SetFunctions(&TestCondition, &DoAction);

  // Set the machine to first state
  fsm.Set(S_START);
}

// ***********************************************
void loop() {
  // State execution
  fsm.Execute();
}

boolean TestCondition(int condition) {
  switch ( condition ) {
  case C_TIMER: // Check if timer ends
    if ( millis() - millis0 > fsm.Param() ) {
      // End of time, reset start time
      millis0 = millis();
      return true;
    }
    return false;
  case C_ELSE:
    return true;
  }
  return false;
}

void DoAction(int action) {
  switch ( action ) {
  case A_LED_OFF:
    digitalWrite(LED, LOW);
    break;
  case A_LED_ON:
    digitalWrite(LED, HIGH);
    break;
  }
  return;
}
