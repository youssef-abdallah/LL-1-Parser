#include "DFASimulator.h"

DFASimulator::DFASimulator()
{
    //ctor
}

DFASimulator::~DFASimulator()
{
    //dtor
}

string DFASimulator::simulate(DFAState& state, string inputString) {
    DFAState& currentState = state;
    for (char &symbol : inputString) {
        if (state.getTransitions()[symbol].size()) {
              currentState = state.getTransitions()[symbol][0];
        } else {
            return "REJECT";
        }
    }
    if (state.isAcceptState()) {
        return state.getAcceptStateToken();
    }
    return "REJECT";
}
