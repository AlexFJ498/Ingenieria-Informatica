/*!
	\file  Vertex.hpp
	\brief Clase para un vértice con un punto 2D como data
*/

#ifndef _VERTEX_HPP_
#define _VERTEX_HPP_

#include <iostream>
#include <cstdlib>
#include <cstring>

#include "Point2D.hpp"

namespace ed{

//! Definición de la clase Vertex
class Vertex{
	private:
		int label_;    //!< Etiqueta del vértice
		Point2D data_; //!< Punto 2D del vértice

	public:
		/*!
			\brief    Constructor de la clase Vertex.hpp
			\param l: Etiqueta (tipo int)
			\param d: Punto (tipo Point2D)
			\note     Parámetros con valores predeterminados de 0
		*/
		Vertex(Point2D d=Point2D(0,0),int l=0){
			label_=l;
			data_=d;
		}

		/*!
			\brief  Observador de la etiqueta
			\note   Función inline
			\note   Función constante
			\return Etiqueta (tipo int)
		*/
		inline int getLabel()const{return label_;}

		/*!
			\brief  Observador de la data
			\note   Función inline
			\note   Función constante
			\return Punto (tipo Point2D)
		*/
		inline Point2D getData()const{return data_;}

		/*!
			\brief    Modificador de la etiqueta
			\note     Función inline
			\param l: Etiqueta (tipo int)
		*/
		inline void setLabel(int l){label_=l;}

		/*!
			\brief    Modificador de la data
			\note     Función inline
			\param d: Punto (tipo Point2D)
		*/
		inline void setData(Point2D const &d){data_=d;}

		/*!
			\brief    Operador de asignación
			\note     Función inline
			\param v: Nuevo Vértice
			\return   Vértice actualizado
		*/
		inline Vertex operator=(Vertex const & v){
			this->setLabel(v.getLabel());
			this->setData(v.getData());

			return *this;
		}

		/*!
			\brief    Operador de igualdad
			\note     Función inline
			\param v: Vértice a comparar
			\return   true si son iguales, false si no
		*/
		inline bool operator==(Vertex const & v)const{
			if(this->getLabel()==v.getLabel() && this->getData()==v.getData()){
				return true;
			}
			return false;
		}
		
};

		std::ostream &operator<<(std::ostream &stream,Vertex const &v);
		std::istream &operator>>(std::istream &stream,Vertex const &v);
} // \brief Fin de namespace ed.

#endif
