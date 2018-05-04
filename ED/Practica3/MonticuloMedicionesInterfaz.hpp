/*!
	\file MonticuloMedicionesInterfaz.hpp
	\brief Se define la interfaz del TAD MonticuloMediciones.
	\author Alejandro Fuerte Jurado
	\date  
*/

#ifndef _MONTICULO_MEDICIONES_INTERFAZ_HPP
#define _MONTICULO_MEDICIONES_INTERFAZ_HPP

#include "Medicion.hpp"

// COMPLETAR EL CÓDIGO E INCLUIR LOS COMENTARIOS DE DOXYGEN

namespace ed{
	// COMPLETAR EL CÓDIGO E INCLUIR LOS COMENTARIOS DE DOXYGEN
	class MonticuloMedicionesInterfaz{
		public:
			// COMPLETAR EL CÓDIGO E INCLUIR LOS COMENTARIOS DE DOXYGEN
			//Observadores
			virtual bool isEmpty()const=0;
			virtual ed::Medicion top()const=0;

			//Modificadores
			virtual void insert(Medicion const & m)=0;
			virtual void remove()=0;
	};
} // Espacio de nombres ed

#endif //  _MONTICULO_MEDICIONES_INTERFAZ_HPPs
