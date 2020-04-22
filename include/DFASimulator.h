#ifndef DFASIMULATOR_H
#define DFASIMULATOR_H
#include "includes.h"
#include "DFAState.h"


class DFASimulator
{
    public:
        DFASimulator();
        virtual ~DFASimulator();
        string simulate(DFAState& state, string inputString);

    protected:

    private:
};

#endif // DFASIMULATOR_H
