#ifndef NFASIMULATOR_H
#define NFASIMULATOR_H
#include "StateMachine.h"

class NFASimulator
{
    public:
        NFASimulator();
        virtual ~NFASimulator();
        string simulate(StateMachine&, string);

    protected:

    private:
};

#endif // NFASIMULATOR_H
