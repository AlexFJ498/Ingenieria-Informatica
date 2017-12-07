#include "contador.h"
#include <iostream>

Contador::Contador(int min,int max,int inicial){
	if(min<max){
		valorMin_=min;
		valorMax_=max;
		if(inicial>=min && inicial<=max){
			numero_=inicial;
		}
		else numero_=0;
	}
	else{
		numero_=0;
		valorMax_=1000;
		valorMin_=0;
	}
}

int Contador::operator=(const Contador &c){
	nValores_.push_back(this->numero_);
	*this=c.numero_;
	return c.numero_;
}

Contador Contador::operator=(int n){
	nValores_.push_back(this->numero_);
	set(n);
	return *this;
}

Contador Contador::operator++(int){
	nValores_.push_back(this->numero_);
	Contador aux=*this;
	set(numero_+1);
	return aux;
}

Contador Contador::operator++(){
	nValores_.push_back(this->numero_);
	set(numero_+1);
	return *this;
}

Contador Contador::operator--(int){
	nValores_.push_back(this->numero_);
	Contador aux=*this;
	set(numero_-1);
	return aux;
}

Contador Contador::operator--(){
	nValores_.push_back(this->numero_);
	set(numero_-1);
	return *this;
}

Contador operator+(int n,Contador &c){
	Contador aux(-999999999,999999999,0);
	aux.set(n+c.numero_);	
	return aux;
}

Contador operator+(Contador &c,int n){
	Contador aux(-999999999,999999999,0);
	aux.set(c.numero_+n);	
	return aux;
}

Contador operator-(int n,Contador &c){
	Contador aux(-999999999,999999999,0);
	aux.set(n-c.numero_);	
	return aux;
}

Contador operator-(Contador &c,int n){
	Contador aux(-999999999,999999999,0);
	aux.set(c.numero_-n);	
	return aux;
}

bool Contador::undo(int n){
	if((n>nValores_.size()) || (n<=0)){
		return false;
	}
	for(int i=0;i<n;i++){
		nValores_.pop_back();
	}
	this->numero_=nValores_.back();
	return true;
}
