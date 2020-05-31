/*!	
	\file  Provincia.hpp
	\brief Definición de la clase Provincia
	\author  
	\date  
	\version 

*/

#ifndef _PROVINCIA_HPP_
#define _PROVINCIA_HPP_

// Para comprobar las pre y post condiciones
#include <cassert>
#include <iostream>
#include <cstring>

#include "ListaDoblementeEnlazadaOrdenadaMunicipios.hpp"


// DEBES COMPLETAR O MODIFICAR EL CÓDIGO DE LA CLASE Provincia

// DEBES COMPLETAR LOS COMENTARIOS DE DOXYGEN

// IMPORTANTE
// Se incluyen los prototipos de las funciones virtuales que hay que redefinir
// Hay que incluir los prototipos de las demás funciones


/*!	
	\namespace ed
	\brief Espacio de nombres para la Provincia Estructuras de Datos

*/
namespace ed{
/*!	

  \class Provincia
  \brief Definición de la clase Provincia

*/
class Provincia
{
	//!	\name Métodos públicos de la clase Provincia

	private:
		std::string      _nombre;     //!<  \brief Nombre de la Provincia
		int              _codigo;	  //!<  \brief Código de la Provincia

	  	ed::ListaDoblementeEnlazadaOrdenadaMunicipios _listaMunicipios; //!<  \brief Lista de municipios de la Provincia


	/////////////////////////////////////////////////////////////////////

	//!	\name  Métodos públicos de la clase Provincia

  public: 

	//!	\name Constructor
Provincia(std::string n="", int c=0)
: _nombre(n), _codigo(c) {};
	/*Provincia(std::string n="",int c=0){
		_nombre=n;
		_codigo=c;
		#ifndef NDEBUG
			assert(this->getNombre()==n and
				   this->getCodigo()==c and
				   this->hayMunicipios()==false);
		#endif
	}*/

	/////////////////////////////////////////////////////////////////////

	//!	\name Observadores
	inline std::string getNombre()const{return _nombre;}
	inline int getCodigo()const{return _codigo;}
	bool hayMunicipios()const;
	int getNumeroMunicipios()const{return _listaMunicipios.nItems();}
	bool existeMunicipio(std::string n);
	Municipio getMunicipio(std::string n);
	int getTotalHombres();
	int getTotalMujeres();

	/////////////////////////////////////////////////////////////////////

	//!	\name Modificadores
	inline void setNombre(std::string n){
		_nombre=n;
		#ifndef NDEBUG
			assert(this->getNombre()==n);
		#endif	
	}
	inline void setCodigo(int c){
		_codigo=c;
		#ifndef NDEBUG
			assert(this->getCodigo()==c);
		#endif
	}
	void insertarMunicipio(const Municipio &m);
	void borrarMunicipio(std::string n);
	void borrarTodosLosMunicipios();


	/////////////////////////////////////////////////////////////////////

	//! \name Función de escritura de la clase Provincia
	void escribirMunicipios();


	/////////////////////////////////////////////////////////////////////

	//! Operaciones con ficheros
	bool cargarFichero(std::string n);
	bool grabarFichero(std::string n);

}; //Fin de la clase  Provincia


} // Fin del espacio de nombres ed

#endif // _PROVINCIA_HPP_
