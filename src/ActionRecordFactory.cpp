#include "ActionRecordFactory.h"

ActionRecordFactory::ActionRecordFactory()
{
    //ctor
}

ActionRecordFactory::~ActionRecordFactory()
{
    //dtor
}

shared_ptr<Token> ActionRecordFactory::create(const string &type) {
    if (type == "1") {
        class DerivedActionRecord : public ActionRecord {
            public:
                void execute(vector<shared_ptr<Token>> stk, vector<shared_ptr<Token>> aux_stk) {
                    stk.pop_back();
                }
        };
        return make_shared<DerivedActionRecord>();
    }
    return 0;
}
