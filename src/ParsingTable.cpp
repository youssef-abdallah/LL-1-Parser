#include "ParsingTable.h"
#include "Grammar.h"
#include "NonTerminal.h"
#include "Terminal.h"
#include "Token.h"
ParsingTable::ParsingTable()
{
    //ctor
}

ParsingTable::~ParsingTable()
{
    //dtor
}

void ParsingTable::set_terminals(vector<shared_ptr<Token>> terminals){
    Terminals = terminals;
}
void ParsingTable::set_non_terminals(vector<shared_ptr<Token>> non_terminals){
    NonTerminals = non_terminals;
}

void ParsingTable::set_first(map<shared_ptr<Token>, set<string>> _first){
    first = _first;
}

void ParsingTable::set_follow(map<shared_ptr<Token>, set<string>> _follow){
    follow = _follow;
}

void ParsingTable::set_productions(multimap<shared_ptr<Token>, vector<shared_ptr<Token>>> prod){
    productions = prod;
}


void ParsingTable::fill_parsing_table(){

    // add "$" to the terminals to appear in the parsing table
    shared_ptr<Token> t = make_shared<Terminal>("$");
    Terminals.push_back(t);

    for (unsigned int i = 0; i < NonTerminals.size(); i++){
        shared_ptr<Token> NT = NonTerminals[i];
        map<shared_ptr<Token>, vector<shared_ptr<Token>>> entry;
        for (unsigned int j = 0; j < Terminals.size(); j++){
            shared_ptr<Token> T = Terminals[j];
            set<string> _first = first[NT];
            set<string> _follow = follow[NT];

            if (_first.find(T->getType()) != _first.end()){
                vector<shared_ptr<Token>> v = add_terminal(NT, T->getType());
                entry.insert({T, v});

            } else if (_follow.find(T->getType()) != _follow.end() && _first.find("0") != _first.end()){ // put epsilon
                shared_ptr<Token> eps = make_shared<Terminal>("0");
                vector<shared_ptr<Token>> v;
                v.push_back(eps);
                entry.insert({T, v});
            } else if (_follow.find(T->getType()) != _follow.end()){  // put synch
                shared_ptr<Token> synch = make_shared<Terminal>("synch");
                vector<shared_ptr<Token>> v;
                v.push_back(synch);
                entry.insert({T, v});
            } else {
                // error
                shared_ptr<Token> error = make_shared<Terminal>("ERROR");
                vector<shared_ptr<Token>> v;
                v.push_back(error);
                entry.insert({T, v});
            }

        }
        table.insert({NT, entry});

    }
}

vector<shared_ptr<Token>> ParsingTable::add_terminal(shared_ptr<Token> NT, string terminal){

    for (auto &production : productions) {
        shared_ptr<Token> nonTerminal = production.first;
        if (nonTerminal->getType() != NT->getType()) continue;
        vector<shared_ptr<Token>> rule = production.second;
        shared_ptr<Token> first_token = rule[0];
        if (first_token->getType() == terminal){
            return rule;
        } else {
            bool isTerminal = false;
            for (unsigned int i = 0; i < Terminals.size(); i++){
                if (first_token->getType() == Terminals[i]->getType())
                    isTerminal = true;
            }

            if (!isTerminal){
                set<string> _first = first[first_token];
                if (_first.find(terminal) != _first.end()){
                    return rule;
                }
            }
        }

    }

}
