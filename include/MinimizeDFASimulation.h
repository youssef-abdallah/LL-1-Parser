#ifndef MINIMIZEDFASIMULATION_H_INCLUDED
#define MINIMIZEDFASIMULATION_H_INCLUDED

#include<Minimize.h>

class MinimizeDFASimulation
{
private:
    int CurrentStateID;
	int initialStateID;
	int nextStateID;
	unordered_map<int, vector<int>> Transitions;
	unordered_map<int, string> Tokens;
	vector<char> Input;
public:
    string simulate(string InputString);
	MinimizeDFASimulation(Minimize minimize);
	void Reset();
	string GEtTokenForInput(string InputString);
	~MinimizeDFASimulation();

};

#endif // MINIMIZEDFASIMULATION_H_INCLUDED
