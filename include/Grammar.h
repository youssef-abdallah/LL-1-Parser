#ifndef GRAMMAR_H
#define GRAMMAR_H
#include "includes.h"
#include "NonTerminal.h"
#include "Token.h"

class Grammar
{
    public:
        Grammar();
        virtual ~Grammar();
        void addProduction(shared_ptr<NonTerminal> &nonTerminal, vector<shared_ptr<Token>> &rightHandSide) {
            productions.insert({nonTerminal, rightHandSide});
        }
        void setStartingSymbol(shared_ptr<NonTerminal> _startingSymbol) {
            this->startingSymbol = _startingSymbol;
        }
        shared_ptr<NonTerminal> getStartingSymbol(){
            return this->startingSymbol;
        }
        map<shared_ptr<Token>, set<string>> getFirst() {
            return this->first;
        }
        map<shared_ptr<Token>, set<string>> getFollow() {
            return this->follow;
        }
        void computeFirst();
        void computeFollow();
        multimap<shared_ptr<Token>, vector<shared_ptr<Token>>> getProductions();

    protected:

    private:
        multimap<shared_ptr<Token>, vector<shared_ptr<Token>>> productions;
        map<shared_ptr<Token>, set<string>> follow;
        map<shared_ptr<Token>, set<string>> first;
        set<shared_ptr<Token>> epsilonTokens;
        shared_ptr<NonTerminal> startingSymbol;

        bool unify(shared_ptr<Token>, shared_ptr<Token>);
        bool updateFollow(shared_ptr<Token> token, set<string> followSoFar);
};

#endif // GRAMMAR_H
