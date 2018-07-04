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
#include <cstdio>
#include <cstdlib>

// Para comprobar las pre y post condiciones
#include <cassert>

#include "Provincia.hpp"


// DEBES CODIFICAR LAS FUNCIONES DE LA CLASE Provincia

///////////////////////////////////////////////////////////////////////////////

// OSBSERVADORES
bool ed::Provincia::hayMunicipios()const{
	if(this->getNumeroMunicipios()!=0){
		return true;
	}
	return false;
}

bool ed::Provincia::existeMunicipio(std::string n){
	Municipio aux(n);

	return _listaMunicipios.find(aux);
}

ed::Municipio ed::Provincia::getMunicipio(std::string n){
	#ifndef NDEBUG
		assert(this->existeMunicipio(n));
	#endif

	return _listaMunicipios.getCurrentItem();
}

int ed::Provincia::getTotalHombres(){
	int num=0;

	_listaMunicipios.gotoHead();

	for(int i=0;i<_listaMunicipios.nItems();i++){
		num+=(_listaMunicipios.getCurrentItem()).getHombres();
		_listaMunicipios.gotoNext();
	}

	return num;
}

int ed::Provincia::getTotalMujeres(){
	int num=0;

	_listaMunicipios.gotoHead();

	for(int i=0;i<_listaMunicipios.nItems();i++){
		num+=(_listaMunicipios.getCurrentItem()).getMujeres();
		_listaMunicipios.gotoNext();
	}

	return num;
}
/////////////////////////////////////////////////////////////////////////////////////////

// MODIFICADORES
void ed::Provincia::insertarMunicipio(const Municipio &m){
	#ifndef NDEBUG
		assert(this->existeMunicipio(m.getNombre())==false);
	#endif

	int old=this->getNumeroMunicipios();

	_listaMunicipios.insert(m);

	#ifndef NDEBUG
		assert(this->existeMunicipio(m.getNombre()));
		assert(this->getNumeroMunicipios()==old+1);
	#endif
}

void ed::Provincia::borrarMunicipio(std::string nombre){
	#ifndef NDEBUG
		assert(this->existeMunicipio(nombre));
	#endif

	int old=this->getNumeroMunicipios();
	Municipio aux(nombre);
	_listaMunicipios.find(aux); //dejamos el cursor en el municipio
	_listaMunicipios.remove(); //borra el municipio apuntado por el cursor

	#ifndef NDEBUG
		assert(this->existeMunicipio(nombre)==false);
		assert(this->getNumeroMunicipios()==old-1);
	#endif
}

void ed::Provincia::borrarTodosLosMunicipios(){
	_listaMunicipios.removeAll();

	#ifndef NDEBUG
		assert(this->hayMunicipios()==false);
	#endif
}

///////////////////////////////////////////////////////////////////////////////////

// FUNCIÓN DE ESCRITURA
void ed::Provincia::escribirMunicipios(){
	if(this->getNumeroMunicipios()==0){
		std::cout<<"LA LISTA ESTA VACIA"<<std::endl;
		return;
	}
	std::cout<<"DATOS DE PROVINCIA"<<std::endl;
	std::cout<<"nombre: "<<this->getNombre()<<std::endl;
	std::cout<<"codigo: "<<this->getCodigo()<<std::endl;
	std::cout<<std::endl;
	std::cout<<"LISTA DE MUNICIPIOS"<<std::endl;
	std::cout<<" numero |nombre | codigo postal | nºmujeres | nºhombres"<<std::endl;

	_listaMunicipios.gotoHead();
	for(int i=0;i<_listaMunicipios.nItems();i++){
		std::cout<<"Municipio "<<i+1<<": "<<_listaMunicipios.getCurrentItem().getNombre()<<", "<<_listaMunicipios.getCurrentItem().getCodigoPostal()<<", "<<_listaMunicipios.getCurrentItem().getMujeres()<<", "<<_listaMunicipios.getCurrentItem().getHombres()<<std::endl;

		if(_listaMunicipios.isLastItem()){break;}
		_listaMunicipios.gotoNext();
	}
	std::cout<<std::endl;
}


/////////////////////////////////////////////////////////////////////////////////////////

// OPERACIONES CON FICHEROS
bool ed::Provincia::cargarFichero(std::string n){
	std::ifstream f;

	f.open(n.c_str());
	if(f.is_open()){
		std::cout<<"Error al abrir el fichero"<<std::endl;
		return false;
	}

	char codigoP[50],nombreP[50], cPostalM[50], nombreM[50], hombresM[50], mujeresM[50];

	f.getline(codigoP,256,' ');
	f.getline(nombreP,256,'\n');
	this->setCodigo(atoi(codigoP));
	this->setNombre(nombreP);
	Municipio aux;

	while(f.getline(cPostalM,256,' ')){
		f.getline(nombreM,256,';');
		f.getline(hombresM,256,';');
		f.getline(mujeresM,256,';');

		aux.setCodigoPostal(atoi(cPostalM));
		aux.setNombre(nombreM);
		aux.setHombres(atoi(hombresM));
		aux.setMujeres(atoi(mujeresM));

		_listaMunicipios.insert(aux);
	}

	return true;
}

bool ed::Provincia::grabarFichero(std::string n){
	std::ofstream f;

	f.open(n.c_str());
	if(f.is_open()){
		std::cout<<"Error al abrir el fichero"<<std::endl;
		return false;
	}

	f<<this->getCodigo()<<" "<<this->getNombre()<<std::endl;

	_listaMunicipios.gotoHead();
	for(int i=0;i<_listaMunicipios.nItems();i++){
		f<<_listaMunicipios.getCurrentItem().getCodigoPostal()<<" "<<_listaMunicipios.getCurrentItem().getNombre()<<";"<<_listaMunicipios.getCurrentItem().getHombres()<<";"<<_listaMunicipios.getCurrentItem().getMujeres()<<";"<<std::endl;

	_listaMunicipios.gotoNext();
	}

	return true;
}
