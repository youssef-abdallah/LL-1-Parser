#ifndef PARSINGTABLE_H
#define PARSINGTABLE_H
#include "includes.h"
#include "NonTerminal.h"
#include "Token.h"


class ParsingTable
{
    public:
        ParsingTable();
        virtual ~ParsingTable();

        // (NonTerminal,Terminal) --> production
        map<shared_ptr<Token>, map<shared_ptr<Token>, vector<shared_ptr<Token>>>> table;
        void set_terminals(vector<shared_ptr<Token>> terminals);
        void set_non_terminals(vector<shared_ptr<NonTerminal>> non_terminals);
        void set_first(map<shared_ptr<Token>, set<string>> first);
        void set_follow(map<shared_ptr<Token>, set<string>> follow);
        void set_productions(multimap<shared_ptr<Token>, vector<shared_ptr<Token>>> prod);
        vector<shared_ptr<Token>> add_terminal(shared_ptr<Token> NT, string terminal);
        vector<shared_ptr<Token>> special_handle(shared_ptr<Token> NT, set<string> _first);
        void fill_parsing_table();

    protected:

    private:
        vector<shared_ptr<NonTerminal>> NonTerminals;
        vector<shared_ptr<Token>> Terminals;
        map<shared_ptr<Token>, set<string>> follow;
        map<shared_ptr<Token>, set<string>> first;
        multimap<shared_ptr<Token>, vector<shared_ptr<Token>>> productions;
};

#endif // PARSINGTABLE_H
