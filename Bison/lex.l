%{
    #include "y.tab.h"
%}
letter [a-zA-Z]
digit [0-9]
digits {digit}+
int {digits}
float [0-9]+"."[0-9]+
id {letter}({letter}|{digits})*
relop "=="|"!="|">"|">="|"<"|"<="

%%
"int" {return INT_KEYWORD;}
"float" {return FLOAT_KEYWORD;}
"if" {return IF_KEYWORD;}
"else" {return ELSE_KEYWORD;}
"while" {return WHILE_KEYWORD;}
{int} {yylval.iVal = atoi(yytext); return INT;}
{float} {yylval.fVal = atof(yytext); return FLOAT;}
{id} {yylval.idLexeme = strdup(yytext); return IDENTIFIER;}
{relop} {return RELATIONAL_OPERATOR;}
"{" {return LEFT_CURLY_BRACE;}
"}" {return RIGHT_CURLY_BRACE;}
"(" {return LEFT_BRACKET;}
")" {return RIGHT_BRACKET;}
";" {return SEMI_COLON;}
"=" {return ASSIGNMENT_OPERATOR;}
"+" {return ADD_OPERATOR;}
"-" {return SUB_OPERATOR;}
"*" {return MUL_OPERATOR;}
"/" {return DIV_OPERATOR;}
%%
int yywrap(void) { return 1; }
