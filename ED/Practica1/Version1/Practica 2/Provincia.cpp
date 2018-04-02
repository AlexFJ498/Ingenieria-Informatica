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
bool ed::Provincia::hayMunicipios(){
	if(listaMunicipios_.isEmpty()){
		return true;
	}
	else return false;
}

bool ed::Provincia::existeMunicipio(std::string n){
	listaMunicipios_.gotoHead();
	Municipio aux=listaMunicipios_.getCurrentItem();
	while(listaMunicipios_.isLastItem()==false){
		if(aux.getNombre()==n){
			return true;
		}
		listaMunicipios_.gotoNext();
		aux=listaMunicipios_.getCurrentItem();
	}
	if(aux.getNombre()==n){
		return true;
	}
	else return false;
}

ed::Municipio ed::Provincia::getMunicipio(std::string n){
	#ifndef NDEBUG
		assert(existeMunicipio(n)==true);
	#endif

	listaMunicipios_.find(n);
	return listaMunicipios_.getCurrentItem();
}

int ed::Provincia::getTotalHombres(){
	int nHombres=0;
	listaMunicipios_.gotoHead();
	Municipio aux=listaMunicipios_.getCurrentItem();
	do{
		nHombres+=aux.getHombres();
		listaMunicipios_.gotoNext();
		aux=listaMunicipios_.getCurrentItem();
	}while(listaMunicipios_.isLastItem()==false);
	nHombres+=aux.getHombres();
	return nHombres;
}

int ed::Provincia::getTotalMujeres(){
	int nMujeres=0;
	listaMunicipios_.gotoHead();
	Municipio aux=listaMunicipios_.getCurrentItem();
	do{
		nMujeres+=aux.getMujeres();
		listaMunicipios_.gotoNext();
		aux=listaMunicipios_.getCurrentItem();
	}while(listaMunicipios_.isLastItem()==false);
	nMujeres+=aux.getMujeres();
	return nMujeres;
}

int ed::Provincia::getTotalHabitantes(){
	int nHabitantes=0;
	listaMunicipios_.gotoHead();
	Municipio aux=listaMunicipios_.getCurrentItem();
	do{
		nHabitantes+=aux.getHabitantes();
		listaMunicipios_.gotoNext();
		aux=listaMunicipios_.getCurrentItem();
	}while(listaMunicipios_.isLastItem()==false);
	nHabitantes+=aux.getHabitantes();

	#ifndef NDEBUG
		assert(nHabitantes==this->getTotalHombres()+this->getTotalMujeres());
	#endif

	return nHabitantes;
}
/////////////////////////////////////////////////////////////////////////////////////////

// MODIFICADORES
void ed::Provincia::setNombre(std::string n){
	nombre_=n;

	#ifndef NDEBUG
		assert(getNombre()==n);
	#endif
}

void ed::Provincia::setCodigo(int c){
	codigo_=c;

	#ifndef NDEBUG
		assert(getCodigo()==c);
	#endif
}

void ed::Provincia::insertarMunicipio(Municipio m){
	#ifndef NDEBUG
		assert(existeMunicipio(m.getNombre())==false);
	#endif
	int old=getNumeroMunicipios();
	listaMunicipios_.insert(m);

	#ifndef NDEBUG
		assert(existeMunicipio(m.getNombre())==true
			   and getNumeroMunicipios()==old+1);
	#endif
}

void ed::Provincia::borrarMunicipio(std::string n){
	#ifndef NDEBUG
		assert(existeMunicipio(n)==true);
	#endif
	
	int old=getNumeroMunicipios();
	Municipio aux=getMunicipio(n);
	listaMunicipios_.find(aux);
	listaMunicipios_.remove();

	#ifndef NDEBUG
		assert(existeMunicipio(aux.getNombre())==false
			   and getNumeroMunicipios()==old-1);
	#endif
}

void ed::Provincia::borrarTodosLosMunicipios(){
	listaMunicipios_.gotoHead();
	do{
		listaMunicipios_.remove();
	}while(listaMunicipios_.isLastItem()==false);

	#ifndef NDEBUG
		assert(hayMunicipios()==false);
	#endif
}
///////////////////////////////////////////////////////////////////////////////////

// FUNCIÓN DE ESCRITURA
void ed::Provincia::escribirMunicipios(){
	std::cout<<"PROVINCIA "<<getNombre()<<std::endl;
	std::cout<<"Codigo: "<<getCodigo()<<std::endl;
	std::cout<<"Nº municipios: "<<getNumeroMunicipios()<<std::endl;
	
	std::cout<<"\nLISTA DE MUNICIPIOS"<<std::endl;
	std::cout<<"--------------------"<<std::endl;
	listaMunicipios_.gotoHead();
	do{
		Municipio aux=listaMunicipios_.getCurrentItem();
		std::cout<<aux.getNombre()<<":"<<std::endl;
		std::cout<<"\t-Codigo Postal: "<<aux.getCodigoPostal()<<std::endl;
		std::cout<<"\t-Nº mujeres: "<<aux.getMujeres()<<std::endl;	
		std::cout<<"\t-Nº hombres: "<<aux.getHombres()<<std::endl;
	}while(listaMunicipios_.isLastItem()==false);
}

/////////////////////////////////////////////////////////////////////////////////////////

// OPERACIONES CON FICHEROS
bool ed::Provincia::cargarFichero(std::string nFich){
	std::ifstream f;
	f.open(nFich.c_str());
	if(f.is_open()){
		Municipio aux;
		char codigo[50],nombreP[50],cPostal[50],nombreM[50],hombres[50],mujeres[50];
		while(f.getline(codigo,256,' ')){
			f.getline(nombreP,256,'\n');
			setCodigo(atoi(codigo));
			setNombre(nombreP);
			while(f.getline(cPostal,256,';')){
				f.getline(nombreM,256,';');
				f.getline(hombres,256,';');
				f.getline(mujeres,256,';');
				aux.setCodigoPostal(atoi(cPostal));
				aux.setNombre(nombreM);
				aux.setHombres(atoi(hombres));
				aux.setMujeres(atoi(mujeres));
				listaMunicipios_.insert(aux);
			}
			listaMunicipios_.gotoNext();
		}
		return true;
	}
	else{
		return false;
	}
}

bool ed::Provincia::grabarFichero(std::string nombre){
	std::ofstream f;
	f.open(nombre.c_str());
	if(f.is_open()){
		Municipio aux;
		listaMunicipios_.gotoHead();
		f<<getCodigo()<<'\n';
		while(listaMunicipios_.isLastItem()==false){
			aux=listaMunicipios_.getCurrentItem();
			f<<aux.getCodigoPostal()<<";"<<aux.getHombres()<<";"<<aux.getMujeres()<<";"<<'\n';
			listaMunicipios_.gotoNext();
		}
		aux=listaMunicipios_.getCurrentItem();
		f<<aux.getCodigoPostal()<<";"<<aux.getHombres()<<";"<<aux.getMujeres()<<";"<<'\n';
		return true;
	}
	else{
		return false;
	}
}
