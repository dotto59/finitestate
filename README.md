# FiniteState
FiniteState machine for Arduino
## Definition
This library enables you to implement Finite State Machines (FSM) on Arduino boards.
## Installation
1) Navigate to the Releases page.
2) Download the latest release.
3) Extract the zip file
4) Move the "finitestate-master" folder that has been extracted to your libraries directory
5) Rename the folder to "FiniteState"
## Usage
You need to draw your **state diagram** first, using circles for the possible states, and arcs representing the "transitions". Each transition is a combination of three items: a "**condition**" (any event or test result) an "**action**" (what to do when the event happens) and the "**next state**" (the new state after the action is done). One of the states will be the "starting" state.
Then, you need just a few coding. First of all, you must define all the symbols for States, Conditions, and Actions. It is suggested you start State names with "S_", Conditions with "C_" and Actions with "A_" and assign then some integer values.
For example, let's assume you want to create a simple machine with just two states to blink a LED, like in FSMBlink example project. The starting state is called START, then the condition will be a timer fired (e.g. 1 second) and the actions are turn the LED on or off:
```
// State
#define S_START 1
#define S_LED 2
// Conditions
#define C_TIMER 0
// Actions
#define A_LED_OFF 0
#define A_LED_ON 1
```
After creating a global variable for the finite state machine, "``FiniteState fsm;``", our machine will be easily defined on setup() function as follows, together with the "initial state" definition:
```
  // State definitions
  fsm.Write(S_START, C_TIMER, A_LED_ON, 1000, S_LED);
  fsm.Write(S_LED, ELSE, A_LED_OFF, 1000, S_START);
  // Set the machine to first state
  fsm.Set(S_START);
```
With the first statement we define a transition from START state to LED state, based on a TIMER of 1000 ms. Obviouslt, the second represents the opposite transition, from state LED back to START after another second. The last statement sets the starting state to START.
After this initialization, you need to create two functions: one to check the conditions or "TestConditions()", and one to perform the required actions, or "DoActions". The first should return a boolean value representing the test result: true if the condition is met and the action will be performed, false if not.
In our example, the code will be as follows:
```
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
```
Finally, you loop() cycle will be pretty simple and identical for almost any project using FSM:
```
void loop() {
  // State execution cycle
  if ( TestCondition() ) {
    // Execute required action
    DoAction();
    // Step to next state
    fsm.SetNext();
    Serial.print("STATE: ");
    Serial.println(fsm.State);
  }
}
```
The first if() checks the conditions 

## Contributing
If you want to contribute to this project:
* Report bugs and errors
* Ask for enhancements
* Create issues and pull requests
* Tell other people about this library
## Copyright
(c) 2020 Alex Palmese
## License
This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation.
This library is distributed WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details. 
