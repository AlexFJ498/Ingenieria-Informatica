/*!
	\file   ListaDoblementeEnlazadaOrdenadaMunicipios.cpp
	\brief  Clase de una lista doblemente enlazada y ordenada de Municipios
	\author  
	\date  
	\version 1.0
*/

// Para comprobar las pre y post-condiciones
#include <cassert>

#include "ListaDoblementeEnlazadaOrdenadaMunicipios.hpp"
#include "NodoMunicipioInterfaz.hpp"
#include "Municipio.hpp"

// DEBES CODIFICAR LAS FUNCIONES DE LA CLASE ListaDoblementeEnlazadaOrdenadaMunicipios

//OBSERVADORES

bool ed::ListaDoblementeEnlazadaOrdenadaMunicipios::isEmpty()const{
		if(this->nItems()==0){
			return true;
		}
		else return false;
}

int ed::ListaDoblementeEnlazadaOrdenadaMunicipios::nItems()const{
	int num=0;
	ListaDoblementeEnlazadaOrdenadaMunicipios aux=*this;
	aux.gotoHead();
	while(aux.isLastItem()==true){
		num++;
		aux.gotoNext();
	}
	num++;
	return num;
}

bool ed::ListaDoblementeEnlazadaOrdenadaMunicipios::isFirstItem()const{
	#ifndef NDEBUG
		assert(isEmpty()==false);
	#endif

	if(getHead()==getCurrent()){
		return true;
	}
	else return false;
}

bool ed::ListaDoblementeEnlazadaOrdenadaMunicipios::isLastItem()const{
	#ifndef NDEBUG
		assert(isEmpty()==false);
	#endif
	ListaDoblementeEnlazadaOrdenadaMunicipios aux=*this;
	aux.gotoLast();
	if(aux.getCurrent()==this->getCurrent()){
		return true;
	}
	else return false;
}

ed::Municipio const & ed::ListaDoblementeEnlazadaOrdenadaMunicipios::getCurrentItem()const{
	#ifndef NDEBUG
		assert(isEmpty()==false);
	#endif

	NodoDoblementeEnlazadoMunicipio *aux=this->getCurrent();
	return aux->getItem();
}

ed::Municipio const & ed::ListaDoblementeEnlazadaOrdenadaMunicipios::getPreviousItem()const{
	#ifndef NDEBUG
		assert(isEmpty()==false 
			   and isFirstItem()==false);
	#endif

	NodoDoblementeEnlazadoMunicipio *aux=this->getCurrent();
	NodoDoblementeEnlazadoMunicipio *aux2=aux->getPrevious();
	return aux2->getItem();
}

ed::Municipio const & ed::ListaDoblementeEnlazadaOrdenadaMunicipios::getNextItem()const{
	#ifndef NDEBUG
		assert(isEmpty()==false
			   and isLastItem()==false);
	#endif

	NodoDoblementeEnlazadoMunicipio *aux=this->getCurrent();
	NodoDoblementeEnlazadoMunicipio *aux2=aux->getNext();
	return aux2->getItem();
}

////////////////////////////////////////////////////////////////////
//MODIFICADORES

void ed::ListaDoblementeEnlazadaOrdenadaMunicipios::gotoHead(){
	#ifndef NDEBUG
		assert(isEmpty()==false);
	#endif

	NodoDoblementeEnlazadoMunicipio *aux=this->getHead();	
	setCurrent(aux);

	#ifndef NDEBUG
		assert(isFirstItem()==true);
	#endif
}

void ed::ListaDoblementeEnlazadaOrdenadaMunicipios::gotoLast(){
	#ifndef NDEBUG
		assert(isEmpty()==false);
	#endif

	while(isLastItem()==false){
		gotoNext();
	}

	#ifndef NDEBUG
		assert(isLastItem()==true);
	#endif
}

void ed::ListaDoblementeEnlazadaOrdenadaMunicipios::gotoPrevious(){
	#ifndef NDEBUG
		assert(isEmpty()==false
			   and isFirstItem()==false);
	#endif

	NodoDoblementeEnlazadoMunicipio *aux=this->getCurrent();
	setCurrent(aux->getPrevious());
}
void ed::ListaDoblementeEnlazadaOrdenadaMunicipios::gotoNext(){
	#ifndef NDEBUG
		assert(isEmpty()==false
			   and isLastItem()==false);
	#endif

	NodoDoblementeEnlazadoMunicipio *aux=this->getCurrent();
	setCurrent(aux->getNext());
}

bool ed::ListaDoblementeEnlazadaOrdenadaMunicipios::find(Municipio m){
	int state;	
	gotoHead();
	NodoDoblementeEnlazadoMunicipio *aux;
	while(isLastItem()==false){
		aux=getCurrent();
		if(m==aux->getItem()){
			state=0;
		}
		gotoNext();
	}
	state=-1;

	#ifndef NDEBUG
		assert(if(state==0){getCurrentItem()==m}
			   and if(state==-1){(getCurrentItem()>m) || (isLastItem()==true)});
	#endif

	if(state==0) return true;
	else return false;
}

void ed::ListaDoblementeEnlazadaOrdenadaMunicipios::insert(Municipio m){
	#ifndef NDEBUG
		assert(find(m)==false);
	#endif

	int old=nItems();
	if(find(m)==false){
		NodoDoblementeEnlazadoMunicipio *aux=this->getCurrent();
		NodoDoblementeEnlazadoMunicipio *aux2=aux.getNext();
		aux2->setNext(m);
	}

	#ifndef NDEBUG
		assert(getCurrentItem()==m
			   and nItems()=old+1);
	#endif
}

void ed::ListaDoblementeEnlazadaOrdenadaMunicipios::remove(){
	#ifndef NDEBUG
		assert(isEmpty()==false);
	#endif

	if(isFirstItem()==false && isLastItem()==false){
		setNextItem(getCurrentItem());
	}
	if(isLastItem()==true && isEmpty()==false){
		setPreviousItem(getCurrentItem());
	}
	if(isFirstItem()==true && isEmpty()==false){
		setNextItem(getCurrentItem());
	}
}

void ed::ListaDoblementeEnlazadaOrdenadaMunicipios::removeAll(){
	gotoHead();
	while(isLastItem()==false){
		remove();
		gotoNext();
	}
}
