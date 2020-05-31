
/*!
  \file   funcionesAuxiliares.hpp
  \brief  Funciones auxiliares para el programa principal de la práctica 1
  \author 
  \date  
*/

#ifndef _FUNCIONESAUXILIARES_HPP_
#define _FUNCIONESAUXILIARES_HPP_

#include "Vector3D.hpp"


namespace ed
{
	/*! 
		\brief   Muestra el menú del programa principal 
		\return  Devuelve el número de opción elegido
	*/
	int menu();

	// COMPLETAR LOS COMENTARIOS DE DOXYGEN
	/*!
		\brief Funcion que lee los vectores pasados por parametro
		\param u: vector listo para leer (tipo Vector3D)
		\param v: vector listo para leer (tipo Vector3D)
		\param w: vector listo para leer (tipo Vector3D)
	*/
	void leerVectores(ed::Vector3D &u, ed::Vector3D &v, ed::Vector3D &w);

	// COMPLETAR LOS COMENTARIOS DE DOXYGEN
	/*!
		\brief Funcion que escribe los vectores pasados por parametro
		\param u: vector listo para escribir (tipo Vector3D)
		\param v: vector listo para escribir (tipo Vector3D)
		\param w: vector listo para escribir (tipo Vector3D)
	*/
	void escribirVectores(ed::Vector3D const &u, ed::Vector3D const &v, ed::Vector3D const &w);


	// COMPLETAR LOS COMENTARIOS DE DOXYGEN
	/*!
		\brief Funcion que muestra el funcionamiento de los observadores de los vectores pasados por parametro
		\param u: vector listo para mostrar los observadores (tipo Vector3D)
		\param v: vector listo para mostrar los observadores (tipo Vector3D)
		\param w: vector listo para mostrar los observadores (tipo Vector3D)
	*/
	void observadoresDeVectores(ed::Vector3D const &u, ed::Vector3D const &v);

	// COMPLETAR LOS COMENTARIOS DE DOXYGEN

	/*!
		\brief Funcion que muestra el funcionamiento de los modificadores de los vectores pasados por parametro
		\param u: vector listo para mostrar los modificadores (tipo Vector3D)
		\param v: vector listo para mostrar los modificadores (tipo Vector3D)
		\param w: vector listo para mostrar los modificadores (tipo Vector3D)
	*/
	void modificarVector(ed::Vector3D &u, ed::Vector3D const &v, double k);

	// COMPLETAR LOS COMENTARIOS DE DOXYGEN
	/*!
		\brief Funcion que muestra el funcionamiento del producto escalar en los vectores pasados por parametro
		\param u: vector listo para realizar el producto escalar (tipo Vector3D)
		\param v: vector listo para realizar el producto escalar (tipo Vector3D)
		\param w: vector listo para realizar el producto escalar (tipo Vector3D)
	*/
	void mostrarProductoEscalar(ed::Vector3D const &u, ed::Vector3D const &v); 

	// COMPLETAR LOS COMENTARIOS DE DOXYGEN
	/*!
		\brief Funcion que muestra el funcionamiento del producto vectorial en los vectores pasados por parametro
		\param u: vector listo para realizar el producto vectorial (tipo Vector3D)
		\param v: vector listo para realizar el producto vectorial (tipo Vector3D)
		\param w: vector listo para realizar el producto vectorial (tipo Vector3D)

	*/
	void mostrarProductoVectorial(ed::Vector3D const &u, ed::Vector3D const &v);

	// COMPLETAR LOS COMENTARIOS DE DOXYGEN
	/*!
		\brief Funcion que muestra el funcionamiento del producto mixto en los vectores pasados por parametro
		\param u: vector listo para realizar el producto mixto (tipo Vector3D)
		\param v: vector listo para realizar el producto mixto (tipo Vector3D)
		\param w: vector listo para realizar el producto mixto (tipo Vector3D)
	*/
	void mostrarProductoMixto(ed::Vector3D const &u, ed::Vector3D const &v, ed::Vector3D const &w);

	// COMPLETAR LOS COMENTARIOS DE DOXYGEN
	/*!
		\brief Funcion que muestra el funcionamiento de los operadores de los vectores pasados por parametro
		\param u: vector listo para mostrar sus operadores (tipo Vector3D)
		\param v: vector listo para mostrar sus operadores (tipo Vector3D)
		\param w: vector listo para mostrar sus operadores (tipo Vector3D)

	*/
	void mostrarOperadores(ed::Vector3D const &u, ed::Vector3D const &v, ed::Vector3D &w,  double k);



} // Fin del espacio de nombre de la asignatura: ed

// Fin de _FUNCIONESAUXILIARES_HPP_
#endif

