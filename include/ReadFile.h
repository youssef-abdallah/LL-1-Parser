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

class ReadFile
{
private:
    vector<vector<std::string>> GrammarFile;
    Grammar grammar;
    unordered_map<std::string, shared_ptr<Token>> Tokens;
    unordered_map<std::string, shared_ptr<NonTerminal>> Non_Terminals;
    vector<std::string> ExractStrings(std::string str);
    shared_ptr<NonTerminal> First_State;
    bool NewProduction(std::string first_element);
    void AddProductions();
public:
	ReadFile();
	~ReadFile();
	Grammar GetGrammar();
	shared_ptr<NonTerminal> GetFirstState();
};
#endif // READFILE_H_INCLUDED
