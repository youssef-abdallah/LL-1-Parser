#include "DFAState.h"

DFAState::DFAState()
{
    this->stateId = stateCounter++;
}

DFAState::~DFAState()
{
    //dtor
}

int DFAState::stateCounter;
