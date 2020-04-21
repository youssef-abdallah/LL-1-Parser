#ifndef DERIVATOR_H
#define DERIVATOR_H
#include "includes.h"
#include "NonTerminal.h"
#include "Terminal.h"
#include "Token.h"
#include <bits/stdc++.h>



class Derivator
{
    public:
        Derivator();
        virtual ~Derivator();
       /* Derivator(map<shared_ptr<Token>, map<shared_ptr<Token>, vector<shared_ptr<Token>>>> Table,
                  vector <shared_ptr<Terminal>> Input){
            this->table = Table;
            this->input = Input;
        }*/
        void derive();
        void set_terminals(vector<shared_ptr<Token>> ter){
            this->Terminals=ter;
        }
        void setStartingSymbol(shared_ptr<NonTerminal> starting){
            this->startingSymbol = starting;
        }
        void setTable(map<shared_ptr<Token>, map<shared_ptr<Token>, vector<shared_ptr<Token>>>> Table){
            this->table = Table;
        }
        void setInput(vector <shared_ptr<Terminal>> Input){
            this->input=Input;
        }

    protected:

    private:
        stack <shared_ptr<Token>> st;
        vector <shared_ptr<Terminal>> input;
        map<shared_ptr<Token>, map<shared_ptr<Token>, vector<shared_ptr<Token>>>> table;
        vector<shared_ptr<Token>> Terminals;
        shared_ptr<NonTerminal> startingSymbol;

};

#endif // DERIVATOR_H
