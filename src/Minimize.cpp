#include<Minimize.h>

Minimize::Minimize(DFAState initialState, vector<DFAState> States, vector<char> Inputs, unordered_map<int, vector<int>> Transitions)
{
    this->InitialID = initialState.getStateId();
	this->States = States;
	this->Inputs = Inputs;
	this->Transitions = Transitions;
	this->Stop = false;
	ExtractTokens();
	Separate();

	while (!Stop) {
		Stop = true;
		Difference();
		UpdateColor();
	}

    RemoveDeadState();
}


void Minimize::Separate()
{
    int Color = 1;
    unordered_map<string, int> SetColor;
    for (int i = 0; i < (int) States.size(); i++){
        DFAState Temp = States[i];
        if (Temp.isAcceptState()){
            auto check = SetColor.find(Temp.getAcceptStateToken());
            if(check == SetColor.end()){
                SetColor.emplace(Temp.getAcceptStateToken(), Color);
                Nodes.push_back(Node(States[i].getStateId(), Color));
                StateColor.emplace(States[i].getStateId(), Color);
                Color++;
            } else {
                Nodes.push_back(Node(States[i].getStateId(), check->second));
                StateColor.emplace(States[i].getStateId(), check->second);
            }
        } else {
            Nodes.push_back(Node(States[i].getStateId(), 0));
			StateColor.emplace(States[i].getStateId(), 0);
        }
    }
    StateColor.emplace(-1, 0);
}

void Minimize::Difference()
{
	for (int i = 0; i < (int) Nodes.size(); i++) {
        vector<int> Temp = (Transitions.find(((Node)(Nodes[i])).GetStateName()))->second;
		for (int j = 0; j < (int) Temp.size(); j++) {
			Nodes[i].AppendString((StateColor.find(Temp[j]))->second);
		}
	}
	StateColor.clear();
	StateColor.emplace(-1, 0);
}

void Minimize::UpdateColor()
{
	bool Case_2 = true;
	int Color = 0, preColor;
	for (int i = 0; i < (int) Nodes.size(); i++) {
		preColor = Nodes[i].GetColor();
		auto temp = ColorUpdate.find(Nodes[i].GetString());
		if (!(temp == ColorUpdate.end())) {
			if (Nodes[i].GetColor() == (temp->second).GetPreColor()) {
				Case_2 = false;
				if (Nodes[i].GetColor() != (temp->second).GetCurColor()) {
					Stop = false;
				}
				Nodes[i].SetColor((temp->second).GetCurColor());
				StateColor.emplace(Nodes[i].GetStateName(), (temp->second).GetCurColor());
			}
		}
		if (Case_2){
			if (Nodes[i].GetColor() != Color) {
				Stop = false;
			}
			Nodes[i].SetColor(Color);
			ColorUpdate.emplace(Nodes[i].GetString(), ColorNode(preColor, Color));
			StateColor.emplace(Nodes[i].GetStateName(), Color);
			Color++;
		}
		Case_2 = true;
	}
	Color = 0;
	ColorUpdate.clear();
	ClearDifferStrings();
}

void Minimize::ClearDifferStrings()
{
	for (int i = 0; i < (int) Nodes.size(); i++) {
		Nodes[i].ClearString();
	}
}

void Minimize::RemoveDeadState()
{
    unordered_map<int, int> Res;
    unordered_map<int, int> ChangeState;
    for (int i = 0; i < (int) Nodes.size(); i++){
        auto temp = Res.find(Nodes[i].GetColor());
        if (temp == Res.end()){
            Res.emplace(Nodes[i].GetColor(), Nodes[i].GetStateName());
        } else {
            ChangeState.emplace(Nodes[i].GetStateName(), temp->second);
        }
    }
    for (int i = 0; i < (int) Nodes.size(); i++){
        vector<int> Temp = (Transitions.find(((Node)(Nodes[i])).GetStateName()))->second;
        for (int j = 0; j < (int) Temp.size(); j++){
            auto temp = ChangeState.find(Temp[j]);
            if (!(temp == ChangeState.end())){
                ((Transitions.find(((Node)(Nodes[i])).GetStateName()))->second)[j] = temp->second;
            }
        }
    }
    for (int i = 0; i < (int) Nodes.size(); i++){
        auto temp = ChangeState.find(Nodes[i].GetStateName());
        if (temp == ChangeState.end()){
            TransitionsMinimize.emplace(Nodes[i].GetStateName(), (Transitions.find(Nodes[i].GetStateName()))->second);
        }
    }
    /*auto it = ChangeState.find(InitialID);
    if (it != ChangeState.end()){
        InitialID = it->second;
    }*/
}

void Minimize::ExtractTokens(){
    for(int i = 0; i < (int) States.size(); i++){
        if(States[i].isAcceptState()){
            Tokens.emplace(States[i].getStateId(), States[i].getAcceptStateToken());
        }
    }
}

unordered_map<int, vector<int>> Minimize::GetTransitions(){
    return this->TransitionsMinimize;
}

unordered_map<int, string> Minimize::GetTokens(){
    return this->Tokens;
}

vector<char> Minimize::GetInputVector(){
    return this->Inputs;
}

int Minimize::GetInitialID(){
    return this->InitialID;
}

Minimize::~Minimize()
{
	//dtor
}
