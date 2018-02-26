/*! 
   \file Vector3D.hpp
   \brief Fichero de definición de la clase Vector3D: vector libre de tres dimensiones
*/

#ifndef _VECTOR3D_HPP_
#define _VECTOR3D_HPP_

// Entrada y salida 
#include <iostream>

// Para usar abs
#include <cmath>

// Para controlar las pre y post condiciones mediante asertos
#include <cassert>

// COMPLETAR, SI ES PRECISO


// Para la sobrecarga de los operadores de flujo: << y >>
using std::istream;
using std::ostream;

#define COTA_ERROR   1.0e-6 //!< Cota de error para la comparación números reales


// Se incluye la clase Vector3D dentro del espacio de nombre de la asigantura: ed
namespace ed {

//!  Definición de la clase Vector3D:  \f$ \vec{v} = (v_1, v_2, v_3) = v_1 \vec{i} + v_2 \vec{j} + v_3 \vec{k} \f$ 
class Vector3D
{
  //! \name Atributos privados de la clase Vector3D
   private: 

	// COMPLETAR
	double v1_;
	double v2_;
	double v3_;

   //! \name Funciones o métodos públicos de la clase Vector3D
   public:

	//! \name Constructores de la clase Vector3D

	// COMPLETAR
	Vector3D(){
		v1_=0;
		v2_=0;
		v3_=0;

		#ifndef NDEBUG
			assert(get1()==0 and
				   get2()==0 and
				   get3()==0);
		#endif
	}

	Vector3D(double v1,double v2,double v3){
		v1_=v1;
		v2_=v2;
		v3_=v3;

		#ifndef NDEBUG
			//Postcondición
			assert(get1()==v1_ and 
				   get2()==v2_ and 
				   get3()==v3_);
		#endif
	}

	Vector3D(Vector3D const &v){
		v1_=v.v1_;
		v2_=v.v2_;
		v3_=v.v3_;

		#ifndef NDEBUG
			assert(get1()==v.get1() and
				   get2()==v.get2() and
				   get3()==v.get3());
		#endif
	}
	//! \name Observadores: funciones de consulta de Vector3D

	// COMPLETAR
	double get1()const;
	double get2()const;
	double get3()const;
	double modulo()const;
	double angulo(Vector3D const &v)const;
	double alfa()const;
	double beta()const;
	double gamma()const;
	double dotProduct(Vector3D const &v)const;
	Vector3D crossProduct(Vector3D const &v)const;
	double productoMixto(Vector3D const &v,Vector3D const &w)const;

	//! \name Modificadores: funciones de modificación de Vector3D

	// COMPLETAR
	void set1(double v);
	void set2(double v);
	void set3(double v);
	void sumConst(double k);
	void sumVect(Vector3D const &v);
	void multConst(double k);
	void multVect(Vector3D const &v);

    //! \name Operadores de la clase
   
	// COMPLETAR COMENTARIOS DE DOXYGEN
	Vector3D & operator=(Vector3D const &objeto);

	// COMPLETAR COMENTARIOS DE DOXYGEN
	bool operator == (Vector3D const &objeto) const;

	// COMPLETAR EL RESTO DE OPERADORES
	Vector3D operator+(Vector3D const &v)const;
	Vector3D operator+()const;
	Vector3D operator-(Vector3D const &v)const;
	Vector3D operator-()const;
	Vector3D operator*(double const k)const;
	Vector3D operator*(Vector3D const &v)const;
	Vector3D operator^(Vector3D const &v)const;

	//! \name Funciones lectura y escritura de la clase Vector3D

	// COMPLETAR
	void leerVector3D();
	void escribirVector3D()const;
}; // Fin de la definición de la clase Vector3D


//////////////////////////////////////////////////////////////////////////////////////

//! \name Funciones que utilizan un objetos de la clase Vector3D, pero que no pertenecen a la clase Vector3D

	// COMPLETAR COMENTARIOS DE DOXYGEN
    Vector3D & operator* (double k, Vector3D const & objeto);

	// COMPLETAR COMENTARIOS DE DOXYGEN
    istream &operator>>(istream &stream, Vector3D &objeto);

	// COMPLETAR COMENTARIOS DE DOXYGEN    
	ostream &operator<<(ostream &stream, Vector3D const &objeto);


} // \brief Fin de namespace ed.

//  _VECTOR3D_HPP_
#endif 
