/*!	
	\file   init.hpp
	\brief   Prototype of the function for the initialization of table of symbols
	\author  
	\date    2017-12-5
	\version 1.0
*/

#ifndef _INIT_HPP_
#define _INIT_HPP_

// sin, cos, atan, fabs, ...
#include <math.h>

#include "table.hpp"

// IMPORTANT: This file must be before y.tab.h
#include "../ast/ast.hpp"
///////////////////////////////////////

//  interpreter.tab.h contains the number values of the tokens produced by the parser
#include "../parser/interpreter.tab.h"

///////////////////////////////////////
// NEW in example 13
#include "mathFunction.hpp"
#include "builtinParameter1.hpp"
///////////////////////////////////////

///////////////////////////////////////
// NEW in example 14
#include "builtinParameter0.hpp"
#include "builtinParameter2.hpp"
///////////////////////////////////////


/*!
  \ brief Predefined numeric constants
*/
static struct {
          std::string name ;
	      double value;
	      } numericConstant[] = { 
	                    "PI",    3.14159265358979323846,
	                    "E",     2.71828182845904523536,
	                    "GAMMA", 0.57721566490153286060,
	                    "DEG",  57.29577951308232087680,
	                    "PHI",   1.61803398874989484820,
	                    "",      0
	                   };



/*!
  \ brief Predefined logical constants
*/
// NEW in example 15 
static struct {
          std::string name ;
	      bool value;
	      } logicalConstant[] = { 
	                    "TRUE", true,
	                    "FALSE", false,
	                    "",      0
	                   };


// NEW in example 12 
/*!
  \ brief Predefined keywords
*/
static struct {
          std::string name ;
	      int token;
	      } keyword[] = {
	                    "LEER",             LEER,
						"LEER_CADENA",      LEER_CADENA,
						"ESCRIBIR",         ESCRIBIR,
						"ESCRIBIR_CADENA",  ESCRIBIR_CADENA,
						"SI",               SI,
						"ENTONCES",         ENTONCES,
						"SI_NO",            SI_NO,
						"FIN_SI",           FIN_SI,
						"MIENTRAS",         MIENTRAS,
						"HACER",            HACER,
						"FIN_MIENTRAS",     FIN_MIENTRAS,
						"REPETIR",          REPETIR,
						"HASTA",            HASTA,
						"PARA",             PARA,
						"FIN_PARA",         FIN_PARA,
						"DESDE",            DESDE,
						"PASO",             PASO,	
	                    "",      0
	                   };


// NEW in example 13

static struct {    /* Predefined functions names */ 
                std::string name ;
				lp::TypePointerDoubleFunction_1 function;
              } function_1 [] = {
									"SIN",     sin,
		    						"COS",     cos,
		    						"ATAN",    atan,
		    						"LOG",     Log,
		    						"LOG10",   Log10,
		    						"EXP",     Exp,
		    						"SQRT",    Sqrt,
		    						"INTEGER", integer,
		    						"ABS",     fabs,   
		    						"",       0
		              };

// NEW in example 14
static struct {   
                std::string name ;
				lp::TypePointerDoubleFunction_0 function;
              } function_0 [] = {
						"RANDOM", Random,
		                "",       0
		              };


// NEW in example 14
static struct {    /* Nombres predefinidos de funciones con 2 argumentos */ 
                std::string name ;
				lp::TypePointerDoubleFunction_2 function;
              } function_2 [] = {
	                   "ATAN2",   Atan2,
		                "",       0
		              };



/*!		
	\brief   Initialize the table of symbols
	\return  void 
*/

void init(lp::Table &t);

// End of _INIT_HPP_
#endif
