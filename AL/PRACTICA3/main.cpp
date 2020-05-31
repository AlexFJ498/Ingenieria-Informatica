#include <iostream>
#include <cstdlib>
#include <string>
#include "funcionesAuxiliares.hpp"
#include "macros.hpp"

int main(){
	std::cout<<CLEAR_SCREEN;
	PLACE(3,1);
	std::cout<<"IMPLEMENTACION DEL ALGORITMO QUICKSORT"<<std::endl;
	std::cout<<std::endl;
	std::cout<<"Este programa implementa un algoritmo basado en quicksort para obtener los k-menores elementos de un conjunto de enteros."<<std::endl;
	std::cout<<"\n\nPulsa enter para continuar"<<std::endl;
	std::cin.ignore();
	std::cout<<CLEAR_SCREEN;
	PLACE(3,1);

	//Rellenar un vector con elementos aleatorios
	int tam;
	Conjunto c;
	Conjunto cAux; //Para guardar los k-menores
	std::cout<<"Tamano del conjunto: ";
	std::cin>>tam;

	rellenarConjunto(c,tam);

	//Realizar algoritmo de k-menores
	int k;
	int contador=0;
	std::cout<<"Valor de k: ";
	std::cin>>k;
	if(k>=tam){
		std::cout<<"Error: el valor debe ser menor que el tamano del vector"<<std::endl;
		return -1;
	}

	kMenores(0,tam-1,tam,k,c,cAux,contador);

	std::cout<<"Numero de llamadas recursivas realizadas: "<<contador<<std::endl;
	std::cout<<"\n";
	std::cout<<"¿Desea mostrar el vector resultante? [s/n]"<<std::endl;
	std::string option;
	std::cin>>option;

	if((option=="s") || (option=="S")){
		for(int i=0;i<tam;i++){
			if(encontrarValor(cAux.getElementos(),c.accederElemento(i))){
				std::cout<<BIBLUE;
				std::cout<<c.accederElemento(i)<< " ";
				std::cout<<RESET;
			}
			else{
				std::cout<<c.accederElemento(i)<< " ";
			}
		}
	}
	
	std::cout<<std::endl;

	return 0;
}
