#include "includes.h"
#include "Token.h"
#include "Terminal.h"
#include "NonTerminal.h"
#include "Grammar.h"
#include "ReadFile.h"

using namespace std;

int main()
{
    /*shared_ptr<NonTerminal> p1 = make_shared<NonTerminal>("E");
    shared_ptr<NonTerminal> p2 = make_shared<NonTerminal>("Edash");
    shared_ptr<NonTerminal> p3 = make_shared<NonTerminal>("T");
    shared_ptr<NonTerminal> p4 = make_shared<NonTerminal>("Tdash");
    shared_ptr<NonTerminal> p5 = make_shared<NonTerminal>("F");
    shared_ptr<Token> p6 = make_shared<Terminal>("+");
    shared_ptr<Token> p7 = make_shared<Terminal>("*");
    shared_ptr<Token> p8 = make_shared<Terminal>("(");
    shared_ptr<Token> p9 = make_shared<Terminal>(")");
    shared_ptr<Token> p10 = make_shared<Terminal>("id");
    vector<shared_ptr<Token>> v1, v2, v3, v4, v5, v6, v7;
    v1.push_back(p3);
    v1.push_back(p2);
    v2.push_back(p6);
    v2.push_back(p3);
    v2.push_back(p2);
    v4.push_back(p5);
    v4.push_back(p4);
    v5.push_back(p7);
    v5.push_back(p5);
    v5.push_back(p4);
    v6.push_back(p8);
    v6.push_back(p1);
    v6.push_back(p9);
    v7.push_back(p10);

    Grammar grammar;
    grammar.addProduction(p1, v1);
    grammar.addProduction(p2, v2);
    //grammar.addProduction(p2, v3);
    grammar.addProduction(p3, v4);
    grammar.addProduction(p4, v5);
    //grammar.addProduction(p4, v3);
    grammar.addProduction(p5, v6);
    grammar.addProduction(p5, v7);

    grammar.computeFirst();
    map<shared_ptr<Token>, set<string>> mp = grammar.getFirst();
    for (auto elem : mp) {
        for (auto elem2 : elem.second) {
            cout << elem.first->getType() << " " << elem2 << " ";
        }
        cout << endl;
    }
    grammar.computeFollow();
    mp = grammar.getFollow();
    for (auto elem : mp) {
        for (auto elem2 : elem.second) {
            cout << elem.first->getType() << " " << elem2 << " ";
        }
        cout << endl;
    }*/
    ReadFile file;
    Grammar grammar = file.GetGrammar();

    grammar.computeFirst();
    map<shared_ptr<Token>, set<string>> mp = grammar.getFirst();
    for (auto elem : mp) {
        for (auto elem2 : elem.second) {
            cout << elem.first->getType() << " " << elem2 << " ";
        }
        cout << endl;
    }
    cout << '\n' << '\n';
    grammar.computeFollow();
    mp = grammar.getFollow();
    for (auto elem : mp) {
        for (auto elem2 : elem.second) {
            cout << elem.first->getType() << " " << elem2 << " ";
        }
        cout << endl;
    }
    return 0;
}

