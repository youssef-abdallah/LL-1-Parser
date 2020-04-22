#ifndef DFASTATE_H
#define DFASTATE_H
#include "includes.h"
#include "NFAState.h"

class DFAState
{
    public:
        DFAState();
        DFAState(bool accept){
            this->stateId = stateCounter++;
            this->acceptState=accept;
        }
        virtual ~DFAState();
        void setAcceptState(bool acceptState){
            this->acceptState = acceptState;
        }
        bool isAcceptState() {
            return this->acceptState;
        }
        void setAcceptStateToken(string token){
            this->acceptStateToken=token;
        }
        string getAcceptStateToken(){
            return this->acceptStateToken;
        }
        void addState(NFAState &state) {
            if (!statesId.count(state.getStateId())) {
                statesId.insert(state.getStateId());
                this->getNFAStates().push_back(state);
            }
        }
        vector<reference_wrapper<NFAState>> &getNFAStates(){
            return this->states;
        }
        set<int> getStatesId(){
            return this->statesId;
        }

        int getStateId() const {
            return stateId;
        }

        unordered_map<char, vector<reference_wrapper<DFAState>>> &getTransitions() {
            return this->transitions;
        }

        void addTransition(char symbol, DFAState &state) {
            this->getTransitions()[symbol].push_back(state);
        }

        bool operator < (DFAState const &obj) const {
            return this->stateId < obj.getStateId();
        }

    private:
        bool acceptState;
        //int stateId;
        string acceptStateToken;
        vector<reference_wrapper<NFAState>> states;
        unordered_map<char, vector<reference_wrapper<DFAState>>> transitions;
        set<int> statesId;
        int stateId;
        static int stateCounter;

};

#endif // DFASTATE_H
