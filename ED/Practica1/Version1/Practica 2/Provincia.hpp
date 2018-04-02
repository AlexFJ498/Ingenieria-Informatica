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
#include "Municipio.hpp"
#include <string>
#include <cstdlib>

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
class Provincia{
	//!	\name Métodos públicos de la clase Provincia

	private:
		std::string      nombre_;     //!<  \brief Nombre de la Provincia
		int              codigo_;	  //!<  \brief Código de la Provincia

	  	ed::ListaDoblementeEnlazadaOrdenadaMunicipios listaMunicipios_; //!<  \brief Lista de municipios de la Provincia


	/////////////////////////////////////////////////////////////////////

	//!	\name  Métodos públicos de la clase Provincia

  public: 

	//!	\name Constructor
		Provincia(std::string n,int c){
			setNombre(n);
			setCodigo(c);

		#ifndef NDEBUG
			assert((getNombre()==nombre_) and
				   (getCodigo()==codigo_) and
				   (hayMunicipios()==false));
		#endif
		}
	/////////////////////////////////////////////////////////////////////

	//!	\name Observadores
		inline std::string getNombre(){return nombre_;}
		inline int getCodigo(){return codigo_;}
		bool hayMunicipios();
		inline int getNumeroMunicipios(){return sizeof(listaMunicipios_);}
		bool existeMunicipio(std::string n);
		Municipio getMunicipio(std::string n);
		int getTotalHombres();
		int getTotalMujeres();
		int getTotalHabitantes();
	/////////////////////////////////////////////////////////////////////

	//!	\name Modificadores
		void setNombre(std::string n);
		void setCodigo(int c);
		void insertarMunicipio(Municipio m);
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
