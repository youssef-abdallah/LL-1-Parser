#ifndef TOKEN_H
#define TOKEN_H
#include "includes.h"

class Token
{
    public:
        Token();
        virtual ~Token();

        Token(const string _type) : type {_type} {};

        string getType() {
            return type;
        }

        void setType(string _type) {
            type = _type;
        }

    protected:

    private:
        string type;
};

#endif // TOKEN_H
