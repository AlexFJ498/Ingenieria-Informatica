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
		int getLeftChild(int i){
			#ifndef NDEBUG
				assert(i>=0);
			#endif

			int indice=2*i+1;
			return indice;
		}
		int getRightChild(int i){
			#ifndef NDEBUG
				assert(i>=0);
			#endif

			int indice=2*i+2;
			return indice;
		}
		int getParent(int i){
			#ifndef NDEBUG
				assert(i>=1);
			#endif

			int indice=(i-1)/2;
		}
		void shiftUp(int i){
			#ifndef NDEBUG
				assert(i>=0 and i<size());
			#endif

			//Si no es la cima y el elemento actual es mayor que el padre
			if(i>0 && getElement(i)>getElement(getParent(i))){
				Medicion aux=getElement(i);
				setElement(i,getElement(getParent(i)));
				setElement(getElement(getParent(i)),aux);
				shiftUp(getParent(i));
			}

			#ifndef NDEBUG
				assert(if(i>0{getElement(i)<=getElement(getParent(i))
					      if(getLeftChild(i)!=i){
 						     getElement(i)>=getElement(getLeftChild(i));
						  }
						  if(getRightChild(i)!=i){
							 getElement(i)>=getElement(getLeftChild(i));
						  }
					   }	   
			    );
			#endif
		}
		void shiftDown(int i){
			#ifndef NDEBUG
				assert(i>=0 and i<size());
			#endif

			int n=i;
			int lC=getLeftChild(i);
			int rC=getRightChild(i);
			std::vector<Medicion>::iterator it;

			//Si el hijo izquierdo tiene menor íncice que el último y su elemento es mayor que el actual
			if(lC<it.vector_.end() && getElement(lC)>getElement(n){
				n=lC;
			}
			if(rC<it.vector_.end() && getElement(rC)>getElement(n){
				n=rC;
			}
			if(i<>n){
				Medicion aux=getElement(i);
				setElement(i,getElement(n));
				setElement(getElement(n),aux);
			}

			#ifndef NDEBUG
				assert(if(i>0{getElement(i)<=getElement(getParent(i))
					      if(getLeftChild(i)!=i){
 						     getElement(i)>=getElement(getLeftChild(i));
						  }
						  if(getRightChild(i)!=i){
							 getElement(i)>=getElement(getLeftChild(i));
						  }
					   }	   
			    );
			#endif
		}

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
