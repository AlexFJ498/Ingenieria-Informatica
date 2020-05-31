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
	double v_[3];

   //! \name Funciones o métodos públicos de la clase Vector3D
   public:

	//! \name Constructores de la clase Vector3D

	// COMPLETAR
	/*
		\brief Constructor que crea un Vector3D nulo
		\note Funcion inline
		\pre Ninguna
		\post ((get1()==0) and (get2()==0) and (get3()==0))
	*/
	Vector3D(){
		v_[0]=0;
		v_[1]=0;
		v_[2]=0;

		#ifndef NDEBUG
			assert(get1()==0 and
				   get2()==0 and
				   get3()==0);
		#endif
	}

	/*!
		\brief Constructor que crea un nuevo vector a partir de los valores de las componentes
		\note Funcion inline
		\param v1: componente "x" del vector (tipo double)
		\param v2: componente "y" del vector (tipo double)
		\param v3: componente "z" del vector (tipo double)
		\pre Ninguna
		\post ((get1()==v1) and (get2()==v2) and (get3()==v3))
	*/
	Vector3D(double v1,double v2,double v3){
		v_[0]=v1;
		v_[1]=v2;
		v_[2]=v3;

		#ifndef NDEBUG
			//Postcondición
			assert((std::abs(get1()-v_[0])<COTA_ERROR) and 
				   (std::abs(get2()-v_[1])<COTA_ERROR) and 
				   (std::abs(get3()-v_[2])<COTA_ERROR));
		#endif
	}

	/*!
		\brief Constructor que crea un nuevo vector a partir de otro vector
		\param v: vector que se desea copiar (tipo Vector3D)
		\pre Ninguna
		\post ((get1()==v.get1())and (get2()==v.get2())and (get3()==v.get3()))
	*/
	Vector3D(Vector3D const &v){
		v_[0]=v.get1();
		v_[1]=v.get2();
		v_[2]=v.get3();

		#ifndef NDEBUG
			assert((std::abs(get1()-v.get1())<COTA_ERROR) and
				   (std::abs(get2()-v.get2())<COTA_ERROR) and
				   (std::abs(get3()-v.get3())<COTA_ERROR));
		#endif
	}
	//! \name Observadores: funciones de consulta de Vector3D

	// COMPLETAR
	/*!
		\brief Funcion que devuelve el valor de la primera componente del vector: v1
		\note La funcion tiene el calificador "const"
		\return Componente "v1" del vector3D (tipo double)
		\pre Ninguna
		\post Ninguna
	
	*/
	double get1()const;

	/*!
		\brief Funcion que devuelve el valor de la segunda componente del vector: v2
		\note La funcion tiene el calificador "const"
		\return Componente "v2" del vector3D (tipo double)
		\pre Ninguna
		\post Ninguna
	*/
	double get2()const;

	/*!
		\brief Funcion que devuelve el valor de la tercera componente del vector: v3
		\note La funcion tiene el calificador "const"
		\return Componente "v3" del vector3D (tipo double)
		\pre Ninguna
		\post Ninguna
	*/
	double get3()const;

	/*!
		\brief Funcion que calcula el modulo del vector
		\note La funcion tiene el calificador "const"
		\return Modulo del vector3D (tipo double)
		\pre Ninguna
		\post (valorDevuelto == sqrt ( get1()*get1()+ get2()*get2()+ get3()*get3()))
	*/
	double modulo()const;

	/*!
		\brief Funcion que devuelve el angulo en radianes entre el vector actual y el vector pasado como argumento
		\note La funcion tiene el calificador "const"
		\return Angulo del vector3D (tipo double)
		\pre (modulo() * v.modulo() > 0)
		\post (valorDevuelto == acos( dotProduct(v) / (modulo() * v.modulo()) ))
	*/
	double angulo(Vector3D const &v)const;

	/*!
		\brief Funcion que calcula el angulo del vector con el eje X
		\note La funcion tiene el calificador "const"
		\return Angulo del eje X del vector3D (tipo double)
		\pre (modulo()>0)
		\post (valorDevuelto == angulo(Vector3D(1,0,0)))
	*/
	double alfa()const;

	/*!
		\brief Funcion que calcula el angulo del vector con el eje Y
		\note La funcion tiene el calificador "const"
		\return Angulo del eje Y del vector3D (tipo double)
		\pre (modulo()>0)
		\post (valorDevuelto == angulo(Vector3D(0,1,0)))
	*/
	double beta()const;

	/*!
		\brief Funcion que calcula el angulo del vector con el eje Z
		\note La funcion tiene el calificador "const"
		\return Angulo del eje Z del vector3D (tipo double)
		\pre (modulo()>0)
		\post (valorDevuelto == angulo(Vector3D(0,0,1)))
	*/
	double gamma()const;

	/*!
		\brief Funcion que calcula el producto escalar
		\note La funcion tiene el calificador "const"
		\param v: vector sobre el que se realiza el producto escalar (tipo Vector3D)
		\return Producto escalar de dos Vector3D (tipo double)
		\pre Ninguna
		\post (valorDevuelto == get1() * v.get1()+ get2() * v.get2()+ get3() * v.get3())
	*/
	double dotProduct(Vector3D const &v)const;

	/*!
		\brief Funcion que devuelve el producto vectorial de dos vectores
		\note La funcion tiene el calificador "const"
		\param v: vector sobre el que se realiza el producto vectorial (tipo Vector3D)
		\return Producto vectorial de dos Vector3D (tipo Vector3D)
		\pre (dotProduct(valorDevuelto) == 0)
			 (v.dotProduct(valorDevuelto) == 0)
		\post (valorDevuelto.modulo() ==modulo()* v.modulo()* sin(angulo(v)))
	*/
	Vector3D crossProduct(Vector3D const &v)const;

	/*!
		\brief Funcion que devuelve el resultado de calcular el producto escalar del vector actual con el vector obtenido al calcular el producto vectorial de otros dos vectores
		\note La funcion tiene el calificador "const"
		\param v: vector sobre el que se realiza el producto mixto (tipo Vector3D)
		\param w: vector sobre el que se realiza el producto mixto (tipo Vector3D)
		\return Producto mixto (tipo double)
		\pre Ninguna
		\post (valorDevuelto == dotProduct(crossProduct(v,w)))
	*/
	double productoMixto(Vector3D const &v,Vector3D const &w)const;

	//! \name Modificadores: funciones de modificación de Vector3D

	// COMPLETAR

	/*!
		\brief Funcion que asigna un nuevo valor "v" a la primera componente del vector
		\param v: nuevo valor de la componente (tipo double)
		\pre Ninguna
		\post (get1()== v)
	*/
	void set1(double v);

	/*!
		\brief Funcion que asigna un nuevo valor "v" a la segunda componente del vector
		\param v: nuevo valor de la componente (tipo double)
		\pre Ninguna
		\post (get2()== v)
	*/
	void set2(double v);

	/*!
		\brief Funcion que asigna un nuevo valor "v" a la tercera componente del vector
		\param v: nuevo valor de la componente (tipo double)
		\pre Ninguna
		\post (get3()== v)
	*/
	void set3(double v);

	/*!
		\brief Funcion que modifica el vector sumando una constante a cada componente
		\param k: valor de la constante (tipo double)
		\pre Ninguna
		\post ((get1() == old.get1() + k)and (get2() == old.get2() + k)and (get3() == old.get3() + k))
	*/
	void sumConst(double k);

	/*!
		\brief Funcion que modifica el vector sumando a cada componente la componente equivalente de otro vector
		\param v: valor del vector que se usa para la suma (tipo Vector3D)
		\pre Ninguna
		\post ((get1() == old.get1() + v.get1())and (get2() == old.get2() + v.get2())and (get3() == old.get3() + v.get3()))
	*/
	void sumVect(Vector3D const &v);

	/*!
		\brief Funcion que modifica el vector multiplicando cada componente por una constante: escala el vector
		\param k: valor de la constante (tipo double)
		\pre Ninguna
		\post ((get1() == old.get1() * k)and (get2() == old.get2() * k)and (get3() == old.get3() * k))
	*/
	void multConst(double k);

	/*!
		\brief Funcion que modifica el vector multiplicando, por separado, cada componente por la componente de otro vector
		\param v: valor del vector que se usa para la multiplicacion (tipo Vector3D)
		\pre Ninguna
		\post ((get1() == old.get1() * v.get1())and (get2() == old.get2() * v.get2())and (get3() == old.get3() * v.get3()))
	*/
	void multVect(Vector3D const &v);

    //! \name Operadores de la clase
   
	// COMPLETAR COMENTARIOS DE DOXYGEN
	/*!
		\brief Operador de asignacion: devuelve el vector actual que ha sido modificado con las componentes de otro vector
		\attention Se sobrecarga el operador de asignacion "="
		\param objeto: valor del vector que se modifica (tipo Vector3D)
		\return Vector asignado (tipo Vector3D)
		\pre Ninguna
		\post ((get1()==v.get1())and (get2()==v.get2())and (get3()==v.get3()))
	*/
	Vector3D & operator=(Vector3D const &objeto);

	// COMPLETAR COMENTARIOS DE DOXYGEN

	/*!
		\brief Operador de igualdad: compara el vector actual con otro vector y comprueba si las componentes son iguales una a una
		\note La funcion tiene el calificador "const"
		\attention Se sobrecarga el operador de igualdad "=="
		\param objeto: valor del vector con el que se hace la comprobacion (tipo Vector3D)
		\return True si los vectores son iguales. False si son diferentes (tipo booleano)
		\pre Ninguna
		\post (valorDevuelto ==(get1() == v.get1())and (get2() == v.get2() )and (get3() == v.get3()))
	*/
	bool operator == (Vector3D const &objeto) const;

	// COMPLETAR EL RESTO DE OPERADORES
	/*!
		\brief Operador de suma binario: devuelve otro vector que es la suma del vector actual y el vector pasado como parametro
		\note La funcion tiene el calificador "const"
		\attention Se sobrecarga el operador de suma "+"
		\param v: valor del vector que se suma (tipo Vector3D)
		\return Vector resultado (tipo Vector3D)
		\pre Ninguna
		\post ((valorDevuelto.get1() == get1() + v.get1())and (valorDevuelto.get2() == get2() + v.get2())and (valorDevuelto.get3() == get3() + v.get3()))
	*/
	Vector3D operator+(Vector3D const &v)const;

	/*!
		\brief Operador de suma unario: devuelve otro vector que es una copia del vector actual
		\note La funcion tiene el calificador "const"
		\attention Se sobrecarga el operador de suma "+"
		\return Vector resultado (tipo Vector3D)
		\pre Ninguna
		\post ((valorDevuelto.get1() == get1())and (valorDevuelto.get2() == get2())and (valorDevuelto.get3() == get3()))
	*/
	Vector3D operator+()const;

	/*!
		\brief Operador de resta binario: devuelve otro vector que es la diferencia entre el vector actual y el vector pasado como parámetro
		\note La funcion tiene el calificador "const"
		\attention Se sobrecarga el operador de resta "-"
		\param v: valor del vector que se usa para la resta (tipo Vector3D)
		\return Vector resultado (tipo Vector3D)
		\pre Ninguna
		\post ((valorDevuelto.get1() == get1() - v.get1())and (valorDevuelto.get2() == get2() - v.get2())and (valorDevuelto.get3() == get3() - v.get3()))
	*/
	Vector3D operator-(Vector3D const &v)const;

	/*!
		\brief Operador de resta unario: devuelve otro vector que es el opuesto al vector actual
		\note La funcion tiene el calificador "const"
		 \attention Se sobrecarga el operador de resta"-"
		\return Vector resultado (tipo Vector3D)
		\pre Ninguna
		\post ((valorDevuelto.get1() == - get1())and (valorDevuelto.get2() == - get2())and (valorDevuelto.get3() == - get3()))
	*/
	Vector3D operator-()const;

	/*!
		\brief Operador producto postfijo: devuelve otro vector cuyas componentes se obtienen multiplicando por “k” las componentes del vector actual
		\note La funcion tiene el calificador "const"
		\attention Se sobrecarga el operador de multiplicacion "*"
		\return Vector resultado (tipo Vector3D)
		\pre Ninguna
		\post ((valorDevuelto.get1() == get1() * k)and (valorDevuelto.get2() == get2() * k)and (valorDevuelto.get3() == get3() * k))
	*/
	Vector3D operator*(double const k)const;

	/*!
		\brief Operador producto escalar: devuelve el producto escalar de dos vectores
		\note La funcion tiene el calificador "const"
		\attention Se sobrecarga el operador de multiplicacion "*"
		\return Producto escalar de dos Vector3D (tipo double)
		\pre Ninguna
		\post (valorDevuelto == get1() * v.get1()+ get2() * v.get2()+ get3() * v.get3())
	*/
	double operator*(Vector3D const &v)const;

	/*!
		\brief Operador producto vectorial: devuelve un Vector3D que es el resultado del producto vectorial de dos vectores
		\note La funcion tiene el calificador "const"
		\attention Se sobrecarga el operador de multiplicacion "*"
		\return Producto vectorial de dos vector3D (tipo Vector3D)
		\pre Ninguna
		\post ((dotProduct(valorDevuelto) == 0)
			   (v.dotProduct(valorDevuelto) == 0)
			   (valorDevuelto.modulo() ==modulo()* v.modulo()* sin(angulo(v))))
	*/
	Vector3D operator^(Vector3D const &v)const;

	//! \name Funciones lectura y escritura de la clase Vector3D

	// COMPLETAR

	/*!
		\brief Lee desde el teclado las componentes del vector
		\pre Ninguna
		\post Ninguna
	*/
	void leerVector3D();

	/*!
		\brief Escribe por pantalla las componentes del vector con el formato (v1,v2,v3)
		\note La funcion tiene el calificador "const"
		\pre Ninguna
		\post Ninguna
	*/
	void escribirVector3D()const;
}; // Fin de la definición de la clase Vector3D


//////////////////////////////////////////////////////////////////////////////////////

//! \name Funciones que utilizan un objetos de la clase Vector3D, pero que no pertenecen a la clase Vector3D

	// COMPLETAR COMENTARIOS DE DOXYGEN
	/*!
		\brief Operador prefijo de producto por un numero real: devuelve otro vector cuyas componentes se obtienen multiplicando por “k” las componentes del vector “objeto” pasado como parámetro
		\attention Se sobrecarga el operador de multiplicacion "*"
		\return Vector resultado (tipo Vector3D)
		\pre Ninguna
		\post ((valorDevuelto.get1() == v.get1() * k)and (valorDevuelto.get2() == v.get2() * k)and (valorDevuelto.get3() == v.get3() * k))
	*/
    Vector3D & operator* (double k, Vector3D const & objeto);

	// COMPLETAR COMENTARIOS DE DOXYGEN
	/*!
		\brief Operador de entrada: lee desde el flujo de entrada las componentes del vector “v” separadas por espacios
		\attention Se sobrecarga el operador de entrada ">>"
		\pre Ninguna
		\post Ninguna
	*/
    istream &operator>>(istream &stream, Vector3D &objeto);

	// COMPLETAR COMENTARIOS DE DOXYGEN    
	/*!
		\brief Operador de salida: escribe en el flujo de salida las componentes del vector “v” con el formato (v1,v2,v3)
		\attention Se sobrecarga el operador de salida ">>"
		\pre Ninguna
		\post Ninguna
	*/
	ostream &operator<<(ostream &stream, Vector3D const &objeto);


} // \brief Fin de namespace ed.

//  _VECTOR3D_HPP_
#endif 
