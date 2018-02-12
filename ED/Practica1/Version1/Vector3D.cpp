/*! 
   \file Vector3D.cpp
   \brief Fichero que contiene el código de las funciones de la clase Vector3D
*/


// Ficheros de cabecera
#include <iostream>

// Para usar sqrt, acos
#include <cmath>

// Para controlar las pre y post condiciones mediante asertos
#include <cassert>

#include "Vector3D.hpp"

// OBSERVADORES

// COMPLETAR
double ed::Vector3D::get1()const{
	return v1_;
}

double ed::Vector3D::get2()const{
	return v2_;
}

double ed::Vector3D::get3()const{
	return v3_;
}

double ed::Vector3D::modulo(){
	double modulo;
	modulo=sqrt(v1_*v1_+v2_*v2_+v3_*v3_);

	#ifndef NDEBUG
		assert(modulo=sqrt(get1()*get1()+get2()*get2()+get3()*get3()));
	#endif
	return modulo;
}

double ed::Vector3D::angulo(Vector3D v){
	double angulo;
	angulo=acos(dotProduct(v)/(modulo()*v.modulo()));

	#ifndef NDEBUG
		assert(angulo=acos(dotProduct(v)/modulo()*v.modulo()));
	#endif
	return angulo;
}

double ed::Vector3D::alfa(){
	#ifndef NDEBUG
		assert(modulo()>0);
	#endif

	double alfa;
	Vector3D v(1,0,0);
	alfa=angulo(v);

	#ifndef NDEBUG
		assert(alfa=angulo(v);
	#endif
	return alfa;
}

double ed::Vector3D::beta(){
	#ifndef NDEBUG
		assert(modulo()>0);
	#endif

	double beta;
	Vector v(0,1,0);
	beta=angulo(v);

	#ifndef NDEBUG
		assert(beta=angulo(v));
	#endif
	return beta;
}

double ed::Vector3D::gamma(){
	#ifndef NDEBUG
		assert(modulo()>0);
	#endif

	double gamma;
	Vector3D v(0,0,1);
	gamma=angulo(v);

	#ifndef NDEBUG
		assert(gamma=angulo(v));
	#endif
	return gamma;
}

double ed::Vector3D::dotproduct(Vector3D v){
	double producto;
	producto=v1_*v.get1()+v2_*get2()+v3_*get3();

	#ifndef NDEBUG
		assert(producto=get1()*v.get1()+get2()*v.get2()+get3()*v.get3());
	#endif
	return producto;
}

Vector3D ed::Vector3D::crossProduct(Vector3D v){
	double producto;
	producto=
}

////////////////////////////////////////////////////////////////

// MODIFICADORES

// COMPLETAR



////////////////////////////////////////////////////////////////////////////////

// OPERADORES

// COMPLETAR



////////////////////////////////////////////////////////////////////////////////

// FUNCIONES DE LECTURA Y ESCRITURA

// COMPLETAR


////////////////////////////////////////////////////////////////////////////////


// Se incluyen los operadores sobrecargados dentro del espacio de nombres de ed

namespace ed{


// Producto "por un" escalar (prefijo): k * v
ed::Vector3D & operator* (double k, ed::Vector3D const & objeto)
{
	ed::Vector3D *vectorResultado = new ed::Vector3D();

	// COMPLETAR

	return *vectorResultado;
}


// Sobrecarga del operador de salida
// Se escriben por pantalla las coordenadas del vector 3D  de la forma (v1, v2, v3)
ostream &operator<<(ostream &stream, ed::Vector3D const &objeto)
{
	// COMPLETAR

  return stream;
}

// Sobrecarga del operador de entrada
istream &operator>>(istream &stream, ed::Vector3D &objeto)
{
  // COMPLETAR

  return stream;
} 

} // Fin del espacio de nombres ed
