#include "DFABuilder.h"


DFABuilder::~DFABuilder()
{
    //dtor
}

void DFABuilder::buildDFA(){
    calculateEpsilonClosure();
    initialize();
    computeNewTable();
}

void DFABuilder::calculateEpsilonClosure()
{
    NFAState &state = machineNFA.getInitialState();
    calculateEpsilonClosure(state);
    unordered_map<int, bool> calculated;
    calculated[state.getStateId()] = 1;
    stack<reference_wrapper<NFAState>> st;
    st.push(state);
    while (!st.empty())
    {
        NFAState& s = st.top();
        st.pop();
        for (NFAState &currentState : s.getEpsilonTransitions())
        {
            if (!calculated[currentState.getStateId()])
            {
                st.push(currentState);
                calculateEpsilonClosure(currentState);
                calculated[currentState.getStateId()] = 1;
            }
        }

        for ( auto &it : s.getTransitions() )
        {
            inputsSet.insert(it.first);
            for(NFAState &currentState : it.second)
            {
                if (!calculated[currentState.getStateId()])
                {
                    st.push(currentState);
                    calculateEpsilonClosure(currentState);
                    calculated[currentState.getStateId()] = 1;
                }
            }
        }
    }
}

void DFABuilder::calculateEpsilonClosure(NFAState &state)
{
    //vector<NFAState> stateClosure;
    stack<reference_wrapper<NFAState>> st;
    st.push(state);
    unordered_set<int> added;
    while (!st.empty())
    {
        NFAState &currentState = st.top();
        st.pop();
        added.insert(currentState.getStateId());
        state.getEpsilonClosure().push_back(currentState);
        for (NFAState &nextState : currentState.getEpsilonTransitions())
        {
            //cout << added.count(nextState.getStateId()) << endl;
            if (!added.count(nextState.getStateId()))
            {
                st.push(nextState);
            }
        }
    }
}

void DFABuilder::initialize() {
    NFAState &state = machineNFA.getInitialState();
    initialState = *new DFAState(0);
    set<int> initialId;
    for(NFAState &s : state.getEpsilonClosure()){
        initialState.addState(s);
        initialId.insert(s.getStateId());
    }
}

void DFABuilder::computeNewTable() {
    vector<reference_wrapper<DFAState>> Dstates;
    Dstates.push_back(initialState);
    for (int i = 0; i < (int) Dstates.size(); i++) {
        DFAState &T = Dstates[i];
        if (marked.count(T.getStatesId())) {
            Dstates.erase(Dstates.begin() + i);
            i--;
            continue;
        }
        marked.insert(T.getStatesId());
        for (set<char>::iterator c = inputsSet.begin(); c != inputsSet.end(); c++) {
            DFAState& U = mov(T, *c);
            T.addTransition(*c, U);
            reducedTable[T.getStateId()].resize(inputsSet.size(), -1);
            reducedTable[T.getStateId()][distance(inputsSet.begin(), c)] = U.getStateId();
            if (marked.count(U.getStatesId()) == 0) {
                    Dstates.push_back(U);
            }
        }
    }
    AllState = Dstates;
}


void DFABuilder::checkIfAcceptState(DFAState &state){
    int minId = INT_MAX;
    for(NFAState &s : state.getNFAStates()){
        if(s.isAcceptState()){
            if(s.getStateId()<minId){
                state.setAcceptState(1);
                state.setAcceptStateToken(s.getAcceptStateToken());
            }
        }
    }
}

DFAState& DFABuilder::mov(DFAState &T, char symbol) {
    set<int> statesIds;
    vector<reference_wrapper<NFAState>> composingStates;
    for (NFAState &nfaState : T.getNFAStates()) {
        vector<reference_wrapper<NFAState>> nextStates = nfaState.getTransitions()[symbol];
        for (NFAState &nextState : nextStates) {
            for (NFAState& epsilonState : nextState.getEpsilonClosure()) {
                composingStates.push_back(epsilonState);
                statesIds.insert(epsilonState.getStateId());
            }
        }
    }
    if (stateMapping.count(statesIds)) {
        return stateMapping[statesIds][0];
    }
    DFAState& newState = *new DFAState(0);
    for (NFAState &composingState : composingStates) {
        newState.addState(composingState);
    }
    checkIfAcceptState(newState);
    stateMapping[statesIds].push_back(newState);
    return newState;
}
