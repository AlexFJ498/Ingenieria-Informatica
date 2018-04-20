/*! 
   \file Medicion.hpp
   \brief Fichero de la clase Medicion: medición de una estación meteorológica
   \author Alejandro Fuerte Jurado
   \date
*/

#ifndef _MEDICION_HPP_
#define _MEDICION_HPP_

// Entrada y salida 
#include <iostream>

// Para controlar las precondiciones y postcondiciones mediante asertos
#include <cassert>

// Definición de la clase Fecha
#include "Fecha.hpp"

// Para la sobrecarga de los operadores de flujo: << y >>
using std::istream;
using std::ostream;

#define COTA_ERROR   1.0e-6 //!< Cota de error para la comparación de números reales

// Se incluye la clase Medicion dentro del espacio de nombres de la asigantura: ed
namespace ed {

//!  Definición de la clase Medicion 
class Medicion{
  //! \name Atributos privados de la clase Medicion
   private: 
		//INCLUIR LOS COMENTARIOS DE DOXYGEN
		Fecha fecha_;
		float precipitacion_;

   //! \name Funciones o métodos públicos de la clase Medicion
   public:

	//! \name Constructor de la clase Medicion

		//INCLUIR LOS COMENTARIOS DE DOXYGEN
		//Constructor parametrizado
		Medicion(Fecha fecha=Fecha(1,1,1),float precipitacion=0.0){
			#ifndef NDEBUG
				assert(precipitacion>=0.0);
			#endif

			setFecha(fecha);
			setPrecipitacion(precipitacion);

			#ifndef NDEBUG
				assert(getFecha()==fecha and
					   getPrecipitacion()==precipitacion);
			#endif
		}

		//Constructor de copia
		Medicion(const Medicion &m){
			this->setFecha(m.getFecha());
			this->setPrecipitacion(m.getPrecipitacion());

			#ifndef NDEBUG
				assert(this->getFecha()==m.getFecha() and
					   this->getPrecipitacion()==m.getPrecipitacion());
			#endif
		}

	//! \name Observadores: funciones de consulta de la clase Medicion

		//INCLUIR LOS COMENTARIOS DE DOXYGEN
		inline Fecha getFecha()const{return fecha_;}
		inline float getPrecipitacion()const{return precipitacion_;}

	//! \name Funciones de modificación de la clase Medicion

		//INCLUIR LOS COMENTARIOS DE DOXYGEN
		void setFecha(Fecha f);
		void setPrecipitacion(float p);

	//! \name Operadores
   
		//INCLUIR LOS COMENTARIOS DE DOXYGEN
		bool operator==(Medicion const & m);
		Medicion operator=(Medicion const & m);

	//! \name Funciones de lectura y escritura de la clase Medicion

		//INCLUIR LOS COMENTARIOS DE DOXYGEN
		void leerMedicion();
		void escribirMedicion();

}; // Fin de la definición de la clase Medicion

   //! \name Funciones externas de la clase Medicion: sobrecarga de los operadores de flujo

		//INCLUIR LOS COMENTARIOS DE DOXYGEN
		istream &operator>>(istream &stream,Medicion &medicion);
		ostream &operator<<(ostream &stream,Medicion const &medicion);

} // \brief Fin de namespace ed.

//  _MEDICION_HPP_
#endif 
