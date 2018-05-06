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

	Medicion aux;
	for(unsigned j=0;j<vector_.size();j++){
	 	if(vector_[j]==vector_[i]){
			aux=vector_[j];
		}
	}
	return aux;
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

	int indice=((2*i)+1);
	return indice;
}

int ed::MonticuloMediciones::getRightChild(int i)const{
	#ifndef NDEBUG
		assert(i>=0);
	#endif

	int indice=((2*i)+2);
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

/*	int iParent;
	iParent=getParent(i);

	if(getElement(iParent).getPrecipitacion()<getElement(i).getPrecipitacion()){
	std::cout<<i<<"\n";
		std::swap(getElement(iParent),getElement(i));
		shiftUp(i);
	}
*/

	//Si no es la cima y el elemento actual es mayor que el padre
	if(i>0 && getElement(i).getPrecipitacion()>getElement(getParent(i)).getPrecipitacion()){

		Medicion aux(vector_[i]);
		vector_[i]=vector_[getParent(i)];
		vector_[getParent(i)]=aux;
		
		shiftUp(i);
	}


	#ifndef NDEBUG
		if(i>0){
			assert(getElement(i).getPrecipitacion()<=getElement(getParent(i)).getPrecipitacion());
		}
		if(i>0 && getLeftChild(i)!=i && getLeftChild(i)<=size()){
 			assert(getElement(i).getPrecipitacion()>=getElement(getLeftChild(i)).getPrecipitacion());
		}
		if(i>0 && getRightChild(i)!=i && getRightChild(i)<=size()){
			assert(getElement(i).getPrecipitacion()>=getElement(getRightChild(i)).getPrecipitacion());
		}
	#endif
}
void ed::MonticuloMediciones::shiftDown(int i){
	#ifndef NDEBUG
		assert(i>=0 and i<size());
	#endif
//	int state=0;
/*while(state==0){
	lC=getLeftChild(i);
	rC=getRightChild(i);
	
	if((rC>size()-1)){
		if(lC>size()-1){
			state=-1;
		}
		else{
			if(getElement(i).getPrecipitacion()<getElement(lC).getPrecipitacion()){
				Medicion aux(vector_[i]);
				vector_[i]=vector_[lC];
				vector_[lC]=aux;
			}
			else{
				state=-1;
			}
		}
	}
	else{
		if(getElement(rC).getPrecipitacion()>getElement(lC).getPrecipitacion()){
			Medicion aux(vector_[i]);
			vector_[i]=vector_[lC];
			vector_[lC]=aux;

			i=lC;
		}
		else{
std::cout<<"hola2\n";
			Medicion aux(vector_[i]);
			vector_[i]=vector_[rC];
			vector_[rC]=aux;

			i=rC;
		}
	}
}*/

	int lC=getLeftChild(i);
	int rC=getRightChild(i);
	int n=i;
	
	if(lC<size()-1 && rC<size()-1){
		if(getElement(lC).getPrecipitacion()>getElement(rC).getPrecipitacion()){
			n=lC;
		}
		else{
			n=rC;
		}
	}

	if(getElement(i).getPrecipitacion()<getElement(n).getPrecipitacion()){
		Medicion aux(vector_[i]);
		vector_[i]=vector_[n];
		vector_[n]=aux;

		shiftDown(n);
	}

	#ifndef NDEBUG
		if(i>0){
			assert(getElement(i).getPrecipitacion()<=getElement(getParent(i)).getPrecipitacion());
		}
		if(i>0 && getLeftChild(i)!=i && getLeftChild(i)<=size()){
 			assert(getElement(i).getPrecipitacion()>=getElement(getLeftChild(i)).getPrecipitacion());
		}
		if(i>0 && getRightChild(i)!=i && getRightChild(i)<=size()){
			assert(getElement(i).getPrecipitacion()>=getElement(getRightChild(i)).getPrecipitacion());
		}
	#endif
}

bool ed::MonticuloMediciones::has(Medicion m){
	for(unsigned j=0;j<vector_.size();j++){
	 	if(vector_[j]==m){
			return true;
		}
	}
	return false;
}
////////////////////////////////////////////////////////////////////////////////////

//Métodos públicos de la clase MonticuloMediciones

//Observadores 
bool ed::MonticuloMediciones::isEmpty()const{
	if(size()==0){
		return true;
	}
	return false;
}

int ed::MonticuloMediciones::size()const{
	int size;
	size=vector_.size();
		//std::cout<<size<<"\n";
	return size;
}

ed::Medicion ed::MonticuloMediciones::top()const{
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
	if(i>0){
		shiftUp(i);
	}

	#ifndef NDEBUG
		assert(isEmpty()==false
			   and has(m)==true);
	#endif
}

void ed::MonticuloMediciones::remove(){
	#ifndef NDEBUG
		assert(isEmpty()==false);
	#endif

	Medicion aux(vector_[0]);
	vector_[0]=vector_[size()-1];
	vector_[size()-1]=aux;

	vector_.erase(vector_.end());
//	vector_.front()==vector_.back();
	if(size()>1){
		shiftDown(0);
	}
}

void ed::MonticuloMediciones::removeAll(){
	while(size()!=0){
		remove();
	}

	#ifndef NDEBUG
		assert(isEmpty()==true);
	#endif
}

void ed::MonticuloMediciones::modify(Medicion m){
	#ifndef NDEBUG
		assert(isEmpty()==false);
	#endif

	vector_[0]=m;
	shiftDown(0);

	#ifndef NDEBUG
		assert(has(m)==true);
	#endif
}

