#ifndef CONTADOR_H
#define CONTADOR_H

#include <list>
#include <iostream>
using namespace std;

/*La clase Contador gestiona un número entero(numero_) cuyo valor está entre un valor mínimo(valorMin_) y un valor máximo(valorMax_), y se hacen operaciones sobre este. Si en una operación el contador pasa por encima del límite superior o por debajo del límite inferior, el contador toma el valor de dicho límite. La lista nValores_ guarda los distintos valores que toma el contador(historial)*/

class Contador{
	private:
		int numero_;
		int valorMin_;
		int valorMax_;

		list <int> nValores_;

		void set(int valor){ //Comprobar si el contador se encuentra entre los límites
			if(valor>valorMax_){
				numero_=valorMax_;
			}
			else if(valor<valorMin_){
				numero_=valorMin_;
			}
			else{
				numero_=valor;
			}
		}

	public:
		Contador(int min=0,int max=1000,int inicial=0);//Parámetros: valores mínimo, máximo e inicial

		int operator=(const Contador &c);              //Asignación de un contador
		Contador operator=(int n);                     //Asignación de un entero
		Contador operator++(int);                      //c++
		Contador operator++();                         //++c
		Contador operator--(int);                      //c--
		Contador operator--();                         //--c
		friend Contador operator+(int n,Contador &c);  //n+c
		friend Contador operator+(Contador &c,int n);  //c+n
		friend Contador operator-(int n,Contador &c);  //n-c
		friend Contador operator-(Contador &c,int n);  //c-n
		bool undo(int n=1);                            //Deshacer las últimas n operaciones
		inline int get(){return numero_;}              //Devolver el contador
};

#endif
