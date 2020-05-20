/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 24 "CFG.y" /* yacc.c:1909  */

    #include "my_header.h"

#line 48 "y.tab.h" /* yacc.c:1909  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IF_KEYWORD = 258,
    INT_KEYWORD = 259,
    ELSE_KEYWORD = 260,
    WHILE_KEYWORD = 261,
    FLOAT_KEYWORD = 262,
    SEMI_COLON = 263,
    LEFT_BRACKET = 264,
    RIGHT_BRACKET = 265,
    LEFT_CURLY_BRACE = 266,
    RIGHT_CURLY_BRACE = 267,
    ASSIGNMENT_OPERATOR = 268,
    RELATIONAL_OPERATOR = 269,
    ADD_OPERATOR = 270,
    SUB_OPERATOR = 271,
    DIV_OPERATOR = 272,
    MUL_OPERATOR = 273,
    INT = 274,
    FLOAT = 275,
    IDENTIFIER = 276
  };
#endif
/* Tokens.  */
#define IF_KEYWORD 258
#define INT_KEYWORD 259
#define ELSE_KEYWORD 260
#define WHILE_KEYWORD 261
#define FLOAT_KEYWORD 262
#define SEMI_COLON 263
#define LEFT_BRACKET 264
#define RIGHT_BRACKET 265
#define LEFT_CURLY_BRACE 266
#define RIGHT_CURLY_BRACE 267
#define ASSIGNMENT_OPERATOR 268
#define RELATIONAL_OPERATOR 269
#define ADD_OPERATOR 270
#define SUB_OPERATOR 271
#define DIV_OPERATOR 272
#define MUL_OPERATOR 273
#define INT 274
#define FLOAT 275
#define IDENTIFIER 276

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 28 "CFG.y" /* yacc.c:1909  */

    int iVal;
    float fVal;
    char* idLexeme;
    enum dataType type;

#line 109 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
