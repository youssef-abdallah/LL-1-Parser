#ifndef FACTORNODE_H_INCLUDED
#define FACTORNODE_H_INCLUDED

#include "includes.h"
#include <string>

struct FactorNode
{
private:
    unsigned Size;
    vector<int> Productions;
     vector<std::string> CommonString;
public:
	FactorNode(unsigned Size,  vector<std::string> CommonString);
	~FactorNode();
	unsigned GetSize();
	vector<int> GetProductions();
    vector<std::string> GetCommonString();
    void AddNumOfProduction(int Num);
};

#endif // FACTORNODE_H_INCLUDED
