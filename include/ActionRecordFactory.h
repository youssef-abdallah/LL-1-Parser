#ifndef ACTIONRECORDFACTORY_H
#define ACTIONRECORDFACTORY_H
#include "includes.h"
#include "Token.h"
#include "ActionRecord.h"


class ActionRecordFactory
{
    public:
        ActionRecordFactory();
        virtual ~ActionRecordFactory();
        static shared_ptr<Token> create(const std::string& type);

    protected:

    private:
};

#endif // ACTIONRECORDFACTORY_H
