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

#define MAX 32    // Numero massimo di condizioni

class FiniteState {
public:
  const int HALT = -1; 
  const int ELSE = -1;
  const int NONE = -1; 
  const int BREAK = -9999;
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

