/*!	
	\file    cadenaVariable.cpp
	\brief   Code of some functions of CadenaVariable class
	\author 
	\date    2017-10-19
	\version 1.0
*/


#include <iostream>

// Delete the comment if you want to use atof in the operator overload >>
// #include <stdlib.h>

#include "cadenaVariable.hpp"


/*
 Definitions of the read and write functions of the CadenaVariable class 
*/

void lp::CadenaVariable::read()
{
  // Inherited attributes
   std::cout << "Name of the CadenaVariable: ";
   std::cin >> this->_name;

   std::cout << "Token of the CadenaVariable: ";
   std::cin >> this->_token;
   // The \n character is read 
   std::cin.ignore(); 

   std::cout << "Type of the CadenaVariable: ";
   std::cin >> this->_type;
   // The \n character is read 
   std::cin.ignore(); 


   // Own attribute
   std::string aux;
   std::cout << "Value of the CadenaVariable: ";
   std::cin >> aux;
   this->_value = aux.c_str();
   // The \n character is read 
   std::cin.ignore(); 
}


void lp::CadenaVariable::write() const
{
  // Inherited methods
  std::cout << "Name:" << this->getName() << std::endl;
  std::cout << "Token:" << this->getToken() << std::endl;
  std::cout << "Type:" << this->getType() << std::endl;

  // Own method
  std::cout << "Value:" << this->getValue() << std::endl;
}

lp::CadenaVariable &lp::CadenaVariable::operator=(const lp::CadenaVariable &n)
  {
 	// Check that is not the current object
		if (this != &n) 
		{
			// Inherited methods
			this->setName(n.getName());

			this->setToken(n.getToken());

			this->setType(n.getType());

			// Own method
			this->setValue(n.getValue());
		}

    // Return the current object
		return *this;
  }


/*!	
	\namespace lp
	\brief Name space for the subject Language Processors
*/
namespace lp{

std::istream &operator>>(std::istream &i, lp::CadenaVariable &n)
{
  // Inherited attributes
  i >> n._name;

  i >> n._token;
  // The \n character is read 
  i.ignore();


  i >> n._type;
  // The \n character is read 
  i.ignore();


  i >> n._token;
  // The \n character is read 
  i.ignore();

  ////////////////////////////////////

  // Own attribute
  std::string aux;
  i >> aux;
  n._value = aux.c_str();
  // The \n character is read 
  i.ignore();

  ////////////////////////////////////

/* Alternative way using an auxiliar string 

  std::string auxiliar;

  std::getline(i,auxiliar);
  n._token = atof(auxiliar.c_str());

  std::getline(i,auxiliar);
  n._type = atof(auxiliar.c_str());

  std::getline(i,auxiliar);
  n._value = atof(auxiliar.c_str());

*/

  // The input stream is returned
  return i;
}


std::ostream &operator<<(std::ostream &o, lp::CadenaVariable const &n)
{
  // Inherited attributes
  o << n._name << std::endl;

  o << n._token << std::endl;

  o << n._type << std::endl;

  // Own attribute
  o << n._value << std::endl;

  // The output stream is returned
  return o;
}

// End of name space lp
} 




