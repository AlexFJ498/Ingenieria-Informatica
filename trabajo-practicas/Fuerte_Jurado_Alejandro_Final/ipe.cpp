/*! 
  \file ipe.cpp
  \brief Main program
*/

/*!
 \mainpage Compilador pseudocódigo
 \author   Alejandro Fuerte Jurado
 \date     2019 - 5 - 24
 \version  1.0
*/



#include <stdio.h>
#include <string>
#include <fstream>
#include "includes/macros.hpp"
//

/////////////////////////////
/* 
  AST class
  IMPORTANT: must be written before ipe.tab.h
*/
#include "ast/ast.hpp"
////////////////////////////////////////

#include "./parser/ipe.tab.h"

int lineNumber = 1; //!< Line counter

bool interactiveMode; //!< Control the interactive mode of execution of the interpreter


extern FILE * yyin; //!< Standard input device for yylex() 
std::string progname; //!<  Program name
//


//////////////////////////////////////////////

// Use for recovery of runtime errors 
#include <setjmp.h>
#include <signal.h>

// Error recovery functions 
#include "error/error.hpp"


lp::AST *root; //!< Root of the abstract syntax tree AST
///////////////////////////////////////////// 

//////////////////////////////////////////////

#include "table/init.hpp"


/*
 jhmp_buf
    This is an array type capable of storing the information of a calling environment to be restored later.
   This information is filled by calling macro setjmp and can be restored by calling function longjmp.
*/
extern jmp_buf begin; //!<  It enables recovery of runtime errors 

//////////////////////////////////////////////

#include "table/table.hpp"

lp::Table table; //!< Table of Symbols



// cout.precision
#include <iostream>
//////////////////////////////////////////////////

//! \name Main program

/*! 
	\brief  Main function
	\param  argc: number of command line parameters
	\param  argv: values of command line parameters
	\return int
	\note   C++ requires that main returns an int value
	\sa     yyparse, yylex
*/
int main(int argc, char *argv[])
{
 // Option -t needed
 // yydebug = 1;
 
 /* 
   If the input file exists 
      then 
           it is set as input device for yylex();
      otherwise
            the input device is the keyboard (stdin)
 */
 if (argc == 2) 
 {
    if(( yyin = fopen(argv[1],"r"))==NULL){
		  std::cerr << BIRED; 
		  std::cout<<"Error: no existe el fichero"<<std::endl;
		  std::cerr << RESET; 
		return -1;
	}

	 interactiveMode = false;
 }
else
 {
	interactiveMode = true;
 }

 // Copy the name of the interpreter 
	progname = argv[0];

 /* Number of decimal places */ 
 std::cout.precision(7);

 /* 
   Table of symbols initialization 
   Must be written before the recovery sentence: setjmp
 */
   init(table);

/* Sets a viable state to continue after a runtime error */
 setjmp(begin);

 /* The name of the function to handle floating-point errors is set */
 signal(SIGFPE,fpecatch);

 // Parser function
  yyparse();

 if (interactiveMode == false)
 {
  /*  root->print(); */
   root->evaluate();
 }

 /* End of program */
 return 0;
}



