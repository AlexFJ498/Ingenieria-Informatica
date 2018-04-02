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
bool ed::ListaDoblementeEnlazadaOrdenada::isEmpty() const{
		if(nItems()==0){
			return true;
		}
		else return false;
	}

int ed::ListaDoblementeEnlazadaOrdenadaMunicipios::nItems(){
	int num=0;
	gotoHead();
	while(gotoNext()==true){
		num++;
		gotoNext();
	}
	num++;
	return num;
}

bool ed::ListaDoblementeEnlazadaOrdenadaMunicipios::isFirstItem(){
	#ifndef NDEBUG
		assert(isEmpty()==false);
	#endif

	if(getHead()==getCurrent()){
		return true;
	}
	else return false;
}

bool ed::ListaDoblementeEnlazadaOrdenadaMunicipios::isLastItem(){
	#ifndef NDEBUG
		assert(isEmpty()==false);
	#endif
	ListaDoblementeEnlazadaOrdenadaMunicipios aux=this*;
	aux.gotoLast();
	if(aux.getCurrent()==this->getCurrent()){
		return true;
	}
	else return false;
}

Municipio ed::ListaDoblementeEnlazadaOrdenadaMunicipios::getCurrentItem(){
	#ifndef NDEBUG
		assert(isEmpty()==false);
	#endif

	NodoDoblementeEnlazado aux=this->getCurrent();
	return aux.getItem();
}

Municipio ed::ListaDoblementeEnlazadaOrdenadaMunicipios::getPreviousItem(){
	#ifndef NDEBUG
		assert(isEmpty()==false 
			   and isFirstItem()==false);
	#endif

	NodoDoblementeEnlazado aux=this->getCurrent();
	NodoDoblementeEnlazado aux2=aux.getPrevious();
	return aux2.getItem();
}

Municipio ed::ListaDoblementeEnlazadaOrdenada::getNextItem(){
	#ifndef NDEBUG
		assert(isEmpty()==false
			   and isLastItem()==false);
	#endif

	NodoDoblementeEnlazado aux=this->getCurrent();
	NodoDoblementeEnlazado aux2=aux.getNext();
	return aux2.getItem();
}

void ed::ListaDoblementeEnlazadaOrdenadaMunicipios::gotoHead(){
	#ifndef NDEBUG
		assert(isEmpty()==false);
	#endif

	NodoDoblementeEnlazado aux=this->getHead();	
	setCurrent(aux);

	#ifndef NDEBUG
		assert(isFirstItem()==true);
	#endif
}

void ListaDoblementeEnlazadaOrdenada::gotoLast(){
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

	NodoDoblementeEnlazado aux=this->getCurrent();
	setCurrent(aux.getPrevious);
}
void ed::ListaDoblementeEnlazadaOrdenadaMunicipios::gotoNext(){
	#ifndef NDEBUG
		assert(isEmpty()==false
			   and isLastItem()=false);
	#endif

	NodoDoblementeEnlazado aux=this->getCurrent();
	setCurrent(aux.getNext();
}

bool ed::ListaDoblementeEnlazadaOrdenadaMunicipios::find(Municipio m){
	int state;	
	gotoHead();
	NodoDoblementeEnlazado aux;
	while(isLastItem()==false){
		aux=getCurrent();
		if(m==aux.getItem()){
			state=0;
		}
		gotoNext();
	}
	state=-1;

	#ifndef NDEBUG
		assert(if(state==0){getCurrentItem()==m
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
		NodoDoblementeEnlazado aux=this->getCurrent();
		NodoDoblementeEnlazado aux2=aux.getNext();
		aux2.setNext(m);
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
