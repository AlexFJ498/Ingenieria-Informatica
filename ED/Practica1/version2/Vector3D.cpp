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
	return v_[0];
}

double ed::Vector3D::get2()const{
	return v_[1];
}

double ed::Vector3D::get3()const{
	return v_[2];
}

double ed::Vector3D::modulo()const{
	double modulo;
	modulo=sqrt(get1()*get1()+get2()*get2()+get3()*get3());

	#ifndef NDEBUG
		assert((std::abs(modulo-sqrt(get1()*get1()+get2()*get2()+get3()*get3())))<COTA_ERROR);
	#endif
	return modulo;
}

double ed::Vector3D::angulo(Vector3D const &v)const{
	#ifndef NDEBUG
		assert(modulo()*v.modulo()>0);
	#endif
	double angulo;
	angulo=acos(dotProduct(v)/(modulo()*v.modulo()));

	#ifndef NDEBUG
		assert(std::abs(angulo-acos(dotProduct(v)/(modulo()*v.modulo())))<COTA_ERROR);
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
		assert((std::abs(alfa-angulo(v)))<COTA_ERROR);
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
		assert((std::abs(beta-angulo(v)))<COTA_ERROR);
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
	producto=get1()*v.get1()+get2()*v.get2()+get3()*v.get3();

	#ifndef NDEBUG
		assert((std::abs(producto-(get1()*v.get1()+get2()*v.get2()+get3()*v.get3())))<COTA_ERROR);
	#endif
	return producto;
}

ed::Vector3D ed::Vector3D::crossProduct(Vector3D const &v)const{
	Vector3D w(0,0,0);
	w.set1(get2()*v.get3()-get3()*v.get2());
	w.set2(get3()*v.get1()-get1()*v.get3());
	w.set3(get1()*v.get2()-get2()*v.get1());


	/*w.v1_=get2()*v.v3_-get3()*v.v2_;
	w.v2_=get3()*v.v1_-get1()*v.v3_;
	w.v3_=get1()*v.v2_-get2()*v.v1_;*/

	#ifndef NDEBUG
		assert((dotProduct(w)==0) and (v.dotProduct(w)==0) and 
				(std::abs(w.modulo()-(modulo()*v.modulo()*sin(angulo(v))))<COTA_ERROR));
	#endif
	return w;
}

double ed::Vector3D::productoMixto(Vector3D const &v,Vector3D const &w)const{
	double producto;
	producto=dotProduct(v.crossProduct(w));

	#ifndef NDEBUG
		assert(std::abs(producto-dotProduct(v.crossProduct(w)))<COTA_ERROR);
	#endif
	return producto;
}

////////////////////////////////////////////////////////////////

// MODIFICADORES

// COMPLETAR
void ed::Vector3D::set1(double v){
	v_[0]=v;

	#ifndef NDEBUG
		assert(std::abs(get1()-v)<COTA_ERROR);
	#endif
}

void ed::Vector3D::set2(double v){
	v_[1]=v;

	#ifndef NDEBUG
		assert(std::abs(get2()-v)<COTA_ERROR);
	#endif
}

void ed::Vector3D::set3(double v){
	v_[2]=v;

	#ifndef NDEBUG
		assert((std::abs(get3()-v))<COTA_ERROR);
	#endif
}

void ed::Vector3D::sumConst(double k){
	Vector3D old=*this;
	set1(old.get1()+k);
	set2(old.get2()+k);
	set3(old.get3()+k);

	#ifndef NDEBUF
		assert(((std::abs(get1()-(old.get1()+k)))<COTA_ERROR) and
			   ((std::abs(get2()-(old.get2()+k)))<COTA_ERROR) and
			   ((std::abs(get3()-(old.get3()+k)))<COTA_ERROR));
	#endif
}

void ed::Vector3D::sumVect(Vector3D const &v){
	Vector3D old=*this;
	set1(old.get1()+v.get1());
	set2(old.get2()+v.get2());
	set3(old.get3()+v.get3());

	#ifndef NDEBUG
		assert((std::abs(get1()-(old.get1()+v.get1()))<COTA_ERROR) and
			   (std::abs(get2()-(old.get2()+v.get2()))<COTA_ERROR) and
			   (std::abs(get3()-(old.get3()+v.get3()))<COTA_ERROR));
	#endif
}

void ed::Vector3D::multConst(double k){
	Vector3D old=*this;
	set1(old.get1()*k);
	set2(old.get2()*k);
	set3(old.get3()*k);

	#ifndef NDEBUG
		assert((std::abs(get1()-old.get1()*k)<COTA_ERROR) and
			   (std::abs(get2()-old.get2()*k)<COTA_ERROR) and
			   (std::abs(get3()-old.get3()*k)<COTA_ERROR));
	#endif
}

void ed::Vector3D::multVect(Vector3D const &v){
	Vector3D old=*this;
	set1(old.get1()*v.get1());
	set2(old.get2()*v.get2());
	set3(old.get3()*v.get3());

	#ifndef NDEBUG
		assert((std::abs(get1()-old.get1()*v.get1())<COTA_ERROR) and
			   (std::abs(get2()-old.get2()*v.get2())<COTA_ERROR) and
			   (std::abs(get3()-old.get3()*v.get3())<COTA_ERROR));
	#endif
}


////////////////////////////////////////////////////////////////////////////////

// OPERADORES

// COMPLETAR
ed::Vector3D& ed::Vector3D::operator=(Vector3D const &objeto){
	this->set1(objeto.get1());
	this->set2(objeto.get2());
	this->set3(objeto.get3());

	#ifndef NDEBUG
		assert((std::abs(get1()-objeto.get1())<COTA_ERROR) and
			   (std::abs(get2()-objeto.get2())<COTA_ERROR) and
			   (std::abs(get3()-objeto.get3())<COTA_ERROR));
	#endif
	return *this;
}

bool ed::Vector3D::operator == (Vector3D const &objeto) const{
	if(get1()!=objeto.get1() || get2()!=objeto.get2() || get3()!=objeto.get3()){
		return false;
	}

	#ifndef NDEBUG
		assert((std::abs(get1()-objeto.get1())<COTA_ERROR) and
			   (std::abs(get2()-objeto.get2())<COTA_ERROR) and
			   (std::abs(get3()-objeto.get3())<COTA_ERROR));
	#endif
	return true;
}

ed::Vector3D ed::Vector3D::operator+(Vector3D const &v)const{
	Vector3D aux(0,0,0);
	aux.set1(this->get1()+v.get1());
	aux.set2(this->get2()+v.get2());
	aux.set3(this->get3()+v.get3());

	#ifndef NDEBUG
		assert((std::abs(aux.get1()-(get1()+v.get1()))<COTA_ERROR) and
			   (std::abs(aux.get2()-(get2()+v.get2()))<COTA_ERROR) and
			   (std::abs(aux.get3()-(get3()+v.get3()))<COTA_ERROR));
	#endif
	return aux;
}

ed::Vector3D ed::Vector3D::operator+()const{
	Vector3D aux=*this;

	#ifndef NDEBUG
		assert((std::abs(aux.get1()-get1())<COTA_ERROR) and
			   (std::abs(aux.get2()-get2())<COTA_ERROR) and
			   (std::abs(aux.get3()-get3())<COTA_ERROR));
	#endif
	return aux;
}

ed::Vector3D ed::Vector3D::operator-(Vector3D const &v)const{
	Vector3D aux(0,0,0);
	aux.set1(this->get1()-v.get1());
	aux.set2(this->get2()-v.get2());
	aux.set3(this->get3()-v.get3());

	#ifndef NDEBUG
		assert((std::abs(aux.get1()-(get1()-v.get1()))<COTA_ERROR) and
			   (std::abs(aux.get2()-(get2()-v.get2()))<COTA_ERROR) and
			   (std::abs(aux.get3()-(get3()-v.get3()))<COTA_ERROR));
	#endif
	return aux;
}

ed::Vector3D ed::Vector3D::operator-()const{
	Vector3D aux(0,0,0);
	aux.set1(this->get1()*(-1));
	aux.set2(this->get2()*(-1));
	aux.set3(this->get3()*(-1));

	#ifndef NDEBUG
		assert((std::abs(aux.get1()-(-get1()))<COTA_ERROR) and
			   (std::abs(aux.get2()-(-get2()))<COTA_ERROR) and
			   (std::abs(aux.get3()-(-get3()))<COTA_ERROR));
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
		assert((std::abs(aux.get1()-get1()*k)<COTA_ERROR) and
			   (std::abs(aux.get2()-get2()*k)<COTA_ERROR) and
			   (std::abs(aux.get3()-get3()*k)<COTA_ERROR));
	#endif	
	return aux;
}

double ed::Vector3D::operator*(Vector3D const &v)const{
	double producto;
	producto=get1()*v.get1()+get2()*v.get2()+get3()*v.get3();	

	//producto=v1_*v.v1_+v2_*v.v2_+v3_*v.v3_;

	#ifndef NDEBUG
		assert(std::abs(producto-(get1()*v.get1()+ get2()*v.get2()+ get3()*v.get3()))<COTA_ERROR);
	#endif
	return producto;
}

ed::Vector3D ed::Vector3D::operator^(Vector3D const &v)const{
	Vector3D w(0,0,0);
	
	w.set1(this->get2()*v.get3()-this->get3()*v.get2());
	w.set2(-this->get1()*v.get3()+this->get3()*v.get1());
	w.set3(this->get1()*v.get2()-this->get2()*v.get1());

	#ifndef NDEBUG
		assert((dotProduct(w)==0) and
			  (v.dotProduct(w)==0) and
			  (std::abs(w.modulo()-(modulo()*v.modulo()*sin(angulo(v))))<COTA_ERROR));
	#endif
	return w;
}
////////////////////////////////////////////////////////////////////////////////

// FUNCIONES DE LECTURA Y ESCRITURA

// COMPLETAR
void ed::Vector3D::leerVector3D(){
	std::cout<<"Introduzca las componentes separadas por espacios"<<std::endl;
	double aux[3]={0,0,0};
	std::cin>>aux[0]>>aux[1]>>aux[2];

	set1(aux[0]);
	set2(aux[1]);
	set3(aux[2]);
}

void ed::Vector3D::escribirVector3D()const{
	std::cout<<"("<<get1()<<","<<get2()<<","<<get3()<<")"<<std::endl;
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
