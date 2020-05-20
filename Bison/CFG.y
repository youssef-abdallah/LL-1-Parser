%{
    #include <bits/stdc++.h>
    #include "my_header.h"
    using namespace std;
    int yylex();
    void yyerror (char *s);
    void insertVar(string, enum dataType);
    void logError(string);
    void emit(string);

    int varCnt = 1;
    struct entry
    {
        enum dataType type;
        int varNum;
    };
    map<string, entry> symTab;
    vector<string> code;
%}


%start METHOD_BODY

%code requires {
    #include "my_header.h"
}

%union {
    int iVal;
    float fVal;
    char* idLexeme;
    enum dataType type;
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
%token RELATIONAL_OPERATOR
%token ADD_OPERATOR
%token SUB_OPERATOR
%token DIV_OPERATOR
%token MUL_OPERATOR

%token<iVal> INT
%token<fVal> FLOAT
%token <idLexeme> IDENTIFIER

%type<type> PRIMITIVE_TYPE


%%

METHOD_BODY:
    STATEMENT MORE_STATEMENTS
    ;
MORE_STATEMENTS:
    STATEMENT MORE_STATEMENTS | 
    ;
STATEMENT:
    DECLARATION
    | IF
    | WHILE
    | ASSIGNMENT
    ;
DECLARATION:
    PRIMITIVE_TYPE IDENTIFIER SEMI_COLON
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
    LEFT_CURLY_BRACE STATEMENT
    RIGHT_CURLY_BRACE ELSE_KEYWORD
    LEFT_CURLY_BRACE STATEMENT RIGHT_CURLY_BRACE
    ;
WHILE:
    WHILE_KEYWORD LEFT_BRACKET
    EXPRESSION RIGHT_BRACKET
    LEFT_CURLY_BRACE STATEMENT RIGHT_CURLY_BRACE
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
    ;
SIMPLE_EXPRESSION:
    TERM MORE_TERMS
    ;
MORE_TERMS:
    ADD_OPERATOR {emit("iadd");} TERM MORE_TERMS
    | SUB_OPERATOR {emit("isub");} TERM MORE_TERMS
    | 
    ;
TERM:
    FACTOR MORE_FACTORS
    ;
MORE_FACTORS:
    MUL_OPERATOR {emit("imul");}  FACTOR MORE_FACTORS
    | DIV_OPERATOR {emit("idiv");}  FACTOR MORE_FACTORS
    |
    ;
FACTOR:
    LEFT_BRACKET SIMPLE_EXPRESSION RIGHT_BRACKET
    | IDENTIFIER {
        cout << $1 << endl;
        int idx = symTab[$1].varNum;
        enum dataType type = symTab[$1].type;
        if (type == INT_T) {
            emit("iload " + idx);
        } else {
            emit("fload " + idx);
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
    return yyparse();
}

void yyerror(char *s) {
    fprintf(stderr, "%s\n", s);
}

void logError(string errorMsg) {
    char cstr[errorMsg.size() + 1];
	errorMsg.copy(cstr, errorMsg.size() + 1);
	cstr[errorMsg.size()] = '\0';
    yyerror(cstr);
}

void emit(string codeLine) {
    cout << codeLine << endl;
    code.push_back(codeLine);
}