/*! 
   \file  Medicion.cpp
   \brief Fichero que contiene el código de las funciones de la clase Medicion
*/


// Ficheros de cabecera
#include <iostream>

// atoi, atof
#include <stdlib.h>

#include "Medicion.hpp"


// COMPLETAR
//Modificadores públicos
void ed::Medicion::setFecha(Fecha f){
	this->fecha_=f;

	#ifndef NDEBUG
		assert(this->getFecha()==f);
	#endif
}

void ed::Medicion::setPrecipitacion(float p){
	#ifndef NDEBUG
		assert(p>=0.0);
	#endif

	this->precipitacion_=p;

	#ifndef NDEBUG
		assert(this->getPrecipitacion()==p);
	#endif
}

//Operadores públicos
bool ed::Medicion::operator==(Medicion const & m){
	if(this->getFecha()==m.getFecha()){
		
	}else{
		return false;
	}

	#ifndef NDEBUG
		assert(this->getFecha()==m.getFecha());
	#endif

	return true;
}

ed::Medicion ed::Medicion::operator=(Medicion const & m){
	this->setFecha(m.getFecha());
	this->setPrecipitacion(m.getPrecipitacion());

	#ifndef NDEBUG
		assert(this->getFecha()==m.getFecha() and
			   this->getPrecipitacion()==m.getPrecipitacion());
	#endif

	return *this;
}

//Funciones de lectura y escritura públicas
void ed::Medicion::leerMedicion(){
	std::cin>>*this;
}

void ed::Medicion::escribirMedicion(){
	std::cout<<*this;
}
////////////////////////////////////////////////////////////////////////////////


// Se incluyen los operadores sobrecargados dentro del espacio de nombres de ed

namespace ed{

// Sobrecarga del operador de salida
ostream &operator<<(ostream &stream, ed::Medicion const &medicion){
	Fecha aux=medicion.getFecha();
	std::cout<<aux.getDia()<<"-"<<aux.getMes()<<"-"<<aux.getAgno()<<" "<<medicion.getPrecipitacion()<<std::endl;

	return stream;
}

// Sobrecarga del operador de entrada
istream &operator>>(istream &stream, ed::Medicion &medicion){
	std::string size;

	std::getline(stream,size,'-');
	(medicion.fecha).setDia(atoi(size.c_str));

	std::getline(stream,size,'-');
	(medicion.fecha).setMes(atoi(size.c_str));

	std::getline(stream,size,' ');
	(medicion.fecha).setAgno(atoi(size.c_str));

	std::getline(stream,size,'\n');
	medicion.precipitacion(atoi(size.c_str));

	return stream;
} 

} // Fin del espacio de nombres ed
