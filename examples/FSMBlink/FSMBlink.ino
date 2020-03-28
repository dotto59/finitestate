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

Full Finite Machine State is defined in setup():

  fsm.Write(S_START, C_TIMER, A_LED_ON, 1000, S_LED);
  fsm.Write(S_LED, ELSE, A_LED_OFF, 1000, S_START);

Write has 5 parameters:
1) Current state code
2) Condition required to change state
3) Action required if Condition is met
4) Optional integer parameter (if not used, simply put a zero)
5) Next state at the end of action

*/

#include <FiniteState.h>
// ***********************************************
// FINITE STATE MACHINE
// ***********************************************
FiniteState fsm;
// State
#define S_START 1
#define S_LED 2
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

// ***********************************************
void setup() {
  Serial.begin(115200);
  delay(500);

  // State definitions
  fsm.Write(S_START, C_TIMER, A_LED_ON, 1000, S_LED);
  fsm.Write(S_LED, ELSE, A_LED_OFF, 1000, S_START);

  // Set the machine to first state
  fsm.Set(S_START);
  Serial.print("First state=");
  Serial.println(fsm.State);

  pinMode(LED, OUTPUT);
  millis0 = millis();
}

// ***********************************************
void loop() {
  // State execution cycle
  while ( fsm.State != HALT && fsm.Next() != BREAK ) {
    // Check if a condition is met
    if ( TestCondition() ) {
      // Execute required action
      DoAction();
      // Step to next state
      fsm.SetNext();
      Serial.print("STATE: ");
      Serial.println(fsm.State);
      // Exit while
      break;
    }
  }
}

boolean TestCondition() {
  switch ( fsm.Condition() ) {
    case C_TIMER: // Check if timer ends
      if ( millis() > millis0 + fsm.Param() ) {
        // End of time, reset start time
        millis0 = 0;
        return true;
      }
      return false;

    case ELSE:
      return true;

  }
  return false;
}

void DoAction() {
  switch ( fsm.Action() ) {
    case A_LED_OFF:
      digitalWrite(LED, LOW);
      delay(fsm.Param());
      return;

    case A_LED_ON:
      digitalWrite(LED, HIGH);
      delay(fsm.Param());
      return;
  }
  return;
}
