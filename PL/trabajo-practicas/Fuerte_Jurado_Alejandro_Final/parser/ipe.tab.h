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

#ifndef YY_YY_IPE_TAB_H_INCLUDED
# define YY_YY_IPE_TAB_H_INCLUDED
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
    SI = 259,
    ENTONCES = 260,
    SI_NO = 261,
    FIN_SI = 262,
    MIENTRAS = 263,
    HACER = 264,
    FIN_MIENTRAS = 265,
    REPETIR = 266,
    HASTA = 267,
    PARA = 268,
    FIN_PARA = 269,
    DESDE = 270,
    PASO = 271,
    LEER = 272,
    LEER_CADENA = 273,
    ESCRIBIR = 274,
    ESCRIBIR_CADENA = 275,
    BORRAR = 276,
    LUGAR = 277,
    LETFCURLYBRACKET = 278,
    RIGHTCURLYBRACKET = 279,
    ASSIGNMENT = 280,
    COMMA = 281,
    NUMBER = 282,
    CADENA = 283,
    BOOL = 284,
    VARIABLE = 285,
    UNDEFINED = 286,
    CONSTANT = 287,
    BUILTIN = 288,
    OR = 289,
    AND = 290,
    GREATER_OR_EQUAL = 291,
    LESS_OR_EQUAL = 292,
    GREATER_THAN = 293,
    LESS_THAN = 294,
    EQUAL = 295,
    NOT_EQUAL = 296,
    NOT = 297,
    PLUS = 298,
    MINUS = 299,
    MULTIPLICATION = 300,
    DIVISION = 301,
    MODULO = 302,
    DIVISION_ENTERA = 303,
    CONCATENACION = 304,
    LPAREN = 305,
    RPAREN = 306,
    UNARY = 307,
    POWER = 308
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 116 "ipe.y" /* yacc.c:1909  */

  char * identifier; 				 
  double number;  
  bool logic;						 
  lp::ExpNode *expNode;  			 
  std::list<lp::ExpNode *>  *parameters;    // NOTE: #include<list> must be in interpreter.l, init.cpp, interpreter.cpp
  std::list<lp::Statement *> *stmts; 
  lp::Statement *st;				 
  lp::AST *prog;					 
  char * cadena;

#line 120 "ipe.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_IPE_TAB_H_INCLUDED  */
