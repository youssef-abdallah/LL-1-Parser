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
    st.push(dollarSign);
    st.push(startingSymbol);
    while(1){
        cout << "Top of Stack: " << st.top()->getType();
        cout << "   Input: "<<input[it]->getType() << endl;
        shared_ptr<Token> TOS = st.top();// top of stack
        if(it!=input.size()-1 && TOS->getType()=="$"){
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
                st.pop();
            }
            else{
                cout<< "Error : matching terminals failed! Extra " << TOS->getType()<< " in stack"<<endl;
                st.pop();
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
                    st.pop();
                }
                else if(entry[0]->getType()=="synch"){ // MUST BE UPDATED TO HANDLE ERRORS
                    cout << NT->getType()<< " -> synch"<< endl;
                    st.pop();
                }
                else if(entry[0]->getType()=="ERROR"){// MUST BE UPDATED TO HANDLE ERRORS
                    cout << "ERROR : empty cell" << endl;
                    it++;
                }
                else{
                    cout << NT->getType()<< " -> "<< entry[0]->getType() << endl;
                    st.pop();
                    st.push(entry[0]);
                }
            }
            else{
                cout << NT->getType() << " -> " ;
                for(int i =0 ; i<entry.size(); i++){
                    cout <<entry[i]->getType()<< " ";
                }
                cout << endl;
                st.pop();
                for(int i=entry.size()-1; i>=0 ; i--){
                    st.push(entry[i]);
                }
            }
        }
    }
}


