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
	std::cout<<"[1] Implementar algoritmo del problema de las n reinas mediante backtracking\n";
	////////////////////////////////////////////////////////
	posicion++;

	PLACE(posicion++,10);
	std::cout<<"[2] Implementar algoritmo del problema de las n reinas mediante el algoritmo de las Vegas\n";
	////////////////////////////////////////////////////////
	posicion++;

	PLACE(posicion++,10);
	std::cout<<"[3] Obtener numero medio de pruebas para obtener solucion con algoritmo de las Vegas\n";
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

void reinasBacktracking(bool unaSolucion){
	int n;
	int k=0;
	std::vector<int> x;
	std::vector<Reina> resultado;

	Reina r;

	std::cout<<"Numero de reinas: ";
	std::cin>>n;
	if(n<4){
		std::cout<<"Valor erroneo"<<std::endl;
		std::cin.ignore();
		return;
	}

	x.resize(n);
	x[0]=0;
	while(k>=0){
		x[k]=x[k]+1;

		while((x[k]<=n) && (lugar(k,x)==false)){
			x[k]=x[k]+1;
		}

		if(x[k]<=n){
			if(k==n-1){
				r.solucion=x;
				resultado.push_back(r);
				if(unaSolucion){
					std::cin.ignore();
					break;
				}
			}
			else{
				k++;
				x[k]=0;
			}
		}
		else{
			k--;
		}
	}
	imprimirReinas(resultado);
	std::cin.ignore();
}

bool lugar(int k,std::vector<int> &x){
	for(int i=0;i<k;i++){
		if((x[i]==x[k]) || (abs(x[i]-x[k])==abs(i-k))){
			return false;
		}
	}
	return true;
}

void imprimirReinas(std::vector<Reina> &resultado){
	for(unsigned int j=0;j<resultado.size();j++){
		std::cout<<"Solucion "<<j+1<<":"<<std::endl;
		for(unsigned int i=0;i<resultado[j].solucion.size();i++){
			std::cout<<"Reina "<<i+1<<": columna "<<resultado[j].solucion[i]<<std::endl;
		}
		std::cout<<"-------------------"<<std::endl;
	}
}

void imprimirReinas(std::vector<int> &x){
	for(unsigned int i=0;i<x.size();i++){
		std::cout<<"Reina "<<i+1<<": columna "<<x[i]<<std::endl;
	}
}

void repetirVegas(){
	srand(time(NULL));
	int n;
	int intentos=0;
	std::cout<<"Numero de reinas: ";
	std::cin>>n;
	if(n<4){
		std::cout<<"Valor erroneo"<<std::endl;
		std::cin.ignore();
		return;
	}

	bool exito;
	std::vector<int> x;
	x.resize(n);

	do{
		intentos++;
		exito=reinasVegas(n,x);
	}while(exito==false);

	imprimirReinas(x);
	std::cout<<"\nNumero de intentos: "<<intentos<<std::endl;
	std::cout<<std::endl;
	std::cin.ignore();
}

void repetirVegas(int n,int &intentos){
	intentos=0;

	bool exito;
	std::vector<int> x;
	x.resize(n);

	do{
		intentos++;
		exito=reinasVegas(n,x);
	}while(exito==false);

	imprimirReinas(x);
	std::cout<<"\nNumero de intentos: "<<intentos<<std::endl;
}

bool reinasVegas(int n,std::vector<int> &x){
	int k;
	int contador;
	std::vector<int> aux;

	aux.resize(n);

	for(int i=0;i<n;i++){
		x[i]=0;
	}

	//Se han colocado k-1 reinas y se buscan todas las posiciones para la k-ésima
	for(k=0;k<n;k++){
		contador=0;

		for(int j=0;j<n;j++){
			x[k]=j+1; //probamos la reina k en la columna j
			if(lugar(k,x)){
				//Se puede colocar en la columna j
				contador++;
				aux.push_back(j+1);
			}
		}

		if(contador==0){
			//No se ha encontrado posición para la reina k
			return false;
		}
		x[k]=aux[rand()%aux.size()];
		aux.clear();
	}

	if(contador==0){
		return false; //No hay solución
	}
	return true; //Hay solución
}

void ampliacionVegas(){
	srand(time(NULL));
	int n,rep,intentos;
	int media=0;

	std::cout<<"Numero de reinas: ";
	std::cin>>n;
	if(n<4){
		std::cout<<"Valor erroneo"<<std::endl;
		std::cin.ignore();
		return;
	}

	std::cout<<"Numero de repeticiones: ";
	std::cin>>rep;
	if(rep<1){
		std::cout<<"Valor erroneo"<<std::endl;
		std::cin.ignore();
		return;
	}

	for(int i=0;i<rep;i++){
		repetirVegas(n,intentos);
		media+=intentos;
	}

	std::cout<<"Numero medio de pruebas: "<<media/rep<<std::endl;
	std::cin.ignore();
	std::cin.ignore();
}

