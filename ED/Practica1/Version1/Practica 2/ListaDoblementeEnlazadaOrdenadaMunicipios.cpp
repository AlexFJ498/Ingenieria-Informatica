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

void ed::ListaDoblementeEnlazadaOrdenadaMunicipios::gotoHead(){
	#ifndef NDEBUG
		assert(this->isEmpty()==false);
	#endif

	this->setCurrent(this->getHead());

	#ifndef NDEBUG
		assert(this->isFirstItem());
	#endif
}

void ed::ListaDoblementeEnlazadaOrdenadaMunicipios::gotoLast(){
	#ifndef NDEBUG
		assert(this->isEmpty()==false);
	#endif

	this->gotoHead();
	for(int i=0;i<this->nItems() && !(this->isLastItem());i++){
		this->gotoNext();
	}

	#ifndef NDEBUG
		assert(this->isLastItem());
	#endif
}

void ed::ListaDoblementeEnlazadaOrdenadaMunicipios::gotoPrevious(){
	#ifndef NDEBUG
		assert(this->isEmpty()==false);
		assert(this->isFirstItem()==false);
	#endif

	this->setCurrent(this->getCurrent()->getPrevious());
}

void ed::ListaDoblementeEnlazadaOrdenadaMunicipios::gotoNext(){
	#ifndef NDEBUG
		assert(this->isEmpty()==false);
		assert(this->isLastItem()==false);
	#endif

	this->setCurrent(this->getCurrent()->getNext());
}

bool ed::ListaDoblementeEnlazadaOrdenadaMunicipios::find(const Municipio &m){
	//Se busca por nombre
	bool state=false;

	if(this->nItems()==0){
		return false;
	}

	this->gotoHead();
	for(int i=0;i<this->nItems();i++){
		if(this->getCurrentItem()==m){
			//Si existe se coloca el cursor en el nodo que contiene el item
			state=true;
			break;
		}
		if(this->isLastItem()){break;}
		this->gotoNext();
	}

	if(state==false){
		for(int j=0;j<this->nItems();j++){
			if(m<this->getCurrentItem()){
				//Si no existe, se coloca en el elemento que es mayor que el item buscado...
				break;
			}
			if(this->isLastItem()){break;}
			this->gotoNext();
			//...o en el último elemento, si todos los elementos son menores que el elemento buscado
		}
	}

	#ifndef NDEBUG
		if(state==true){
			assert(this->getCurrentItem()==m);
		}
		if(state==false){
			assert(m<this->getCurrentItem() || this->isLastItem());
		}
	#endif

	return state;
}

void ed::ListaDoblementeEnlazadaOrdenadaMunicipios::insert(const Municipio &m){
	#ifndef NDEBUG
		assert(this->find(m)==false);
	#endif

	int old=nItems();
	NodoDoblementeEnlazadoMunicipio *aux=new NodoDoblementeEnlazadoMunicipio(m,NULL,NULL);

	//Si la lista está vacía
	if(this->nItems()==0){
		this->setHead(aux);
		this->getHead()->setItem(m);
		this->getHead()->setPrevious(NULL);
		this->getHead()->setNext(NULL);

		this->gotoHead(); //para situar el cursor en el nuevo nodo

	}
	else{

		gotoHead();//Situamos el cursor en la cabeza

		//Si insertamos al comienzo de la lista
		if(m<this->getCurrentItem()){

			aux->setNext(this->getCurrent()); //Creamos un nodo que tenga un puntero anterior a null, y un puntero siguiente al que era la cabeza de la lista
			this->getCurrent()->setPrevious(aux); //Conectamos el puntero anterior de la antigua cabeza a la nueva
			this->setHead(aux);

			this->gotoHead(); //para situar el cursor en el nuevo nodo
		}
		else{

			this->gotoLast(); //Situamos el cursor al final de la lista

			//Si insertamos al final de la lista
			if(this->getCurrentItem()<m){

				aux->setPrevious(this->getCurrent()); //Creamos un nodo al revés que en el caso anterior
				this->getCurrent()->setNext(aux);

				this->gotoLast(); //para situar el cursor en el nuevo nodo
			}
			else{

				this->gotoHead();

				//Insertamos el item en cualquier otro sitio de la lista
				for(int i=0;i<this->nItems();i++){

					if(m<this->getCurrentItem()){
						this->gotoPrevious();

						aux->setPrevious(this->getCurrent());
						aux->setNext(this->getCurrent()->getNext()); //Creamos un nodo que tenga un puntero anterior al item actual, y un puntero siguiente al item siguiente del actual

						this->gotoNext();
						this->getCurrent()->setPrevious(aux); //Conectamos el puntero anterior del item siguiente del actual al nuevo nodo

						this->gotoPrevious();
						this->gotoPrevious();
						this->getCurrent()->setNext(aux); //Conectamos el puntero siguiente del item actual al nuevo nodo

						this->gotoNext(); //para situar el cursor en el nuevo nodo
						break;
					}
					else{

						if(this->isLastItem()){break;}
						this->gotoNext();
					}

				}
			}
		}
	}

	#ifndef NDEBUG
		assert(this->getCurrentItem()==m);
		assert(this->nItems()==old+1);
	#endif
}

void ed::ListaDoblementeEnlazadaOrdenadaMunicipios::remove(){
	#ifndef NDEBUG
		assert(this->isEmpty()==false);
	#endif

	//Si la lista está vacía no se puede borrar nada
	if(this->getCurrent()==NULL){
		return;
	}
	else{

		//Si borramos el único elemento que hay en la lista
		if(this->isFirstItem() && this->isLastItem()){

			this->getCurrent()->setPrevious(NULL);
			this->getCurrent()->setNext(NULL);
			_head=NULL;
			_current=NULL;

		}
		else{

			//Si borramos el primer elemento
			if(this->isFirstItem()){
	
				this->getCurrent()->getNext()->setPrevious(NULL);
				this->setHead(this->getCurrent()->getNext()); //Actualizamos la cabeza
				this->getCurrent()->setNext(NULL); //Desconectamos el nodo de la lista
	
				this->gotoHead(); //Situamos el cursor
	
			}
			else{
	
				//Si borramos el último elemento
				if(this->isLastItem()){
	
					this->getCurrent()->getPrevious()->setNext(NULL);
					this->getCurrent()->setPrevious(NULL);
	
					this->gotoLast();
	
				}
				else{
	
					//Borramos cualquier otro elemento
					this->getCurrent()->getPrevious()->setNext(this->getCurrent()->getNext());
					this->getCurrent()->getNext()->setPrevious(this->getCurrent()->getPrevious());
	
					this->setCurrent(this->getCurrent()->getNext());
	
				}
			}
		}
	}
}

void ed::ListaDoblementeEnlazadaOrdenadaMunicipios::removeAll(){
	while(this->nItems()!=0){
		this->gotoHead();
		this->remove();
	}

	/*Como estamos situados en la cabeza, siempre borraremos desde arriba, ya que el cursor se mantiene siempre ahí*/

	#ifndef NDEBUG
		assert(this->isEmpty());
	#endif
}
