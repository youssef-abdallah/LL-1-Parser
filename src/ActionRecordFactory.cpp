#include "ActionRecordFactory.h"

ActionRecordFactory::ActionRecordFactory()
{
    //ctor
}

ActionRecordFactory::~ActionRecordFactory()
{
    //dtor
}

void ActionRecordFactory::pop(vector<shared_ptr<Token>> &stk, int i) {
    while (i--) {
        stk.pop_back();
    }
    return;
}

shared_ptr<Token> ActionRecordFactory::create(const string &type) {
    if (type == "\"1.1\"") {
        class DerivedActionRecord : public Token {
            public:
                DerivedActionRecord(string _type) : Token(_type) {};
                virtual void execute(vector<shared_ptr<Token>> &stk, vector<shared_ptr<Token>> &aux_stk) {
                    int p_top = stk.size() - 1;
                    int aux_top = aux_stk.size() - 1;
                    int ntop = stk.size() - 2;
                    stk[ntop]->attribute = aux_stk[aux_top]->attribute;
                }
        };
        return make_shared<DerivedActionRecord>("ACTION_RECORD");
    } else if (type == "\"1.2\"") {
        class DerivedActionRecord : public Token {
            public:
                DerivedActionRecord(string _type) : Token(_type) {};
                virtual void execute(vector<shared_ptr<Token>> &stk, vector<shared_ptr<Token>> &aux_stk) {
                    int p_top = stk.size() - 1;
                    int aux_top = aux_stk.size() - 1;
                    int ntop = stk.size() - 2;
                    pop(aux_stk, 3);
                }
        };
        return make_shared<DerivedActionRecord>("ACTION_RECORD");
    } else if (type == "\"2\"") {
        class DerivedActionRecord : public Token {
            public:
                DerivedActionRecord(string _type) : Token(_type) {};
                virtual void execute(vector<shared_ptr<Token>> &stk, vector<shared_ptr<Token>> &aux_stk) {
                    int p_top = stk.size() - 1;
                    int aux_top = aux_stk.size() - 1;
                    int ntop = stk.size() - 2;
                    aux_stk[aux_top - 1]->attribute = "integer";
                    pop(aux_stk, 1);
                }
        };
        return make_shared<DerivedActionRecord>("ACTION_RECORD");
    } else if (type == "\"3\"") {
        class DerivedActionRecord : public Token {
            public:
                DerivedActionRecord(string _type) : Token(_type) {};
                virtual void execute(vector<shared_ptr<Token>> &stk, vector<shared_ptr<Token>> &aux_stk) {
                    int p_top = stk.size() - 1;
                    int aux_top = aux_stk.size() - 1;
                    int ntop = stk.size() - 2;
                    aux_stk[aux_top - 1]->attribute = "float";
                    pop(aux_stk, 1);
                }
        };
        return make_shared<DerivedActionRecord>("ACTION_RECORD");
    } else if (type == "\"4.1\"") {
        class DerivedActionRecord : public Token {
            public:
                DerivedActionRecord(string _type) : Token(_type) {};
                virtual void execute(vector<shared_ptr<Token>> &stk, vector<shared_ptr<Token>> &aux_stk) {
                    int p_top = stk.size() - 1;
                    int aux_top = aux_stk.size() - 1;
                    int ntop = stk.size() - 2;
                    cout << "Type of " << aux_stk[aux_top]->getType() << " is " << aux_stk[aux_top - 1]->attribute << endl;
                    stk[ntop]->attribute = aux_stk[aux_top - 1]->attribute;
                }
        };
        return make_shared<DerivedActionRecord>("ACTION_RECORD");
    } else if (type == "\"4.2\"") {
        class DerivedActionRecord : public Token {
            public:
                DerivedActionRecord(string _type) : Token(_type) {};
                virtual void execute(vector<shared_ptr<Token>> &stk, vector<shared_ptr<Token>> &aux_stk) {
                    int p_top = stk.size() - 1;
                    int aux_top = aux_stk.size() - 1;
                    int ntop = stk.size() - 2;
                    pop(aux_stk, 2);
                }
        };
        return make_shared<DerivedActionRecord>("ACTION_RECORD");
    } else if (type == "\"5.1\"") {
        class DerivedActionRecord : public Token {
            public:
                DerivedActionRecord(string _type) : Token(_type) {};
                virtual void execute(vector<shared_ptr<Token>> &stk, vector<shared_ptr<Token>> &aux_stk) {
                    int p_top = stk.size() - 1;
                    int aux_top = aux_stk.size() - 1;
                    int ntop = stk.size() - 2;
                    stk[ntop]->attribute = aux_stk[aux_top - 1]->attribute;
                }
        };
        return make_shared<DerivedActionRecord>("ACTION_RECORD");
    } else if (type == "\"5.2\"") {
        class DerivedActionRecord : public Token {
            public:
                DerivedActionRecord(string _type) : Token(_type) {};
                virtual void execute(vector<shared_ptr<Token>> &stk, vector<shared_ptr<Token>> &aux_stk) {
                    int p_top = stk.size() - 1;
                    int aux_top = aux_stk.size() - 1;
                    int ntop = stk.size() - 2;
                    pop(aux_stk, 2);
                }
        };
        return make_shared<DerivedActionRecord>("ACTION_RECORD");
    }
    return 0;
}
