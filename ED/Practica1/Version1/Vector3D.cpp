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

double ed::Vector3D::modulo()const{
	double modulo;
	modulo=sqrt(v1_*v1_+v2_*v2_+v3_*v3_);

	#ifndef NDEBUG
		assert(modulo=sqrt(get1()*get1()+get2()*get2()+get3()*get3()));
	#endif
	return modulo;
}

double ed::Vector3D::angulo(Vector3D const &v)const{
	double angulo;
	angulo=acos(dotProduct(v)/(modulo()*v.modulo()));

	#ifndef NDEBUG
		assert(angulo=acos(dotProduct(v)/modulo()*v.modulo()));
	#endif
	return angulo;
}

double ed::Vector3D::alfa()const{
	#ifndef NDEBUG
		assert(modulo()>0);
	#endif

	double alfa;
	Vector3D v(1,0,0);
	alfa=angulo(v);

	#ifndef NDEBUG
		assert(alfa=angulo(v));
	#endif
	return alfa;
}

double ed::Vector3D::beta()const{
	#ifndef NDEBUG
		assert(modulo()>0);
	#endif

	double beta;
	Vector3D v(0,1,0);
	beta=angulo(v);

	#ifndef NDEBUG
		assert(beta=angulo(v));
	#endif
	return beta;
}

double ed::Vector3D::gamma()const{
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

double ed::Vector3D::dotProduct(Vector3D const &v)const{
	double producto;
	producto=v1_*v.get1()+v2_*get2()+v3_*get3();

	#ifndef NDEBUG
		assert(producto=get1()*v.get1()+get2()*v.get2()+get3()*v.get3());
	#endif
	return producto;
}

ed::Vector3D ed::Vector3D::crossProduct(Vector3D const &v)const{
	Vector3D w(0,0,0);
	w.v1_=get2()*v.v3_-get3()*v.v2_;
	w.v2_=get3()*v.v1_-get1()*v.v3_;
	w.v3_=get1()*v.v2_-get2()*v.v1_;

	#ifndef NDEBUG
		assert((dotProduct(w)==0) and (v.dotProduct(w)==0) and 
				(w.modulo()==modulo()*v.modulo()*sin(angulo(v))));
	#endif
	return w;
}

double ed::Vector3D::productoMixto(Vector3D const &v,Vector3D const &w)const{
	double producto;
	producto=dotProduct(v.crossProduct(w));

	#ifndef NDEBUG
		assert(dotProduct(v.crossProduct(w)));
	#endif
	return producto;
}

////////////////////////////////////////////////////////////////

// MODIFICADORES

// COMPLETAR
void ed::Vector3D::set1(double v){
	v1_=v;

	#ifndef NDEBUG
		assert(get1()==v);
	#endif
}

void ed::Vector3D::set2(double v){
	v2_=v;

	#ifndef NDEBUG
		assert(get2()==v);
	#endif
}

void ed::Vector3D::set3(double v){
	v3_=v;

	#ifndef NDEBUG
		assert(get3()==v);
	#endif
}

void ed::Vector3D::sumConst(double k){
	Vector3D old(0,0,0);
	old=*this;

	v1_=old.v1_+k;
	v2_=old.v2_+k;
	v3_=old.v3_+k;

	#ifndef NDEBUF
		assert(get1()==old.get1()+k and
			   get2()==old.get2()+k and
			   get3()==old.get3()+k);
	#endif
}

void ed::Vector3D::sumVect(Vector3D const &v){
	Vector3D old(0,0,0);
	old=*this;

	v1_=old.v1_+v.v1_;
	v2_=old.v2_+v.v2_;
	v3_=old.v3_+v.v3_;

	#ifndef NDEBUG
		assert(get1()==old.get1()+v.get1() and
			   get2()==old.get2()+v.get2() and
			   get3()==old.get3()+v.get3());
	#endif
}

void ed::Vector3D::multConst(double k){
	Vector3D old(0,0,0);
	old=*this;

	v1_=old.v1_*k;
	v2_=old.v2_*k;
	v3_=old.v3_*k;

	#ifndef NDEBUG
		assert(get1()==old.get1()*k and
			   get2()==old.get2()*k and
			   get3()==old.get3()*k);
	#endif
}

void ed::Vector3D::multVect(Vector3D const &v){
	Vector3D old(0,0,0);
	old=*this;

	v1_=old.v1_*v.v1_;
	v2_=old.v2_*v.v2_;
	v3_=old.v3_*v.v3_;

	#ifndef NDEBUG
		assert(get1()==old.get1()*v.get1() and
			   get2()==old.get2()*v.get2() and
			   get3()==old.get3()*v.get3());
	#endif
}


////////////////////////////////////////////////////////////////////////////////

// OPERADORES

// COMPLETAR
ed::Vector3D& ed::Vector3D::operator=(Vector3D const &objeto){
	*this=objeto;

	#ifndef NDEBUG
		assert(get1()==objeto.get1() and
			   get2()==objeto.get2() and
			   get3()==objeto.get3());
	#endif
	return *this;
}

bool ed::Vector3D::operator == (Vector3D const &objeto) const{
	if(get1()!=objeto.get1() || get2()!=objeto.get2() || get3()!=objeto.get3()){
		return false;
	}

	#ifndef NDEBUG
		assert(get1()==objeto.get1() and
			   get2()==objeto.get2() and
			   get3()==objeto.get3());
	#endif
	return true;
}

ed::Vector3D ed::Vector3D::operator+(Vector3D const &v)const{
	Vector3D aux(0,0,0);
	double v1,v2,v3;

	v1=this->get1()+v.get1();
	v2=this->get2()+v.get2();
	v3=this->get3()+v.get3();

	aux.set1(v1);
	aux.set2(v2);
	aux.set3(v3);

	#ifndef NDEBUG
		assert(aux.get1()==get1()+v.get1() and
			   aux.get2()==get2()+v.get2() and
			   aux.get3()==get3()+v.get3());
	#endif
	return aux;
}

ed::Vector3D ed::Vector3D::operator+()const{
	Vector3D aux(0,0,0);
	aux=*this;

	#ifndef NDEBUG
		assert(aux.get1()==get1() and
			   aux.get2()==get2() and
			   aux.get3()==get3());
	#endif
	return aux;
}

ed::Vector3D ed::Vector3D::operator-(Vector3D const &v)const{
	Vector3D aux(0,0,0);
	double v1,v2,v3;

	v1=this->get1()-v.get1();
	v2=this->get2()-v.get2();
	v3=this->get3()-v.get3();

	aux.set1(v1);
	aux.set2(v2);
	aux.set3(v3);

	#ifndef NDEBUG
		assert(aux.get1()==get1()-v.get1() and
			   aux.get2()==get2()-v.get2() and
			   aux.get3()==get3()-v.get3());
	#endif
	return aux;
}

ed::Vector3D ed::Vector3D::operator-()const{
	Vector3D aux(0,0,0);

	aux.set1(-v1_);
	aux.set2(-v2_);
	aux.set2(-v3_);

	#ifndef NDEBUG
		assert(aux.get1()==-get1() and
			   aux.get2()==-get2() and
			   aux.get3()==-get3());
	#endif
	return aux;
}

ed::Vector3D ed::Vector3D::operator*(double const k)const{
	Vector3D aux(0,0,0);
	double v1,v2,v3;

	v1=get1()*k;
	v2=get2()*k;
	v3=get3()*k;

	aux.set1(v1);
	aux.set2(v2);
	aux.set3(v3);

	#ifndef NDEBUG
		assert(aux.get1()==get1()*k and
			   aux.get2()==get2()*k and
			   aux.get3()==get3()*k);
	#endif	
	return aux;
}

ed::Vector3D ed::Vector3D::operator*(Vector3D const &v)const{
	Vector3D aux(0,0,0);

	aux.v1_=this->v1_*v.v1_;
	aux.v2_=this->v2_*v.v2_;
	aux.v3_=this->v3_*v.v3_;

	#ifndef NDEBUG
		assert(aux.v1_==this->get1()*v.get1() and
			   aux.v2_==this->get2()*v.get2() and
			   aux.v3_==this->get3()*v.get3());
	#endif
	return aux;
}

ed::Vector3D ed::Vector3D::operator^(Vector3D const &v)const{
	Vector3D w(0,0,0);

	w.v1_=this->v2_*v.v3_-this->v3_*v.v2_;
	w.v2_=-this->v1_*v.v3_+this->v3_*v.v1_;
	w.v3_=this->v1_*v.v2_-this->v2_*v.v1_;

	#ifndef NDEBUG
		assert((dotProduct(w)==0) and
			  (v.dotProduct(w)==0) and
			  (w.modulo()==modulo()*v.modulo()*sin(angulo(v))));
	#endif
	return w;
}
////////////////////////////////////////////////////////////////////////////////

// FUNCIONES DE LECTURA Y ESCRITURA

// COMPLETAR
void ed::Vector3D::leerVector3D(){
	std::cin>>v1_>>v2_>>v3_;
}

void ed::Vector3D::escribirVector3D()const{
	std::cout<<"("<<v1_<<","<<v2_<<","<<v3_<<")"<<std::endl;
}

////////////////////////////////////////////////////////////////////////////////


// Se incluyen los operadores sobrecargados dentro del espacio de nombres de ed

namespace ed{


// Producto "por un" escalar (prefijo): k * v
ed::Vector3D & operator* (double k, ed::Vector3D const & objeto)
{
	ed::Vector3D *vectorResultado = new ed::Vector3D(0,0,0);
	double v1,v2,v3;

	// COMPLETAR
	v1=k*objeto.get1();
	v2=k*objeto.get2();
	v3=k*objeto.get3();

	vectorResultado->set1(v1);
	vectorResultado->set2(v2);
	vectorResultado->set3(v3);

	#ifndef NDEBUG
		assert(vectorResultado->get1()==objeto.get1()*k and
			   vectorResultado->get2()==objeto.get2()*k and
			   vectorResultado->get3()==objeto.get3()*k);
	#endif
	return *vectorResultado;
}


// Sobrecarga del operador de salida
// Se escriben por pantalla las coordenadas del vector 3D  de la forma (v1, v2, v3)
ostream &operator<<(ostream &stream, ed::Vector3D const &objeto)
{
	// COMPLETAR
	stream<<'('<<objeto.get1()<<','<<objeto.get2()<<','<<objeto.get3()<<')';
  return stream;
}

// Sobrecarga del operador de entrada
istream &operator>>(istream &stream, ed::Vector3D &objeto)
{
  // COMPLETAR
	double aux;

	stream>>aux;
	objeto.set1(aux);

	stream>>aux;
	objeto.set2(aux);

	stream>>aux;
	objeto.set3(aux);
  return stream;
} 

} // Fin del espacio de nombres ed