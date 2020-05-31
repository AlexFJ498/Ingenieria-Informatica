#include <iostream>
#include "dados.h"
#include <ctime>
#include <cstdlib>
#include <stdlib.h>

Dados::Dados(){
	srand(time(NULL)); 
	d1_=1;
	d2_=1;
	nlanzamientos1_=0;
	nlanzamientos2_=0;
	media1_=0;
	media2_=0;

	for(int i=0;i<5;i++){
		v1_[i]=0;
		v2_[i]=0;
	}
}

float Dados::getDado1(){

	return d1_;
	
}

float Dados::getDado2(){
	return d2_;
}

void Dados::lanzamiento(){
	float r1,r2;

	r1=rand()%6+1;
	r2=rand()%6+1;

	nlanzamientos1_++;
	nlanzamientos2_++;

	d1_=r1;
	d2_=r2;
	media1_=media1_+d1_;
	media2_=media2_+d2_;
	
	operacionesUltimos1();
	operacionesUltimos2();
}

bool Dados::setDado1(float r1){
	if((r1>0)&&(r1<7)){
		d1_=r1;
		media1_=media1_+d1_;
		nlanzamientos1_++;
		operacionesUltimos1();
		return true;
	}
	else{
		return false;
	}
}

bool Dados::setDado2(float r2){
	if((r2>0)&&(r2<7)){
		d2_=r2;
		media2_=media2_+d2_;
		nlanzamientos2_++;
		operacionesUltimos2();
		return true;
	}
	else{
		return false;
	}
}

int Dados::getSuma(){
	int s;
	
	s=d1_+d2_;

	return s;
}

int Dados::getDiferencia(){
	int d;

	d=d1_-d2_;

	return abs(d);
}

int Dados::getLanzamiento1(){
	return nlanzamientos1_;
}

int Dados::getLanzamiento2(){
	return nlanzamientos2_;
}

float Dados::getMedia1(){
	float media;
	if(media1_==0){
		return 0;
	}
	media=media1_/nlanzamientos1_;
	return media;
}

float Dados::getMedia2(){
	float media2;
	if(media2_==0){
		return 0;
	}
	media2=media2_/nlanzamientos2_;
	return media2;
}

void Dados::getUltimos1(float v1[5]){
	for(int i=0;i<5;i++){
		v1[i]=v1_[i];
	}

}

void Dados::getUltimos2(float v2[5]){
	for(int i=0;i<5;i++){
		v2[i]=v2_[i];
	}

}

void Dados::operacionesUltimos1(){
	int cont=0;
	for(int i=4;i>=0 && cont==0;i--){
		if(v1_[i]==0){
			v1_[i]=d1_;
			cont++;
		}
		if(v1_[0]!=0 && cont==0){
			v1_[4]=v1_[3];
			v1_[3]=v1_[2];
			v1_[2]=v1_[1];
			v1_[1]=v1_[0];
			v1_[0]=d1_;
			cont++;
		}
	}
}

void Dados::operacionesUltimos2(){
	int cont=0;
	for(int i=4;i>=0 && cont==0;i--){
		if(v2_[i]==0){
			v2_[i]=d2_;
			cont++;
		}
		if(v2_[0]!=0 && cont==0){
			v2_[4]=v2_[3];
			v2_[3]=v2_[2];
			v2_[2]=v2_[1];
			v2_[1]=v2_[0];
			v2_[0]=d2_;
			cont++;
		}
		
	}
}
