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
        string attribute;

    protected:
        string type;
    private:
};

#endif // TOKEN_H
