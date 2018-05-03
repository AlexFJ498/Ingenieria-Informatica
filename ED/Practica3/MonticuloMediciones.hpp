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
		Medicion getElement(int i)const;
		void setElement(int i,Medicion m);
		int getLeftChild(int i)const;
		int getRightChild(int i)const;
		int getParent(int i)const;
		void shiftUp(int i);
		void shiftDown(int i);
		bool has(Medicion m);

	  /////////////////////////////////////////////////////////////////////////////////////

	//! \name Métodos públicos de la clase MonticuloMediciones
	public:

		//! \name Constructor

		// COMPLETAR EL CÓDIGO E INCLUIR LOS COMENTARIOS DE DOXYGEN
		MonticuloMediciones(){
			std::vector<Medicion> constructor;
			
		}

		//! \name Observadores
		// COMPLETAR EL CÓDIGO E INCLUIR LOS COMENTARIOS DE DOXYGEN
		bool isEmpty()const;
		int size()const;
		Medicion top()const;
		////////////////////////////////////////////////////////////

		//! \name Operaciones de modificación
		// COMPLETAR EL CÓDIGO E INCLUIR LOS COMENTARIOS DE DOXYGEN
		void insert(Medicion m);
		void remove();
		void removeAll();
		void modify(Medicion m);

		//! \name Operadores
		// COMPLETAR
 		MonticuloMediciones operator=(MonticuloMediciones m){
			/*#ifndef NDEBUG
				assert(*this!=m);
			#endif*/

			int i=0;
			MonticuloMediciones aux=*this;
			while(i<aux.size()){
				aux.setElement(i,getElement(i));
			}

			return aux;
		}

		////////////////////////////////////////////////////////////////////

		//! \name Función de escritura
		// COMPLETAR
		void print(){
			std::cout<<"LISTA DE MEDICIONES"<<std::endl;
			std::cout<<"-------------------"<<std::endl;

			int i=0;
			while(i!=size()-1){
				std::cout<<i<<": "<<getElement(i)<<std::endl;
			}
		}

	}; // Clase MonticuloMediciones

} // Espacio de nombres ed

#endif // _MONTICULO_MEDICIONES_HPP
