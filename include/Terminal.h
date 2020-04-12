#ifndef TERMINAL_H
#define TERMINAL_H

#include "Token.h"

class Terminal : public Token
{
    public:
        Terminal();
        Terminal(const string _type) : Token(_type) {};
        virtual ~Terminal();

    protected:

    private:
};

#endif // TERMINAL_H
