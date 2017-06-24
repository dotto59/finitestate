/*
@file FiniteState.h
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
#ifndef FiniteState_h
#define FiniteState_h

#include "Arduino.h"

#define MAX 32    // Max conditions

// Null state (start), do nothing
#define HALT -1
// Default condition (ELSE)
#define ELSE -1
// Null condition returned from Next to signal end of conditions
#define BREAK -2
// No actions
#define NONE -1

class FiniteState {
public:
  int State;

  FiniteState();
  void Reset();
  void Write(int idState, int idCond, int idAction, int idParam, int idNext);
  int Next();
  void Set(int newState);
  void SetNext();
  
  int Write();
  int Action();
  int Param();
  int NextState();
  int Condition();
  
private:
  int _CurState[MAX];
  int _Condition[MAX];
  int _Action[MAX];
  int _Param[MAX];
  int _NextState[MAX];
  int id;    
  int Max;
};

#endif
