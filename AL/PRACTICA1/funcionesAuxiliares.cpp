#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <algorithm>
#include <fstream>
#include "funcionesAuxiliares.hpp"

int menu(){
	int opcion;
	int posicion;

	posicion=2;
	std::cout<<CLEAR_SCREEN;

	PLACE(1,10);
	std::cout<<BIBLUE;
	std::cout<<"Programa principal | Opciones del menu";
	std::cout<<RESET;

	////////////////////////////////////////////////////////
	posicion++;

	PLACE(posicion++,10);
	std::cout<<"[1] Metodo burbuja\n";
	////////////////////////////////////////////////////////
	posicion++;

	PLACE(posicion++,10);
	std::cout<<"[2] Metodo por contabilizacion de frecuencias\n";
	////////////////////////////////////////////////////////
	posicion++;

	PLACE(posicion++,10);
	std::cout<<BIGREEN;
	std::cout<<"Opcion: ";
	std::cout<<RESET;

	//Se lee el número de opción
	std::cin>>opcion;

	//Se elimina el salto de línea del flujo de entrada
	std::cin.ignore();

	return opcion;
}

void rellenarVector(std::vector<int> &v,int i){
	int num;

	for (int n=0;n<i;n++){
		num=rand()%10000;
		v.push_back(num);
	}

}

void pedirValores(double &min,double &max,double &inc,double &rep){
	std::cout<<"Valor minimo del numero de elementos del vector: "<<std::endl;
	std::cin>>min;
	std::cout<<"Valor maximo del numero de elementos del vector: "<<std::endl;
	std::cin>>max;
	std::cout<<"Incremento del valor del numero de elementos: "<<std::endl;
	std::cin>>inc;
	std::cout<<"Número de repeticiones de la ordenacion para cada numero de elementos: "<<std::endl;
	std::cin>>rep;

	assert(min<=max);
	assert(min>0);
	assert(inc>0);
	assert(rep>0);
}

void ordenacionBurbuja(std::vector<int> & v){
	assert(!v.empty());

	int tiem=v.size();
	int temp;

	for(int i=1;i<tiem;i++){
		for(int j=tiem-1;j>=i;j--){
			if(v.at(j)<v.at(j-1)){
				temp=v.at(j);
				v.at(j)=v.at(j-1);
				v.at(j-1)=temp;
			}
		}
	}
}

void ordenacionFrecuencias(std::vector<int> & v){
	assert(!v.empty());

	std::vector<int> aux;
	int contador=0;

//	aux.resize(10000,0);
	for(unsigned i=0;i<v.size();i++){
		aux[v[i]]= aux[v[i]]+1;
	}
	for(unsigned j=0;j<aux.size();j++){
		if(aux[j]>0){
			for(int k=0;k<aux[j];k++){
				v[contador]=j;
				contador++;
			}
		}
	}
}

void estaOrdenado(const std::vector<int> &v){
	
	for(unsigned i=1;i<v.size();i++){
		assert(v.at(i)>=v.at(i-1));
	}
}

void almacenarMetodo(std::string nombre,std::vector<double> &n,std::vector<double> &t,std::vector<double> &tEstimados){
	assert(!n.empty());
	assert(!t.empty());
	assert(!tEstimados.empty());

	std::ofstream f(nombre.c_str());

	for(unsigned i=0;i<n.size();i++){
		f << n.at(i) << " " << t.at(i) << " " << tEstimados.at(i) << "\n"; 
	}

	f.close();
}

double calcularVarianza(std::vector<double> v){
	assert(!v.empty());

	double media=0;
	double varianza=0;

	for(unsigned i=0;i<v.size();i++){
		media+=v[i];
	}
	media=media/v.size();

	for(unsigned i=0;i<v.size();i++){
		varianza=varianza+(v[i]-media)*(v[i]-media);
	}
	varianza=varianza/v.size();

	return varianza;
}
