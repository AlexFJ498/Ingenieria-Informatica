/*!
	\file MonticuloMediciones.cpp
	\brief Fichero que contiene el código de las funciones de la clase MonticuloMediciones.
	\author
	\date
*/

//#include <vector>

#include <cassert>

#include "Medicion.hpp"

#include "MonticuloMediciones.hpp"

////////////////////////////////////////////////////////////////////////////////////

//Métodos privados de la clase MonticuloMediciones

	//COMPLETAR
ed::Medicion ed::MonticuloMediciones::getElement(int i)const{
	#ifndef NDEBUG
		assert(i>=0 and i<size());
	#endif

	for(unsigned j=0;j<vector_.size();j++){
	 	if(vector_[j]==vector_[i]){
			return vector_[j];
		}
	}
}

void ed::MonticuloMediciones::setElement(int i,Medicion m){
	#ifndef NDEBUG
		assert(i>=0 and i<size());
	#endif

	for(unsigned j=0;j<vector_.size();j++){
		if(vector_[j]==vector_[i]){
			vector_[j].setFecha(m.getFecha());
			vector_[j].setPrecipitacion(m.getPrecipitacion());
		}
	}

	#ifndef NDEBUG
		assert(this->getElement(i)==m);
	#endif
}

int ed::MonticuloMediciones::getLeftChild(int i)const{
	#ifndef NDEBUG
		assert(i>=0);
	#endif

	int indice=2*i+1;
	return indice;
}

int ed::MonticuloMediciones::getRightChild(int i)const{
	#ifndef NDEBUG
		assert(i>=0);
	#endif

	int indice=2*i+2;
	return indice;
}

int ed::MonticuloMediciones::getParent(int i)const{
	#ifndef NDEBUG
	assert(i>=1);
	#endif

	int indice=(i-1)/2;
	return indice;
}

void ed::MonticuloMediciones::shiftUp(int i){
	#ifndef NDEBUG
		assert(i>0 and i<size());
	#endif

	//Si no es la cima y el elemento actual es mayor que el padre
	if(i>0 && getElement(i).getPrecipitacion()>getElement(getParent(i)).getPrecipitacion()){
		Medicion aux=getElement(i);
		setElement(i,getElement(getParent(i)));
		setElement(getElement(getParent(i)),aux);
		shiftUp(getParent(i));
	}

	#ifndef NDEBUG
		assert(if(i>0){getElement(i).getPrecipitacion()<=getElement(getParent(i)).getPrecipitacion();
			   		if(getLeftChild(i)!=i){
 						getElement(i).getPrecipitacion()>=getElement(getLeftChild(i)).getPrecipitacion();
					}
					if(getRightChild(i)!=i){
						getElement(i).getPrecipitacion()>=getElement(getLeftChild(i)).getPrecipitacion();
					}
			   }
		);
	#endif
}
void ed::MonticuloMediciones::shiftDown(int i){
	#ifndef NDEBUG
		assert(i>=0 and i<size());
	#endif

	int n=i;
	int lC=getLeftChild(i);
	int rC=getRightChild(i);
	std::vector<Medicion>::iterator it;

	//Si el hijo izquierdo tiene menor íncice que el último y su elemento es mayor que el actual
	if(lC<it.vector_.end() && getElement(lC)>getElement(n){
		n=lC;
	}
	if(rC<it.vector_.end() && getElement(rC)>getElement(n){
		n=rC;
	}
	if(i<>n){
		Medicion aux=getElement(i);
		setElement(i,getElement(n));
		setElement(getElement(n),aux);
	}

	#ifndef NDEBUG
		assert(if(i>0{getElement(i)<=getElement(getParent(i))
			   		if(getLeftChild(i)!=i){
 						getElement(i)>=getElement(getLeftChild(i));
					}
				    if(getRightChild(i)!=i){
						getElement(i)>=getElement(getLeftChild(i));
				    }
			   }
		);
	#endif
}

bool ed::MonticuloMediciones::has(Medicion m){
	std::vector::<Medicion>::iterator it;
	for(it=vector_.begin();it!=vector_.end();it++){
		if(it==i){
			return true;
		}
	}
	return false;
}
////////////////////////////////////////////////////////////////////////////////////

//Métodos públicos de la clase MonticuloMediciones

//Observadores 
	//COMPLETAR
bool ed::MonticuloMediciones::isEmpty()const{
	if(size()==0){
		return true;
	}
	return false;
}

int ed::MonticuloMediciones::size()const{
	int size;
	size=vector_.size();
	return size;
}

Medicion ed::MonticuloMediciones::top()const{
	#ifndef NDEBUG
		assert(isEmpty()==false);
	#endif

	Medicion aux= vector_.front();

	#ifndef NDEBUG
		assert(aux==getElement(0));
	#endif
	return aux;
}

//Modificadores
	//COMPLETAR
void ed::MonticuloMediciones::insert(Medicion m){
	int i;
	vector_.push_back(m);

	i=size()-1; //posición que ocupa el último elemento
	shiftUp(i);

	#ifndef NDEBUG
		assert(isEmpty()==false
			   and has(m)==true);
	#endif
}

void ed::MonticuloMediciones::remove(){
	#ifndef NDEBUG
		assert(isEmpty()==false);
	#endif

	vector_.front()==vector_.back();
	shiftDown(0);
}

void ed::MonticuloMediciones::removeAll(){
	while(size()!=0){
		remove();
	}

	#ifndef NDEBUG
		assert(isEmpty()==true);
	#endif
}

void modify(Medicion m){
	#ifndef NDEBUG
		assert(isEmpty()==false);
	#endif

	vector_.front()==m;
	shiftDown(0);

	#ifndef NDEBUG
		assert(has(m)==true);
	#endif
}
