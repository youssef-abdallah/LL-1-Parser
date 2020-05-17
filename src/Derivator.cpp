#include "Derivator.h"
#include "ParsingTable.h"
#include "NonTerminal.h"
#include "Terminal.h"
#include "Token.h"

Derivator::Derivator()
{
    //ctor
}

Derivator::~Derivator()
{
    //dtor
}


void Derivator::derive(){
    int it = 0; // input iterator
    shared_ptr<Token> dollarSign = make_shared<Terminal>("$");
    stk.push_back(dollarSign);
    stk.push_back(startingSymbol);
    while(1){
        cout << "Top of Stack: " << stk.back()->getType();
        cout << "   Input: "<<input[it]->getType() << endl;
        shared_ptr<Token> TOS = stk.back();// top of stack
        if (TOS->getType() == "ACTION_RECORD") {
            shared_ptr<ActionRecord> semantic_rule = static_pointer_cast<ActionRecord>(TOS);
            semantic_rule->execute(stk, aux_stk);
            stk.pop_back();
            continue;
        }
        int sizeOfInput = input.size()-1;
        if(it!=sizeOfInput && TOS->getType()=="$"){
            cout << "ERROR : Stack is empty & input isn't done!" << endl;
            break;
        }
        if(input[it]->getType()== "$" && TOS->getType()=="$"){ // last step in derivation
            cout << "Successfully Done" << endl;
            break;
        }
        else if(count(Terminals.begin(), Terminals.end(), TOS)>0){ // if top of stack is a terminal
            if(TOS->getType()==input[it]->getType()){
                cout << " matched " << input[it]->getType()<<endl;
                it++;
                aux_stk.push_back(stk.back());
                stk.pop_back();
            }
            else{
                cout<< "Error : matching terminals failed! Extra " << TOS->getType()<< " in stack"<<endl;
                stk.pop_back();
            }
        }
        else{ // if top of stack is non terminal
            shared_ptr<Token> NT = TOS;
            map<shared_ptr<Token>, vector<shared_ptr<Token>>> row = table[NT];
            vector<shared_ptr<Token>> entry ;
            for(auto e : row){
                if(e.first->getType()==input[it]->getType()){
                    entry = e.second;
                }
            }
            if(entry.size()==1){
                if(entry[0]->getType()=="0"){
                    cout << NT->getType()<< " -> epsilon"<< endl;
                    aux_stk.push_back(stk.back());
                    stk.pop_back();
                }
                else if(entry[0]->getType()=="synch"){ // MUST BE UPDATED TO HANDLE ERRORS
                    cout << NT->getType()<< " -> synch"<< endl;
                    aux_stk.push_back(stk.back());
                    stk.pop_back();
                }
                else if(entry[0]->getType()=="ERROR"){// MUST BE UPDATED TO HANDLE ERRORS
                    cout << "ERROR : empty cell" << endl;
                    it++;
                }
                else{
                    cout << NT->getType()<< " -> "<< entry[0]->getType() << endl;
                    aux_stk.push_back(stk.back());
                    stk.pop_back();
                    stk.push_back(entry[0]);
                }
            }
            else{
                cout << NT->getType() << " -> " ;
                int sizeOfEntry = entry.size();
                for(int i =0 ; i<sizeOfEntry; i++){
                    cout <<entry[i]->getType()<< " ";
                }
                cout << endl;
                aux_stk.push_back(stk.back());
                stk.pop_back();
                for(int i=entry.size()-1; i>=0 ; i--){
                    stk.push_back(entry[i]);
                }
            }
        }
    }
}


