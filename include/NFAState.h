#ifndef NFASTATE_H
#define NFASTATE_H
#include "includes.h"

struct NFAState {

public:
    NFAState() {
        this->acceptState = 0;
        this->stateId = stateCounter++;
    }
    NFAState(bool acceptState) {
        this->acceptState = acceptState;
        this->stateId = stateCounter++;
    }
    ~NFAState();
    void setAcceptState(bool acceptState) {
        this->acceptState = acceptState;
    }

    bool isAcceptState() const {
        return this->acceptState;
    }

    void addTransition(char symbol, NFAState &state) {
        if (symbol == 0) {
            this->getEpsilonTransitions().push_back(state);
        } else {
            this->getTransitions()[symbol].push_back(state);
        }
    }

    vector<reference_wrapper<NFAState>> &getEpsilonTransitions() {
        return this->epsilonTransitions;
    }

    unordered_map<char, vector<reference_wrapper<NFAState>>> &getTransitions() {
        return this->transitions;
    }

    static int getStateCounter() {
        return NFAState::stateCounter;
    }

    int getStateId() const {
        return this->stateId;
    }

    void setAcceptStateToken(string token) {
        this->acceptStateToken = token;
    }

    string getAcceptStateToken() const {
        return this->acceptStateToken;
    }

    void setEpsilonClosure(vector<reference_wrapper<NFAState>> eClosure){
        this->epsilonClosure = eClosure;
    }
    vector<reference_wrapper<NFAState>> & getEpsilonClosure() {
        return this->epsilonClosure;
    }

    bool operator < (NFAState const &obj) const {
         return stateId < obj.getStateId();
    }

private:
    static int stateCounter;
    int stateId;
    bool acceptState;
    unordered_map<char, vector<reference_wrapper<NFAState>>> transitions;
    vector<reference_wrapper<NFAState>> epsilonTransitions;
    vector<reference_wrapper<NFAState>> epsilonClosure;
    string acceptStateToken;

};

#endif
