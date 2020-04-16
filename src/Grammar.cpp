#include "Grammar.h"

Grammar::Grammar()
{
    //ctor
}

Grammar::~Grammar()
{
    //dtor
}

void Grammar::computeFirst() {
    for (auto &production : productions) {
        shared_ptr<Token> nonTerminal = production.first;
        first[nonTerminal];
        vector<shared_ptr<Token>> rule = production.second;
        for (auto &token : rule) {
            if (productions.count(token) == 0) {
                first[token].insert(token->getType());
            }
        }
    }
    while (1) {
        bool changes = 0;
        for (auto &production : productions) {
            shared_ptr<Token> nonTerminal = production.first;
            vector<shared_ptr<Token>> rule = production.second;
            bool loop_broken = 0;
            for (shared_ptr<Token>& token : rule) {
                changes |= unify(nonTerminal, token);
                if (!epsilonTokens.count(token)) {
                    loop_broken = 1;
                    break;
                }
            }
            if (!loop_broken) {
                changes |= (epsilonTokens.count(nonTerminal) == 0);
                epsilonTokens.insert(nonTerminal);
                // 0 means EPSILON for now.
                first[nonTerminal].insert("0");
            }
        }
        if (!changes) break;
    }
}

bool Grammar::unify(shared_ptr<Token> token, shared_ptr<Token> second) {
    int original_size = first[token].size();
    first[token].insert(first[second].begin(), first[second].end());
    return original_size != (int) first[token].size();
}

void Grammar::computeFollow() {
    follow[startingSymbol].insert("$");
    while (1) {
        bool changes = 0;
        for (auto &production : productions) {
            shared_ptr<Token> nonTerminal = production.first;
            set<string> followSoFar = follow[nonTerminal];
            vector<shared_ptr<Token>> rule = production.second;
            for (auto it = rule.rbegin(); it != rule.rend(); it++) {
                if (productions.count(*it)) {
                    changes |= updateFollow(*it, followSoFar);
                }
                if (epsilonTokens.count(*it)) {
                    followSoFar.insert(first[*it].begin(), first[*it].end());
                    followSoFar.erase("0");
                } else {
                    followSoFar = first[*it];
                    followSoFar.erase("0");
                }
            }
        }
        if (!changes) break;
    }
}

bool Grammar::updateFollow(shared_ptr<Token> token, set<string> followSoFar) {
    int originalSize = follow[token].size();
    follow[token].insert(followSoFar.begin(), followSoFar.end());
    return originalSize != (int) follow[token].size();
}
