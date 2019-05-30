/*!	
	\file   init.hpp
	\brief   Prototype of the function for the initialization of table of symbols
	\author  Alejandro Fuerte Jurado
	\date    2019-24-5
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
#include "../parser/ipe.tab.h"

///////////////////////////////////////
#include "mathFunction.hpp"
#include "builtinParameter1.hpp"
///////////////////////////////////////

///////////////////////////////////////
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
static struct {
          std::string name ;
	      bool value;
	      } logicalConstant[] = { 
	                    "true", true,
	                    "false", false,
	                    "",      0
	                   };


/*!
  \ brief Predefined keywords
*/
static struct {
          std::string name ;
	      int token;
	      } keyword[] = {
	                    "leer",             LEER,
						"leer_cadena",      LEER_CADENA,
						"escribir",         ESCRIBIR,
						"escribir_cadena",  ESCRIBIR_CADENA,
						"si",               SI,
						"entonces",         ENTONCES,
						"si_no",            SI_NO,
						"fin_si",           FIN_SI,
						"mientras",         MIENTRAS,
						"hacer",            HACER,
						"fin_mientras",     FIN_MIENTRAS,
						"repetir",          REPETIR,
						"hasta",            HASTA,
						"para",             PARA,
						"fin_para",         FIN_PARA,
						"desde",            DESDE,
						"paso",             PASO,	
	                    "",      0
	                   };



static struct {    /* Predefined functions names */ 
                std::string name ;
				lp::TypePointerDoubleFunction_1 function;
              } function_1 [] = {
									"sin",     sin,
		    						"cos",     cos,
		    						"atan",    atan,
		    						"log",     Log,
		    						"log10",   Log10,
		    						"exp",     Exp,
		    						"sqrt",    Sqrt,
		    						"integer", integer,
		    						"abs",     fabs,   
		    						"",       0
		              };

static struct {   
                std::string name ;
				lp::TypePointerDoubleFunction_0 function;
              } function_0 [] = {
						"random", Random,
		                "",       0
		              };


static struct {    /* Nombres predefinidos de funciones con 2 argumentos */ 
                std::string name ;
				lp::TypePointerDoubleFunction_2 function;
              } function_2 [] = {
	                   "atan2",   Atan2,
		                "",       0
		              };



/*!		
	\brief   Initialize the table of symbols
	\return  void 
*/

void init(lp::Table &t);

// End of _INIT_HPP_
#endif
