%{
    #include <bits/stdc++.h>
    #include "my_header.h"
    
    using namespace std;
    int yylex();
    void yyerror (char *s);
    void insertVar(string, enum dataType);
    void logError(string);
    void emit(string);
    void backPatch(vector<int> *list, string *label);
    vector<int>* merge(vector<int> *, vector<int> *);
    void printCode();
    string getOperation(string op);
    void generateHeader();
    void generateFooter();
    extern FILE *yyin;
    ofstream out("myFile.j");

    int varCnt = 1;
    int labelCnt = 1;
    struct entry
    {
        enum dataType type;
        int varNum;
    };
    map<string, entry> symTab;
    map<string, string> operations = {
        {"==", "if_icmpne"},
        {"<=", "if_icmpgt"},
        {">=", "if_icmplt"},
        {"!=", "if_icmpeq"},
        {">", "if_icmple"},
        {"<", "if_icmpge"},
    };
    vector<string> code;
    int InsCnt = 0;
%}


%start METHOD_BODY

%code requires {
    #include "my_header.h"
    #include <bits/stdc++.h>
    using namespace std;
}

%union {
    int iVal;
    float fVal;
    char* idLexeme;
    enum dataType type;
    struct{
        string *label;
    } labelName;
    struct {
        vector<int> *trueList, *falseList, *nextList;
    } list_type;
}

%token IF_KEYWORD
%token INT_KEYWORD
%token ELSE_KEYWORD
%token WHILE_KEYWORD
%token FLOAT_KEYWORD
%token SEMI_COLON
%token LEFT_BRACKET
%token RIGHT_BRACKET
%token LEFT_CURLY_BRACE
%token RIGHT_CURLY_BRACE
%token ASSIGNMENT_OPERATOR
%token ADD_OPERATOR
%token SUB_OPERATOR
%token DIV_OPERATOR
%token MUL_OPERATOR

%token<iVal> INT
%token<fVal> FLOAT
%token <idLexeme> IDENTIFIER
%token<idLexeme> RELATIONAL_OPERATOR

%type<list_type> EXPRESSION
%type<type> PRIMITIVE_TYPE
%type<labelName> MARKER
%type<list_type> GOTO
%type<list_type> STATEMENT
%type<list_type> MORE_STATEMENTS
%type<list_type> IF
%type<list_type> WHILE

%%

METHOD_BODY:
    {
        generateHeader();
    }
    STATEMENT MORE_STATEMENTS
    {
        generateFooter();
    }
    ;
MORE_STATEMENTS:
    STATEMENT MARKER MORE_STATEMENTS { 
        $$.nextList = $3.nextList;
        backPatch($1.nextList, $2.label);
        }
    | {$$.nextList = new vector<int> (); }
    ;
STATEMENT:
    DECLARATION {$$.nextList = new vector<int> (); }
    | IF { $$.nextList = $1.nextList; }
    | WHILE { $$.nextList = $1.nextList; }
    | ASSIGNMENT { $$.nextList = new vector<int> (); }
    ;
DECLARATION:
    PRIMITIVE_TYPE IDENTIFIER ASSIGNMENT_OPERATOR EXPRESSION SEMI_COLON
    {
        enum dataType type = $1;
        string lexeme = $2;
        insertVar(lexeme, type);
        int idx = symTab[lexeme].varNum;
        if (type == INT_T) {
            emit("istore " + to_string(idx));
        } else {
            emit("fstore " + to_string(idx));
        }
    }
    | PRIMITIVE_TYPE IDENTIFIER SEMI_COLON
    {
        enum dataType type = $1;
        string lexeme = $2;
        insertVar(lexeme, type);
    }
    ;
PRIMITIVE_TYPE:
    INT_KEYWORD {$$ = INT_T;}
    | FLOAT_KEYWORD {$$ = FLOAT_T;}
    ;
IF:
    IF_KEYWORD LEFT_BRACKET
    EXPRESSION RIGHT_BRACKET
    LEFT_CURLY_BRACE STATEMENT GOTO
    RIGHT_CURLY_BRACE ELSE_KEYWORD
    LEFT_CURLY_BRACE MARKER STATEMENT RIGHT_CURLY_BRACE
    {
        backPatch($3.falseList, $11.label);
        //backPatch($7.nextList, $14.label);
        $$.nextList = merge($7.nextList, $6.nextList);
        $$.nextList = merge($$.nextList, $12.nextList);
    }
    ;
WHILE:
    WHILE_KEYWORD LEFT_BRACKET MARKER
    EXPRESSION RIGHT_BRACKET
    LEFT_CURLY_BRACE STATEMENT GOTO RIGHT_CURLY_BRACE
    {
        //backPatch($4.falseList, $10.label);
        backPatch($8.nextList, $3.label);
        $$.nextList = $4.falseList;
    }
    ;
ASSIGNMENT:
    IDENTIFIER ASSIGNMENT_OPERATOR
    EXPRESSION SEMI_COLON
    {
        string id = $1;
        if (!symTab.count(id)) {
            string errorMsg = "Non-declared identifier " + id + "\n";
            logError(errorMsg);
        }
        int idx = symTab[id].varNum;
        enum dataType type = symTab[id].type;
        if (type == INT_T) {
            emit("istore " + to_string(idx));
        } else {
            emit("fstore " + to_string(idx));
        }
    }
    ;
EXPRESSION:
    SIMPLE_EXPRESSION
    | SIMPLE_EXPRESSION RELATIONAL_OPERATOR SIMPLE_EXPRESSION
    {
        $$.falseList = new vector<int>();
        $$.falseList->push_back(code.size());
        emit(getOperation($2) + " ");
    }
    ;
SIMPLE_EXPRESSION:
    TERM MORE_TERMS
    ;
MORE_TERMS:
    ADD_OPERATOR TERM {emit("iadd");} MORE_TERMS
    | SUB_OPERATOR TERM {emit("isub");} MORE_TERMS
    | 
    ;
TERM:
    FACTOR MORE_FACTORS
    ;
MORE_FACTORS:
    MUL_OPERATOR FACTOR {emit("imul");} MORE_FACTORS
    | DIV_OPERATOR FACTOR {emit("idiv");} MORE_FACTORS
    |
    ;
FACTOR:
    LEFT_BRACKET SIMPLE_EXPRESSION RIGHT_BRACKET
    | IDENTIFIER {
        int idx = symTab[$1].varNum;
        enum dataType type = symTab[$1].type;
        if (type == INT_T) {
            emit("iload " + to_string(idx));
        } else {
            emit("fload " + to_string(idx));
        } 
    } 
    | INT
    {
        emit("bipush " + to_string($1));
    }
    | FLOAT
    {
        emit("ldc " + to_string($1));
    }
    ;
GOTO:
    {
        $$.nextList = new vector<int>();
        $$.nextList->push_back(code.size());
        emit("goto ");
    }
    ;
MARKER:
    {   
        $$.label = new string("Label" + to_string(labelCnt++));
        emit(*$$.label + ":");
    }
    ;
%%

void insertVar(string lexeme, enum dataType type) {
    if (!symTab.count(lexeme)) {
        struct entry new_entry;
        new_entry.type = type;
        new_entry.varNum = varCnt++;
        symTab[lexeme] = new_entry;
    } else {
        string errorMsg = "Duplicate declaration for the same identifier" + lexeme + "\n";
        logError(errorMsg);
    }
}

int main(void) {
    FILE *file = fopen("input_program.txt", "r");
    if (!file) {
        cout << "Cannot open input file!";
    }
    yyin = file;
    yyparse();
    printCode();
    return 0;
}

void yyerror(char *s) {
    fprintf(stderr, "%s\n", s);
}

void backPatch(vector<int> *list, string *label) {
    if (list->size()){
        for (int i = 0; i < list->size(); i++){
            code[(*list)[i]] = code[(*list)[i]] + (*label);
        }
    } else {
        remove(code.begin(), code.end(), (*label) + ":");
    }
}

vector<int>* merge(vector<int> *list1, vector<int> *list2) {
    vector<int> *newList = new vector<int>();
    newList->insert(newList->end(), list1->begin(), list1->end());
    newList->insert(newList->end(), list2->begin(), list2->end());
    return newList;
}

void logError(string errorMsg) {
    char cstr[errorMsg.size() + 1];
	errorMsg.copy(cstr, errorMsg.size() + 1);
	cstr[errorMsg.size()] = '\0';
    yyerror(cstr);
}

void emit(string codeLine) {
    //string str = to_string(InsCnt) + ": " + codeLine;
    // cout << InsCnt << " :" << codeLine << endl;
    code.push_back(codeLine);
    //InsCnt++;
}

void printCode(){
    cout << '\n';
    for (string &line : code){
        out << line << '\n';
    }
}

string getOperation(string op){
    return operations[op];
}

void generateHeader() {
    emit(".class public test");
    emit(".super java/lang/Object");
    emit(".method public <init>()V");
    emit("aload_0");
    emit("invokenonvirtual java/lang/Object/<init>()V");
    emit("return");
    emit(".end method\n");
    emit(".method public static main([Ljava/lang/String;)V");
    emit(".limit locals 100");
    emit(".limit stack 50");
}

void generateFooter() {
    emit("return");
    emit(".end method");
}