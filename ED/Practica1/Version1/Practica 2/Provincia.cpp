/*!	

	\file  Provincia.cpp
	\brief Definición de la clase Provincia
	\author  
	\date  
	\version 1.0

*/
//Para los flujos de entrada/salida en ficheros.
#include <fstream>  
#include <iostream>

// Para comprobar las pre y post condiciones
#include <cassert>

#include "Provincia.hpp"


// DEBES CODIFICAR LAS FUNCIONES DE LA CLASE Provincia

///////////////////////////////////////////////////////////////////////////////

// OSBSERVADORES
bool Provincia::hayMunicipios(){
	if(listaMunicipios_.empty()){
		return true;
	}
	else return false;
}

bool Provincia::existeMunicipio(std::string n){
	listaDoblementeEnlazada::iterator i;
	for(i==listaMunicipios_.begin();i!=listaMunicipios_.end();i++){
		if(i.getNombre()==n){
			return true;
		}
	}
	return false;
}

listaDoblementeEnlazada Provincia::getMunicipio(std::string n){
	#ifndef NDEBUG
		assert(existeMunicipio(n)==true);
	#endif

	listaDoblementeEnlazada::iterator i;
	for(i==listaMunicipios_.begin();i!=lsitaMunicipios_.end();i++){
		if(i.getNombre()==n){
			return listaMunicipios_[i];
		}
	}
}

int Provincia::getTotalHombres(){
	
}

int Provincia::getTotalMujeres(){

}

int getTotalHabitantes(){

}
/////////////////////////////////////////////////////////////////////////////////////////

// MODIFICADORES
void Provincia::setNombre(std::string n){
	nombre_=n;

	#ifndef NDEBUG
		assert(getNombre()==n)
	#endif
}

void Provincia::setCodigo(int c){
	codigo_=c;

	#ifndef NDEBUG
		assert(getCodigo()==c);
	#endif
}

///////////////////////////////////////////////////////////////////////////////////

// FUNCIÓN DE ESCRITURA



/////////////////////////////////////////////////////////////////////////////////////////

// OPERACIONES CON FICHEROS


