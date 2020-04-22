#include "NFASimulator.h"

NFASimulator::NFASimulator()
{
    //ctor
}

NFASimulator::~NFASimulator()
{
    //dtor
}

string NFASimulator::simulate(StateMachine &stateMachine, string inputString) {
    set<NFAState> currentStates;
    for (auto &elem : stateMachine.getInitialState().getEpsilonClosure()) {
        currentStates.insert(elem);
    }
    for (char &symbol : inputString) {
        set<NFAState> newStates;
        for (NFAState currentState : currentStates) {
            if (currentState.getTransitions().count(symbol)) {
                vector<reference_wrapper<NFAState>> possibleTransitions = currentState.getTransitions()[symbol];
                for (NFAState &state : possibleTransitions) {
                    for (auto &elem : state.getEpsilonClosure()) {
                        newStates.insert(elem);
                    }
                }
            }
        }
        currentStates = newStates;
    }
    for (NFAState currentState : currentStates) {
        if (currentState.isAcceptState()) {
            return currentState.getAcceptStateToken();
        }
    }
    return "REJECT";
}
