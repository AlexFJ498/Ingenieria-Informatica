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

namespace ed{

// COMPLETAR EL CÓDIGO E INCLUIR LOS COMENTARIOS DE DOXYGEN

class MonticuloMediciones : public MonticuloMedicionesInterfaz{
	private:

		//! \name Atributos privados de la clase MonticuloMediciones
		/*
		\brief Vector de la STL
		*/
		std::vector<Medicion> vector_;


		//! \name Métodos privados de la clase MonticuloMediciones

		/*
		\brief Devolver elemento del montículo
		\note Función constante
		\param i: Posición del elemento (tipo int)
		\pre i>=0 and i<=size()
		\post Ninguna
		\return Medicion
		*/
		Medicion getElement(int i)const;

		/*
		\brief Asignar valor a un elemento del montículo
		\param i: Posición del elemento (tipo int)
		\param m: Medición objeto (tipo Medicion)
		\pre i>=0 and i<size()
		\post this->getElement(i)==m
		*/
		void setElement(int i,Medicion m);

		/*
		\brief Devolver hijo izquierdo de un elemento
		\note Función constante
		\param i: Posición del elemento (tipo int)
		\pre i>=0
		\post Ninguna
		\return entero
		*/
		int getLeftChild(int i)const;

		/*
		\brief Devolver hijo derecho de un elemento
		\note Función constante
		\param i: Posición del elemento (tipo int)
		\pre i>=0
		\post Ninguna
		\return entero
		*/
		int getRightChild(int i)const;
		
		/*
		\brief Devolver padre de un elemento
		\note Función constante
		\param i: Posición del elemento (tipo int)
		\pre i>=1
		\post Ninguna
		\return entero
		*/
		int getParent(int i)const;

		/*
		\brief Mover nodo hacia arriba según ordenación
		\param i: Posición del elemento (tipo int)
		\pre i>0 and i<size()
		*/
		void shiftUp(int i);

		/*
		\brief Mover nodo hacia abajo según ordenación
		\param i: Posición del elemento (tipo int)
		\pre i>=0 and i<size()
		*/
		void shiftDown(int i);

		/*
		\brief Comprobar si existe un elemento en el montículo
		\param m: Medición objeto (tipo Medicion)
		\pre Ninguna
		\post Ninguna
		\return booleana
		*/
		bool has(Medicion m);

	  /////////////////////////////////////////////////////////////////////////////////////

	//! \name Métodos públicos de la clase MonticuloMediciones
	public:

		//! \name Constructor

		/*
		\brief Constructor del montículo
		\pre Ninguna
		\post Ninguna
		*/
		MonticuloMediciones(){
			removeAll();			
		}

		//! \name Observadores
		
		/*
		\brief Comprobar si el montículo está vacío
		\pre Ninguna
		\post Ninguna
		\note Función constante
		\return booleana
		*/
		bool isEmpty()const;

		/*
		\brief Devolver el tamaño del montículo
		\pre Ninguna
		\post Ninguna
		\note Función constante
		\return entero
		*/
		int size()const;

		/*
		\brief Devolver la medición que se encuentra en el top del montículo
		\pre isEmpty()==false
		\post aux==getElement(0)
		\note Función constante
		\return Medicion
		*/
		Medicion top()const;
		////////////////////////////////////////////////////////////

		//! \name Operaciones de modificación
		
		/*
		\brief Insertar una medición en el montículo
		\param m: Medición objeto (tipo Medicion)
		\pre Ninguna
		\post isEmpty()==false and has(m)==true
		*/
		void insert(Medicion m);

		/*
		\brief Borrar el top del montículo
		\pre isEmpty()==false
		\post Ninguna
		*/
		void remove();

		/*
		\brief Borrar todas las mediciones del montículo
		\pre Ninguna
		\post isEmpty()==true
		*/
		void removeAll();

		/*
		\brief Modificar el top de la medición
		\param m: Medición objeto (tipo Medicion)
		\pre isEmpty()==false
		\post has(m)==true
		*/
		void modify(Medicion m);

		//! \name Operadores
		/*
		\brief Operador de asignación de montículos
		\param m: Montículo objeto (tipo MonticuloMediciones)
		\return MonticuloMediciones
		*/
 		MonticuloMediciones operator=(MonticuloMediciones m){
			int i=0;
			MonticuloMediciones aux=*this;
			while(i<aux.size()){
				aux.setElement(i,getElement(i));
			}

			return aux;
		}

		////////////////////////////////////////////////////////////////////

		//! \name Función de escritura
		/*
		\brief Imprimir el montículo
		\note Función inline
		*/
		void print(){
			if(size()==0){
				std::cout<<"Monticulo vacio"<<std::endl;
				return;
			}
			std::cout<<"LISTA DE MEDICIONES"<<std::endl;
			std::cout<<"-------------------"<<std::endl;

			int i=0;
			while(i<=size()-1){
				std::cout<<i+1<<": "<<getElement(i);
				i++;
			}
		}

	}; // Clase MonticuloMediciones

} // Espacio de nombres ed

#endif // _MONTICULO_MEDICIONES_HPP

