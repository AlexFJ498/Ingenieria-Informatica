/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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

#ifndef YY_YY_INTERPRETER_TAB_H_INCLUDED
# define YY_YY_INTERPRETER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    SEMICOLON = 258,
    PRINT = 259,
    READ = 260,
    SI = 261,
    ENTONCES = 262,
    SI_NO = 263,
    FIN_SI = 264,
    MIENTRAS = 265,
    HACER = 266,
    FIN_MIENTRAS = 267,
    REPETIR = 268,
    HASTA = 269,
    PARA = 270,
    FIN_PARA = 271,
    DESDE = 272,
    PASO = 273,
    LEER = 274,
    LEER_CADENA = 275,
    ESCRIBIR = 276,
    ESCRIBIR_CADENA = 277,
    LETFCURLYBRACKET = 278,
    RIGHTCURLYBRACKET = 279,
    ASSIGNMENT = 280,
    COMMA = 281,
    NUMBER = 282,
    BOOL = 283,
    VARIABLE = 284,
    UNDEFINED = 285,
    CONSTANT = 286,
    BUILTIN = 287,
    OR = 288,
    AND = 289,
    GREATER_OR_EQUAL = 290,
    LESS_OR_EQUAL = 291,
    GREATER_THAN = 292,
    LESS_THAN = 293,
    EQUAL = 294,
    NOT_EQUAL = 295,
    NOT = 296,
    PLUS = 297,
    MINUS = 298,
    MULTIPLICATION = 299,
    DIVISION = 300,
    MODULO = 301,
    LPAREN = 302,
    RPAREN = 303,
    UNARY = 304,
    POWER = 305
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 131 "interpreter.y" /* yacc.c:1909  */

  char * identifier; 				 /* NEW in example 7 */
  double number;  
  bool logic;						 /* NEW in example 15 */
  lp::ExpNode *expNode;  			 /* NEW in example 16 */
  std::list<lp::ExpNode *>  *parameters;    // New in example 16; NOTE: #include<list> must be in interpreter.l, init.cpp, interpreter.cpp
  std::list<lp::Statement *> *stmts; /* NEW in example 16 */
  lp::Statement *st;				 /* NEW in example 16 */
  lp::AST *prog;					 /* NEW in example 16 */

#line 116 "interpreter.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_INTERPRETER_TAB_H_INCLUDED  */
