#ifndef READFILE_H_INCLUDED
#define READFILE_H_INCLUDED

#include "includes.h"
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include "Terminal.h"
#include "NonTerminal.h"
#include "Token.h"
#include "Grammar.h"
#include "unordered_map"
#include <bits/stdc++.h>
#include "FactorNode.h"

bool CompareSize(FactorNode n1, FactorNode n2);

class ReadFile
{
private:
    vector<vector<std::string>> GrammarFile;
    vector<vector<std::string>> LLGrammarFile;
    Grammar grammar;
    unordered_map<std::string, shared_ptr<Token>> Tokens;
    unordered_map<std::string, shared_ptr<NonTerminal>> Non_Terminals;
    unordered_map<int, bool> Used_Production;
    shared_ptr<NonTerminal> First_State;
    vector<shared_ptr<Token>> Terminals;
    vector<shared_ptr<NonTerminal>> NonTerminals;
    set<shared_ptr<Token>> set_terminals;
    vector<FactorNode> nodes;
    vector<std::string> ExractStrings(std::string str);
    bool NewProduction(std::string first_element);
    void AddProductions();
    void EliminateLeftFactoring();
	vector<vector<std::string>> SplitProduction(vector<std::string> Production);
	vector<std::string> GetCommon(vector<std::string> v1, vector<std::string> v2);
	void InsertNode(int ProductionNum1 , int ProductionNum2, vector<std::string> Common);
	void AddLeftFactoring(vector<vector<FactorNode>> Elemination, vector<vector<std::string>> Productions, std::string NonTerminal);
	vector<std::string> SubVector(int Size, int Limit, vector<std::string> test);
public:
	ReadFile();
	~ReadFile();
	Grammar GetGrammar();
    shared_ptr<NonTerminal> GetFirstState();
	vector<shared_ptr<Token>> GetTerminals();
	vector<shared_ptr<NonTerminal>> GetNonTerminals();
	void eliminateLeftRecursion();
	void eliminateImmediateLeftRecursion(unsigned int);
};
#endif // READFILE_H_INCLUDED
