/*!
	\file MonticuloMediciones.hpp
	\brief Se define el TAD MonticuloMediciones.
	\author Alejandro Fuerte Jurado
	\date 
*/

#ifndef _MONTICULO_MEDICIONES_HPP
#define _MONTICULO_MEDICIONES_HPP

#include <vector>

#include <cassert>

#include "Medicion.hpp"

#include "MonticuloMedicionesInterfaz.hpp"


// COMPLETAR EL CÓDIGO E INCLUIR LOS COMENTARIOS DE DOXYGEN

namespace ed{

// COMPLETAR EL CÓDIGO E INCLUIR LOS COMENTARIOS DE DOXYGEN

class MonticuloMediciones : public MonticuloMedicionesInterfaz{
	private:

		//! \name Atributos privados de la clase MonticuloMediciones
		// COMPLETAR EL CÓDIGO E INCLUIR LOS COMENTARIOS DE DOXYGEN
		std::vector<Medicion> vector_;


		//! \name Métodos privados de la clase MonticuloMediciones
		// COMPLETAR EL CÓDIGO E INCLUIR LOS COMENTARIOS DE DOXYGEN
		Medicion getElement(int i)const{
			#ifndef NDEBUG
				assert(i>=0 and i<size());
			#endif

			std::vector::<Medicion>::iterator it;
			for(it=vector_.begin();it!=vector_.end();it++){
				if(it==i){
					return it;
				}
			}
		}
		void setElement(int i,Medicion m){
			#ifndef NDEBUG
				assert(i>=0 and i<size());
			#endif

			std::vector::<Medicion>::iterator it;
			for(it=vector_.begin();it!=vector_.end();it++){
				if(it==i){
					it.setFecha(m.getFecha());
					it.setPrecipitacion(m.getPrecipitacion());
				}
			}

			#ifndef NDEBUG
				assert(this->getElement(i)==m);
			#endif
		}

	  /////////////////////////////////////////////////////////////////////////////////////

	//! \name Métodos públicos de la clase MonticuloMediciones
	public:

		//! \name Constructor

		// COMPLETAR EL CÓDIGO E INCLUIR LOS COMENTARIOS DE DOXYGEN


		//! \name Observadores

		// COMPLETAR EL CÓDIGO E INCLUIR LOS COMENTARIOS DE DOXYGEN

		////////////////////////////////////////////////////////////

		//! \name Operaciones de modificación

		// COMPLETAR EL CÓDIGO E INCLUIR LOS COMENTARIOS DE DOXYGEN


		//! \name Operadores
   
		// COMPLETAR
 

		////////////////////////////////////////////////////////////////////

		//! \name Función de escritura

		// COMPLETAR

	}; // Clase MonticuloMediciones

} // Espacio de nombres ed


#endif // _MONTICULO_MEDICIONES_HPP
