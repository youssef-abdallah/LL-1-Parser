#include "../include/LexicalAnalyzer.h"

LexicalAnalyzer::LexicalAnalyzer() {

}

LexicalAnalyzer& LexicalAnalyzer::getInstance() {
    static LexicalAnalyzer instance;
    return instance;
}

vector<std::string> LexicalAnalyzer::execute() {
    vector<std::string> Result;
    Scanner::getInstance().read_lexical_rules("./test/lexical_rules.txt");
    vector<RegularExpression> regularExpressions = Scanner::getInstance().reg_expressions;
    vector<StateMachine> stateMachines;
    for (RegularExpression regularExpression : regularExpressions) {
        stateMachines.push_back(NFABuilder::buildNFAFromPostfix(regularExpression.getPostfixExpression(),
                                                                 regularExpression.getExpressionType()));
    }
    NFAState initialState(0), finalState(0);
    for (StateMachine &stateMachine: stateMachines) {
        initialState.addTransition(0, stateMachine.getInitialState());
    }
    StateMachine &combinedStateMachine = *new StateMachine(initialState, finalState);
    DFABuilder builder(combinedStateMachine);
    builder.buildDFA();
    Minimize minimize(builder.getInitialState(),builder.GetAllState(),builder.GetInputs(),builder.getReducedTable());
    NFASimulator simulator;
    vector<string> results = Scanner::getInstance().process_input_program("./input_program.txt");
    /*cout << simulator.simulate(combinedStateMachine, "123") << '\n';
    DFASimulator dfaSimulator;
    cout << dfaSimulator.simulate(builder.getInitialState(), "123") << '\n';
    MinimizeDFASimulation minsimulator(minimize);
    cout << minsimulator.GEtTokenForInput("123") << '\n';
    minsimulator.Reset();
    cout << minsimulator.GEtTokenForInput("F5nj7") << '\n';
    minsimulator.Reset();
    cout << minsimulator.GEtTokenForInput("==") << '\n';
    minsimulator.Reset();
    cout << minsimulator.GEtTokenForInput("+") << '\n';
    minsimulator.Reset();
    cout << minsimulator.GEtTokenForInput("*") << '\n';
    minsimulator.Reset();
    cout << minsimulator.GEtTokenForInput("int") << '\n';
    minsimulator.Reset();
    cout << minsimulator.GEtTokenForInput("\(") << '\n';*/

    MinimizeDFASimulation minsimulator(minimize);
    for (int i = 0; i < (int) results.size(); i++){
        std::string str = minsimulator.simulate(results[i]);
        std::regex Split_Space("\\s+");
        std::vector<std::string> result{std::sregex_token_iterator(str.begin(), str.end(), Split_Space, -1), {}};
        for (unsigned j = 0; j < result.size(); j++){
            cout << "result : "<<  result[j] << '\n';
            Result.push_back(result[j]);
        }


        minsimulator.Reset();
    }
    return Result;
}
