/*!
	\file Edge.hpp
	\brief Constructor de un lado con dos vértices
*/

#ifndef _EDGE_HPP_
#define _EDGE_HPP_

#include <cassert>
#include <iostream>

#include "Vertex.hpp"

namespace ed{

//! Definición de la clase Edge
class Edge{
	private:
		Vertex v1_;   //!< Vértice 1
		Vertex v2_;   //!< Vértice 2
		double data_; //!< Peso del lado

	public:
		/*!
			\brief     Constructor de la clase Edge
			\param v1: Vértice 1 (tipo Vertex)
			\param v2: Vértice 2 (tipo Vertex)
			\param d:  Peso del lado (tipo double)
		*/
		Edge(Vertex v1,Vertex v2,double d=0.0){
			v1_=v1;
			v2_=v2;
			data_=d;
		}

		/*!
			\brief  Observador del primer vértice
			\note   Función inline
			\note   Función constante
			\return Vértice 1 (tipo Vertex)
		*/
		inline Vertex getFirst()const{
			#ifndef NDEBUG
				assert(this->other(v1_)==v2_);
			#endif

			return v1_;
		}

		/*!
			\brief  Observador del segundo vértice
			\note   Función inline
			\note   Función constante
			\return Vértice 2 (tipo Vertex)
		*/
		inline Vertex getSecond()const{
			#ifndef NDEBUG
				assert(this->other(v2_)==v1_);
			#endif
			return v2_;
		}

		/*!
			\brief  Observador del peso del lado
			\note   Función inline
			\note   Función constante
			\return Peso (tipo double)
		*/
		inline double getData()const{return data_;}

		/*!
			\brief    Comprueba si un vértice es parte del lado
			\note     Función constante
			\param v: Vértice a comprobar (tipo Vertex)
			\return   True si el vértice es parte del lado, false si no
		*/
		bool has(Vertex const &v)const;

		/*!
			\brief    Devuelve el otro vértice del lado
			\note     Función constante
			\param v: Vértice del que sacar el segundo (tipo Vertex)
			\return   Vértice (tipo Vertex)
		*/
		Vertex other(Vertex const &v)const;

		/*!
			\brief    Modificador del peso del lado
			\note     Función inline
			\param d: Nuevo peso (tipo double)
		*/
		inline void setData(double d){data_=d;}

};
} // \brief Fin de namespace ed.

#endif
