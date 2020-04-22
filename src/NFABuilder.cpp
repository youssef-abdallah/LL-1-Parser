#include "../include/NFABuilder.h"

NFABuilder::NFABuilder() {

}

NFABuilder& NFABuilder::getInstance() {
    static NFABuilder instance;
    return instance;
}

StateMachine& NFABuilder::buildNFAFromPostfix(string postfix, string regularExpression) {
    stack<reference_wrapper<StateMachine>> st;
    for (int i = 0; i < (int) postfix.length(); i++) {
        if (postfix[i] == '\\') {
            i++;
            st.push(stateMachineOfSymbol(postfix[i]));
        }
        else if (postfix[i] == '*') {
            StateMachine &fsm = st.top();
            st.pop();
            st.push(getTheMachineClosure(fsm));
        } else if (postfix[i] == '~') {
            StateMachine &fsm2 = st.top();
            st.pop();
            StateMachine &fsm1 = st.top();
            st.pop();
            st.push(concatenateTwoMachines(fsm1, fsm2));
        } else if (postfix[i] == '|') {
            StateMachine &fsm2 = st.top();
            st.pop();
            StateMachine &fsm1 = st.top();
            st.pop();
            st.push(unifyTwoMachines(fsm1, fsm2));
        } else {
            st.push(stateMachineOfSymbol(postfix[i]));
        }
    }
    st.top().get().getFinalState().setAcceptStateToken(regularExpression);
    return st.top();
}

StateMachine& NFABuilder::stateMachineOfSymbol(char symbol) {
    NFAState& initialState = *new NFAState(0);
    NFAState&  finalState = *new NFAState(1);
    initialState.addTransition(symbol, finalState);
    return *new StateMachine(initialState, finalState);
}

StateMachine& NFABuilder::concatenateTwoMachines(StateMachine &fsm1, StateMachine &fsm2) {
    fsm1.getFinalState().setAcceptState(0);
    fsm1.getFinalState().addTransition(0, fsm2.getInitialState());
    return *new StateMachine(fsm1.getInitialState(), fsm2.getFinalState());
}

StateMachine& NFABuilder::unifyTwoMachines(StateMachine &fsm1, StateMachine &fsm2) {
    NFAState& initialState = *new NFAState(0);
    initialState.addTransition(0, fsm1.getInitialState());
    initialState.addTransition(0, fsm2.getInitialState());
    NFAState& finalState = *new NFAState(1);
    fsm1.getFinalState().setAcceptState(0);
    fsm2.getFinalState().setAcceptState(0);
    fsm1.getFinalState().addTransition(0, finalState);
    fsm2.getFinalState().addTransition(0, finalState);
    return *new StateMachine(initialState, finalState);
}

StateMachine& NFABuilder::getTheMachineClosure(StateMachine &fsm) {
    NFAState& initialState = *new NFAState(0);
    NFAState& finalState = *new NFAState(1);
    initialState.addTransition(0, finalState);
    initialState.addTransition(0, fsm.getInitialState());
    fsm.getFinalState().setAcceptState(0);
    fsm.getFinalState().addTransition(0, fsm.getInitialState());
    fsm.getFinalState().addTransition(0, finalState);
    return *new StateMachine(initialState, finalState);
}
