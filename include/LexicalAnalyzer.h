#pragma once
#include "includes.h"
#include "NFAState.h"
#include "LexicalAnalyzer.h"
#include "RegularExpression.h"
#include "NFABuilder.h"
#include "Scanner.h"
#include "DFABuilder.h"
#include "NFASimulator.h"
#include "DFASimulator.h"
#include "Minimize.h"
#include "MinimizeDFASimulation.h"
#include <regex>


class LexicalAnalyzer {

public:
    static LexicalAnalyzer& getInstance();
    static vector<std::string> execute();

    LexicalAnalyzer(LexicalAnalyzer const&) = delete;
    void operator=(LexicalAnalyzer const&) = delete;

private:
    LexicalAnalyzer();
};
