#ifndef ACTIONRECORD_H
#define ACTIONRECORD_H

#include <Token.h>


class ActionRecord : public Token
{
    public:
        ActionRecord();
        ActionRecord(const string _type) : Token(_type) {};
        virtual void execute(vector<shared_ptr<Token>>&, vector<shared_ptr<Token>>&) = 0;
        virtual ~ActionRecord();
        string getType() {
            return Token::getType();
        }

    protected:

    private:
};

#endif // ACTIONRECORD_H
