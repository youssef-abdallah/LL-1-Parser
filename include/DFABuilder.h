#ifndef DFABUILDER_H
#define DFABUILDER_H
#include "NFAState.h"
#include "StateMachine.h"
#include "includes.h"
#include "DFAState.h"


class DFABuilder
{
    public:
        DFABuilder(StateMachine &machine): machineNFA(machine) {

        }
        virtual ~DFABuilder();
        void buildDFA();
        DFAState& getInitialState() {
            return initialState;
        }

        vector<DFAState> GetAllState(){
            return vector<DFAState>(this->AllState.begin(), this->AllState.end());
        }
        unordered_map<int, vector<int>> getReducedTable() {
            return this->reducedTable;
        }

        vector<char> GetInputs(){
            return {inputsSet.begin(), inputsSet.end()};
        }

    private:
        map<set<int>, vector<reference_wrapper<DFAState>>> stateMapping;
        vector<reference_wrapper<DFAState>> AllState;
        set<set<int>> marked;
        void calculateEpsilonClosure();
        void calculateEpsilonClosure(NFAState &state);
        void initialize();
        void computeNewTable();
        void checkIfAcceptState(DFAState &state);
        StateMachine &machineNFA;
        DFAState initialState;
        set<char> inputsSet;
        DFAState& mov(DFAState &T, char symbol);
        unordered_map<int, vector<int>> reducedTable;

};

#endif // DFABUILDER_H
