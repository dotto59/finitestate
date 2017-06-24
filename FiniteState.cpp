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
// INIZIALIZZAZIONI
// ------------------------------------------------
// Stato nullo (iniziale)
const int HALT = -1;    
// Condizione sempre verificata (ELSE)
const int ELSE = -1;    
// Condizione nulla restituita da Next per indicare fine condizioni
const int BREAK = -2;
// Nessuna azione
const int NONE = -1;

int Max;
int id;         // Condizione corrente
int State;    // Stato corrente

// ------------------------------------------------
// METODI
// ------------------------------------------------
FiniteState::FiniteState() {
  Reset();
}

void FiniteState::Reset() {
  id = -1;
  // Crea il primo record "nullo"
  Write(HALT,ELSE,NONE,0,HALT);
  id = -1;
  Max = -1;
  // Si posiziona nello stato "nullo"
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

// Cerca la prossima condizione nell'array per
// lo stato corrente. Restituisce BREAK se non ci sono
// altre condizioni da verificare
int FiniteState::Next() {
  for (int i=++id; i<=Max; ++i)
    if ( _CurState[i] == State ) {
      id = i;
      return _Condition[i];
    }
  id = -1;
  return BREAK;
}

// Imposta il prossimo stato
void FiniteState::Set(int newState) {
  State = HALT;
  for(id=0; id<=Max; ++id)
    if ( _CurState[id] == newState ) {
      State = newState;
    }
  id = -1;
}

// Imposta il prossimo stato indicato dall'attuale NextState
void FiniteState::SetNext() {
  Set(NextState());
}

int FiniteState::Condition() {
  if ( id > -1 )
      return _Condition[id];
  else
      return BREAK;
}
int FiniteState::Action() {
  if ( id > -1 )
      return _Action[id];
  else
      return NONE;
}
int FiniteState::Param() {
  if ( id > -1 )
      return _Param[id];
  else
      return 0;
}
int FiniteState::NextState() {
  if ( id > -1 )
      return _NextState[id];
  else
      return HALT;
}

