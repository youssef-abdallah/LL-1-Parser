#ifndef STATEMACHINE_H
#define STATEMACHINE_H
#include "includes.h"
#include "NFAState.h"



class StateMachine
{
    public:
        StateMachine();
        StateMachine(NFAState &_initialState, NFAState &_finalState):initialState(_initialState), finalState(_finalState) {

        }
        virtual ~StateMachine();
        NFAState& getInitialState() {
            return this->initialState;
        }
        NFAState& getFinalState() {
            return this->finalState;
        }
        void setInitialState(NFAState &state) {
            this->initialState = state;
        }
        void setFinalState(NFAState &state) {
            this->finalState = state;
        }
    private:
        NFAState& initialState;
        NFAState& finalState;
};

#endif
