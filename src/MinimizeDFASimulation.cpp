#include <MinimizeDFASimulation.h>

MinimizeDFASimulation::MinimizeDFASimulation(Minimize minimize){
    this->initialStateID = minimize.GetInitialID();
    this->Transitions = minimize.GetTransitions();
    this->Tokens = minimize.GetTokens();
    this->Input = minimize.GetInputVector();
    CurrentStateID = initialStateID;
}
void MinimizeDFASimulation::Reset(){
    CurrentStateID = initialStateID;
}

string MinimizeDFASimulation::GEtTokenForInput(string InputString){
    string LastToken;
    bool LastChar = false;
    for (char Symbol : InputString) {
        LastChar = false;
        auto it = std::find(Input.begin(), Input.end(), Symbol);
        int Pos = it - Input.begin();
        auto iter = Transitions.find(CurrentStateID);
        if (iter != Transitions.end()){
            vector<int> Temp = iter->second;
            CurrentStateID = Temp[Pos];
            auto t = Tokens.find(CurrentStateID);
            if (t != Tokens.end()){
                LastToken = t->second;
                LastChar = true;
            }
        }else {
            return "Non Valid input";
        }

    }
    if (!LastToken.empty()){
        if (LastChar){
            return LastToken;
        } else {
            return "Expected : " + LastToken;
        }
    } else{
        return "There is not Any Accept State";
    }
}

string MinimizeDFASimulation::simulate(string InputString) {
    string LastToken;
    int LastChar = -1;
    for (int i = 0; i < (int) InputString.size(); i++) {
        char Symbol = InputString[i];
        auto it = std::find(Input.begin(), Input.end(), Symbol);
        int Pos = it - Input.begin();
        auto iter = Transitions.find(CurrentStateID);
        if (iter != Transitions.end()){
            vector<int> Temp = iter->second;
            CurrentStateID = Temp[Pos];
            auto t = Tokens.find(CurrentStateID);
            if (t != Tokens.end()){
                LastToken = t->second;
                LastChar = i;
            }
        } else {
            return "Non Valid input";
        }

    }
    if (!LastToken.empty()){
        if (LastChar != -1){
            if (LastChar == (int) InputString.length() - 1) return LastToken;
            CurrentStateID = initialStateID;
            return LastToken + '\n' + simulate(InputString.substr(LastChar + 1));
        } else {
            return "Expected : " + LastToken;
        }
    } else{
        return "There is not Any Accept State";
    }
}

MinimizeDFASimulation::~MinimizeDFASimulation(){
}
