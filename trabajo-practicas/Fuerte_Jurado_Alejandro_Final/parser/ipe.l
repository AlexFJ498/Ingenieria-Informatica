/*! 
  \file ipe.l
  \brief Lexical or scanner file
*/
%{
#include <iostream>

/*********************/
/* atof */
#include <stdlib.h>
/*********************/

/* Macros for the screen */
#include "../includes/macros.hpp"

/*********************/
/* 
  AST class
  IMPORTANT: must be written before ipe.tab.h
*/
#include "../ast/ast.hpp"
/*********************/

/*  ipe.tab.h contains the numeric values of the tokens produced by the parser */
#include "ipe.tab.h"

/********************/
#include "../error/error.hpp"
/********************/


/*********************************************/
/* Table of symbols */
#include "../table/table.hpp"

#include "../table/numericVariable.hpp"
#include "../table/cadenaVariable.hpp"

extern lp::Table table; //!< External Table of Symbols
/*********************************************/

extern int lineNumber; //!< External line counter

%}


/*! \name REGULAR DEFINITIONS  */

DIGIT  [0-9] 

LETTER [a-zA-Z]

SUBRAYADO "_"

NUMBER1 {DIGIT}+\.?

NUMBER2 {DIGIT}*\.{DIGIT}+

IDENTIFIER  {LETTER}({LETTER}|{DIGIT}|{SUBRAYADO}({LETTER}|{DIGIT}))*

/* STATE  */
%x ERROR
%x ESTADO_CADENA
%x ESTADO_COMENTARIO
%x ESTADO_COMENTARIO2

/*! \name REGULAR EXPRESSIONS  */
%%

[ \t] 	{ ; }    /* skip white space and tabular */

\n      { 
			/* Line counter */
           	lineNumber++; 
	
        	/* return NEWLINE; */
        }

";"		{
			return SEMICOLON;
		}


","		{
			return COMMA;
		}

{NUMBER1}|{NUMBER2}   {
			/* Conversion of type and sending of the numerical value to the parser */
			yylval.number = atof(yytext); 

                        return NUMBER; 
                      }

"'"		{
			/* Se activa el reconocimiento de la cadena */
			BEGIN ESTADO_CADENA; 
		}


<ESTADO_CADENA>"'"  { /* Fin de la cadena: se vuelve al estado por defecto */
			        BEGIN 0; 
			        yytext[yyleng-1]='\0';

				yylval.cadena = (char *) malloc(strlen(yytext) + 1);
				strcpy(yylval.cadena,yytext);
				return CADENA;
		    } 

<ESTADO_CADENA>"\\\'"     {yymore();}
<ESTADO_CADENA>"\\t"       {
				yymore(); 
				char tab[10] = "  ";
				char esp[10] = "";
				yytext[yyleng-2] = *tab;
				yytext[yyleng-1] = *esp;
			}
<ESTADO_CADENA>.          {yymore();}     
<ESTADO_CADENA>"\\n"    {
				yymore(); 
				char esp[10] ="";
				char tab[10] = "\n";
				yytext[yyleng-2] = *tab;
				yytext[yyleng-1] = *esp;
				lineNumber++;
				yymore();
			}

"#"	      	{
			  /* Se activa el reconocimiento de un comentario */
			  BEGIN ESTADO_COMENTARIO; 
		}

<ESTADO_COMENTARIO>"#"            { /* Fin del comentario: se vuelve al estado por defecto */
				  BEGIN 0; 
				  }      
<ESTADO_COMENTARIO>.        {;}
<ESTADO_COMENTARIO>\n       {;}

"@"				{
					BEGIN ESTADO_COMENTARIO2;
				}
<ESTADO_COMENTARIO2>.        {;}
<ESTADO_COMENTARIO2>\n {BEGIN 0;}


{IDENTIFIER}   		 {

						for(int i=0; yytext[i] != '\0'; i++){
							yytext[i] = tolower(yytext[i]);
						}

						 std::string identifier(yytext);

						/* 
                          strdup() function returns a pointer to a new string 
                          which  is a duplicate of the string yytext
                        */

						  yylval.identifier =  strdup(yytext);

						/* No diferenciar entre mayúsculas y minúsculas */
						

						/* If the identifier is not in the table of symbols then it is inserted */	
						 if (table.lookupSymbol(identifier) == false)
							{
								/* 
								 The identifier is inserted into the symbol table 
								 as undefined Variable with value 0.0
								*/
								lp::NumericVariable *n = new lp::NumericVariable(identifier,VARIABLE,UNDEFINED,0.0);

								/* A pointer to the new NumericVariable is inserted into the table of symbols */
								table.installSymbol(n);

								return VARIABLE;
							}

						/* 
							If the identifier is in the table of symbols then its token is returned 
								The identifier can be a variable or a numeric constant
						*/
						else 
							{
								lp::Symbol	*s = table.getSymbol(identifier);

/*
								std::cout << "lex: "<< s->getName() 
										  << "token " << s->getToken()
  										  << std::endl; 
*/

								/*  If the identifier is in the table then its token is returned  */
								return s->getToken();
							}
                     }

"-"		{ return MINUS;  } 			
"+"		{ return PLUS;   } 			

"*"	    { return MULTIPLICATION; } 	
"/"     { return DIVISION; } 		

"("     { return LPAREN; } 			
")"	    { return RPAREN; } 			


(?i:_div)  { return DIVISION_ENTERA; }
(?i:_mod)  { return MODULO; }			
(?i:_borrar) { return BORRAR; }
(?i:_lugar)  { return LUGAR; }

"**"    { return POWER; }			

":=" 	{ return ASSIGNMENT; }		

"="	{ return EQUAL; }			

"<>"	{ return NOT_EQUAL; }		

">="	{ return GREATER_OR_EQUAL; }

"<="	{ return LESS_OR_EQUAL; }	

">"		{ return GREATER_THAN; }	

"<"		{ return LESS_THAN; }		

(?i:_no)	{ return NOT; }				

(?i:_o)	{ return OR; }				

(?i:_y)	{ return AND; }				

"||"    { return CONCATENACION; }



^~ { /* The interpreter finishes when the symbol ~ is written at the beginning of the line */
	  //std::cout << CLEAR_SCREEN; 
	  //PLACE(24,10);
  	  std::cout <<  BIYELLOW;
   	  std::cout <<  ">>>>>>> End of program <<<<<<<";
 	  std::cout << std::endl;
   	  std::cout << RESET;
	  //PLACE(25,1);

  	  return 0;
	}

<<EOF>> { /* The interpreter finishes when finds the end of file character */
		  /*PLACE(24,10);
	  	  std::cout <<  BICYAN;
	   	  std::cout <<  ">>>>>>> End of file <<<<<<<";
	 	  std::cout << std::endl;
	   	  std::cout << RESET;
		  PLACE(25,1);
		*/
	  	  return 0;
		
	}


.								{ 	
									/* Any other character */
									/* Change to error state */
									BEGIN(ERROR); 

									/* 
										The current value of yytext 
										will be concatenated with the next character
									*/
									yymore();  
								}

<ERROR>[^0-9+\-*/()\^% \t\n\;a-zA-Z=<>!&]	{ 
								  /* 
									The current value of yytext 
									will be concatenated with the next character
								  */
									yymore(); 
								}

<ERROR>(.|\n)                { 
								/* Rewind one position */
								yyless(yyleng-1); 

								/* Display the error message */
								warning("Lexical error", yytext);

								/* Restore the initial state */
   								BEGIN(INITIAL);
							}
%%

