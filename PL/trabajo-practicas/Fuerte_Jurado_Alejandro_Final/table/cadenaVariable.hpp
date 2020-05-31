/*!	
	\file    cadenaVariable.hpp
	\brief   Declaration of CadenaVariable class
	\author  
	\date    2017-12-1
	\version 1.0
*/

#ifndef _CADENAVARIABLE_HPP_
#define _CADENAVARIABLE_HPP_

#include <string>
#include <iostream>

#include "variable.hpp"

/*!	
	\namespace lp
	\brief Name space for the subject Language Processors
*/
namespace lp{

/*!	
  \class CadenaVariable
  \brief Definition of atributes and methods of CadenaVariable class
  \note  CadenaVariable Class publicly inherits from Variable class
*/
class CadenaVariable:public lp::Variable
{
/*!		
\name Private atributes of CadenaVariable class
*/
	private:
		char const *      _value;   //!< \brief Cadena value of the CadenaVariable

/*!		
\name Public methods of CadenaVariable class
*/
	public:

/*!	
	\name Constructors
*/
		
/*!		
	\brief Constructor with arguments with default values
	\note  Inline function that uses Variable's constructor as members initializer
	\param name: name of the CadenaVariable
	\param token: token of the CadenaVariable
	\param type: type of the CadenaVariable
	\param value: cadena value of the CadenaVariable
	\pre   None
	\post  A new CadenaVariable is created with the values of the parameters
	\sa   setName, setValue
*/
	inline CadenaVariable(std::string name="", int token = 0, int type = 0,  char const * cadena=""): 
 	Variable(name,token,type)
	{
		this->setValue(cadena);
	}
		
/*!		
	\brief Copy constructor
	\note  Inline function
	\param n: object of CadenaVariable class
	\pre   None
	\post  A new CadenaVariable is created with the values of an existent CadenaVariable
	\sa    setName, setValue
*/
	CadenaVariable(const CadenaVariable & n)
	{
		// Inherited methods
		this->setName(n.getName());

		this->setToken(n.getToken());

		this->setType(n.getType());
		
		// Own method
		this->setValue(n.getValue());
	}


/*!	
	\name Observer
*/
	
/*!	
	\brief  Public method that returns the value of the CadenaVariable
	\note   Función inline
	\pre    None
	\post   None
    \return Value of the CadenaVariable
	\sa		getValue
*/
	inline char const * getValue() const
	{
		return this->_value;
	}



/*!	
	\name Modifier
*/
		
/*!	
	\brief   This functions modifies the value of the CadenaVariable
	\note    Inline function
	\param   value: new value of the CadenaVariable
	\pre     None
	\post    The value of the CadenaVariable is equal to the parameter 
	\return  void
	\sa 	 setValue
*/
	inline void setValue(char const * value)
	{
	    this->_value = value;
	}



		
/*!	
	\name I/O Functions
*/
		
/*!		
	\brief Read a CadenaVariable
	\pre   None
	\post  The atributes of the CadenaVariable are modified with the read values
    \sa    write
*/
	void read();

	
/*!		
	\brief Write a CadenaVariable
	\pre   None
	\post  None
    \sa    read
*/
	void write() const;


/*!	
	\name Operators
*/
	
/*!		
	\brief  Assignment Operator
	\param  n: objectoof CadenaVariable class
	\post   The atributes of this object are equal to the atributes of the parameter
	\return Reference to this object
*/
	CadenaVariable &operator=(const CadenaVariable &n);
	

 //! \name Friend functions
/*!		
	\brief  Insertion operator
	\param  i: input stream
	\param  n: object of CadenaVariable class
	\pre    nome
	\post   The atributes of the CadenaVariable are modified with the inserted values from the input stream
	\return The input stream
*/
	friend std::istream &operator>>(std::istream &i, CadenaVariable &n);

/*!		
	\brief  Extraction operator
	\param  o: output stream
	\param  n: object of CadenaVariable class
	\pre    nome
	\post   The atributes of the CadenaVariable are written in the output stream
	\return The output stream
*/
	friend std::ostream &operator<<(std::ostream &o, CadenaVariable const &n);
	
// End of CadenaVariable class
};

// End of name space lp
}

// End of _CADENAVARIABLE_HPP_
#endif
