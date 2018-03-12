/*!	
	\file  Provincia.hpp
	\brief Definición de la clase Provincia
	\author Alejandro Fuerte Jurado
	\date  
	\version 1.0

*/

#ifndef _PROVINCIA_HPP_
#define _PROVINCIA_HPP_

// Para comprobar las pre y post condiciones
#include <cassert>

#include <string>
#include "municipio.h"

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
		std::string      nombre_;     //!<  \brief Nombre de la Provincia
		int              codigo_;	  //!<  \brief Código de la Provincia

	  	ed::listaDoblementeEnlazada listaMunicipios_; //!<  \brief Lista de municipios de la Provincia


	/////////////////////////////////////////////////////////////////////

	//!	\name  Métodos públicos de la clase Provincia

  public: 

	//!	\name Constructor
		Provincia(std::string n,int c){
			nombre_=n;
			codigo_=c;

		#ifndef NDEBUG
			assert(getNombre()==nombre_ and
				   getCodigo()==codigo_ and
				   hayMunicipios()==false);
		#endif
		}
	/////////////////////////////////////////////////////////////////////

	//!	\name Observadores
		inline std::string getNombre(){return nombre_;}
		inline std::string getCodigo(){return codigo_;}
		bool hayMunicipios();
		inline int getNumeroMunicipios(){return sizeof(listaMunicipios_);}
		bool existeMunicipio(std::string n);
		listaDoblementeEnlazada getMunicipio(std::string n);
		int getTotalHombres();
		int getTotalMujeres();
		int getTotalHabitantes();
	/////////////////////////////////////////////////////////////////////

	//!	\name Modificadores
		void setNombre(std::string n);
		void setCodigo(int c);
		void insertarMunicipio(Municipio)

	/////////////////////////////////////////////////////////////////////

	//! \name Función de escritura de la clase Provincia



	/////////////////////////////////////////////////////////////////////

	//! Operaciones con ficheros


}; //Fin de la clase  Provincia


} // Fin del espacio de nombres ed

#endif // _PROVINCIA_HPP_
