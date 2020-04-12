#ifndef NONTERMINAL_H
#define NONTERMINAL_H

#include "Token.h"


class NonTerminal : public Token
{
    public:
        NonTerminal();
        NonTerminal(string _type) : Token(_type) {};
        virtual ~NonTerminal();

    protected:

    private:
};

#endif // NONTERMINAL_H
