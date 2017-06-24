/*
@file FiniteState.cpp
@version 1.1
@author Alex Palmese
@contact alex.palmese@gmail.com
@description
| Finite state machine implementation (for robot programming)
@license
| This library is free software; you can redistribute it and/or
| modify it under the terms of the GNU Lesser General Public
| License as published by the Free Software Foundation.
| This library is distributed WITHOUT ANY WARRANTY; without even
| the implied warranty of MERCHANTABILITY or FITNESS FOR A
| PARTICULAR PURPOSE.  See the GNU Lesser General Public License
| for more details.
*/
#include "Arduino.h"
#include "FiniteState.h"

// ------------------------------------------------
// INIT
// ------------------------------------------------
int Max;
int id;    // Current condition
int State; // Current state

// ------------------------------------------------
// METHODS
// ------------------------------------------------
FiniteState::FiniteState() {
  Reset();
}

void FiniteState::Reset() {
  id = -1;
  // Create first "null" record
  Write(HALT,ELSE,NONE,0,HALT);
  id = -1;
  Max = -1;
  // Set current state to HALT
  Set(HALT);
}  
void FiniteState::Write(int idState, int idCond, int idAction, int idParam, int idNext) {
    ++id;
    _CurState[id] = idState;
    _Condition[id] = idCond;
    _Action[id] = idAction;
    _Param[id] = idParam;
    _NextState[id] = idNext;
    if (id > Max) Max = id;
}

// Search next current state condition. 
// Returns BREAK if no more conditions are found
int FiniteState::Next() {
  for (int i=++id; i<=Max; ++i)
    if ( _CurState[i] == State ) {
      id = i;
      return _Condition[i];
    }
  id = -1;
  return BREAK;
}

// Sets current state
void FiniteState::Set(int newState) {
  State = HALT;
  for(id=0; id<=Max; ++id)
    if ( _CurState[id] == newState ) {
      State = newState;
    }
  id = -1;
}

// Sets next state
void FiniteState::SetNext() {
  Set(NextState());
}

// Returns current state condition
int FiniteState::Condition() {
  if ( id > -1 )
      return _Condition[id];
  else
      return BREAK;
}

// Returns current state action
int FiniteState::Action() {
  if ( id > -1 )
      return _Action[id];
  else
      return NONE;
}

// Returns current state interger parameter
int FiniteState::Param() {
  if ( id > -1 )
      return _Param[id];
  else
      return 0;
}

// Returns the next state for current condition
int FiniteState::NextState() {
  if ( id > -1 )
      return _NextState[id];
  else
      return HALT;
}
