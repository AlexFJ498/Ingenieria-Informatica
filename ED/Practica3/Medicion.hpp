/*! 
   \file Medicion.hpp
   \brief Fichero de la clase Medicion: medición de una estación meteorológica
   \author Alejandro Fuerte Jurado
   \date 07-05-2018
*/

#ifndef _MEDICION_HPP_
#define _MEDICION_HPP_

//Entrada y salida 
#include <iostream>

//Para controlar las precondiciones y postcondiciones mediante asertos
#include <cassert>

//Definición de la clase Fecha
#include "Fecha.hpp"

//Para la sobrecarga de los operadores de flujo: << y >>
using std::istream;
using std::ostream;

#define COTA_ERROR   1.0e-6 //!< Cota de error para la comparación de números reales

// Se incluye la clase Medicion dentro del espacio de nombres de la asigantura: ed
namespace ed{

//!  Definición de la clase Medicion 
class Medicion{
  //! \name Atributos privados de la clase Medicion
   private: 
		/*
		\brief Atributo de clase fecha
		*/ 
		Fecha fecha_;

		/*
		\brief Atributo de tipo flotante
		*/
		float precipitacion_;

   //! \name Funciones o métodos públicos de la clase Medicion
   public:

	//! \name Constructor de la clase Medicion

		/*
		\brief Constructor parametrizado
		\note Funcion inline
		\warning Parámetros con valores por defecto
		\param fecha: fecha de la medición (tipo Fecha)
		\param precipitacion: valor de la precipitación de la medición (tipo float)
		\pre precipitacion>=0.0
		\post getFecha()==fecha and getPrecipitacion()==precipitacion
		*/
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

		/*
		\brief Constructor de copia
		\note Funcion inline
		\note Parámetro constante
		\param m: la medición que se desea copiar (tipo Medicion)
		\pre Ninguna
		\post this->getFecha()==m.getFecha() and this->getPrecipitacion()==m.getPrecipitacion()
		*/
		Medicion(const Medicion &m){
			this->setFecha(m.getFecha());
			this->setPrecipitacion(m.getPrecipitacion());

			#ifndef NDEBUG
				assert(this->getFecha()==m.getFecha() and
					   this->getPrecipitacion()==m.getPrecipitacion());
			#endif
		}

	//! \name Observadores: funciones de consulta de la clase Medicion

		/*
		\brief Observador de la fecha de la medición
		\note Funcion inline
		\return fecha_: fecha de la medición
		\pre Ninguna
		\post Ninguna
		*/
		inline Fecha getFecha()const{return fecha_;}

		/*
		\brief Observador de la precipitación de la medición
		\note Funcion inline
		\return precipitacion_: precipitación de la medición
		\pre Ninguna
		\post Ninguna
		*/
		inline float getPrecipitacion()const{return precipitacion_;}

	//! \name Funciones de modificación de la clase Medicion

		/*
		\brief Modificador de la fecha de la medición
		\pre Ninguna
		\post this->getFecha()==f
		*/
		void setFecha(Fecha f);

		/*
		\brief Modificador de la precipitación de la medición
		\pre p>=0.0
		\post this->getPrecipitacion()==p
		*/
		void setPrecipitacion(float p);

	//! \name Operadores
   
		/*!
		\brief Operador comparador de igualdad
		\param Medicion objeto pasado por referencia
		\note Medición constante
		\pre Ninguna
		\post this->getFecha()==m.getFecha()
		*/
		bool operator==(Medicion const & m)const;

		/*!
		\brief Operador de asignación
		\param Medicion objeto pasado por referencia
		\note Medición constante
		\pre Ninguna
		\post this->getFecha()==m.getFecha() and this->getPrecipitacion()==m.getPrecipitacion()
		*/
		Medicion operator=(Medicion const & m);

	//! \name Funciones de lectura y escritura de la clase Medicion

		/*
		\brief Función de lectura por pantalla de una medición
		\pre Ninguna
		\post Ninguna
		*/
		void leerMedicion();

		/*
		\brief Función de escritura por pantalla de una medición
		\pre Ninguna
		\post Ninguna
		*/
		void escribirMedicion();

}; //Fin de la definición de la clase Medicion

   //! \name Funciones externas de la clase Medicion: sobrecarga de los operadores de flujo

		/*
		\brief Sobrecarga del operador de salida <<
		\param stream: Flujo de salida
		\param medicion: Medición objeto
		\pre Ninguna
		\post Ninguna
		*/
		istream &operator>>(istream &stream,Medicion &medicion);

		/*
		\brief Sobrecarga del operador de entrada >>
		\param stream: Flujo de entrada
		\param medicion: Medición objeto
		\pre Ninguna
		\post Ninguna
		*/
		ostream &operator<<(ostream &stream,Medicion const &medicion);

} // \brief Fin de namespace ed.

//  _MEDICION_HPP_
#endif 
