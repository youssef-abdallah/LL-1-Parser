#pragma once
#include "includes.h"
#include "NFAState.h"
#include "StateMachine.h"


class NFABuilder {

public:
    static NFABuilder& getInstance();

    NFABuilder(NFABuilder const&) = delete;
    void operator=(NFABuilder const&) = delete;
    static StateMachine& buildNFAFromPostfix(string, string);

private:
    NFABuilder();
    static StateMachine& stateMachineOfSymbol(char);
    static StateMachine& concatenateTwoMachines(StateMachine &fsm1, StateMachine &fsm2);
    static StateMachine& unifyTwoMachines(StateMachine &fsm1, StateMachine &fsm2);
    static StateMachine& getTheMachineClosure(StateMachine &fsm);
};
