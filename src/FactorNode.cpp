#include <FactorNode.h>

FactorNode::FactorNode(int Size,  vector<std::string> CommonString){
    this->Size = Size;
    this->CommonString = CommonString;

}

FactorNode::~FactorNode(){

}

int FactorNode::GetSize(){
    return this->Size;
}

vector<int> FactorNode::GetProductions(){
    return this->Productions;
}

vector<std::string> FactorNode::GetCommonString(){
    return this->CommonString;
}

void FactorNode::AddNumOfProduction(int Num){
    this->Productions.push_back(Num);
}
