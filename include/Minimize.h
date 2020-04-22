#ifndef MINIMIZE_H_INCLUDED
#define MINIMIZE_H_INCLUDED

#include<includes.h>
#include<Node.h>
#include<ColorNode.h>
#include<algorithm>
#include<DFAState.h>

class Minimize
{
private:
    int InitialID;
	vector<DFAState> States;
	vector<char> Inputs;
	unordered_map<int, vector<int>> Transitions;
	unordered_map<int, vector<int>> TransitionsMinimize;
	unordered_map<int, string> Tokens;
	unordered_map<string, ColorNode> ColorUpdate;
	unordered_map<int, int> StateColor;
	vector<Node> Nodes;
	bool Stop;
	void Separate();
	void Difference();
	void UpdateColor();
	void ClearDifferStrings();
	void RemoveDeadState();
	void ExtractTokens();
public:
	Minimize(DFAState initialState, vector<DFAState> States, vector<char> Inputs, unordered_map<int, vector<int>> Transitions);
	unordered_map<int, vector<int>> GetTransitions();
	unordered_map<int, string> GetTokens();
	vector<char> GetInputVector();
	int GetInitialID();
	~Minimize();
};

#endif // MINIMIZE_H_INCLUDED
