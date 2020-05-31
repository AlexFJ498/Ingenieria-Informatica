#include "funcionesAuxiliares.hpp"

/*Nombre del fichero usado para el algoritmo del cambio*/
#define CONJUNTO "valoresConjunto.txt"

/*Nombre del fichero usado para el algoritmo de la mochila*/
#define MOCHILA "valoresMateriales.txt"

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
	std::cout<<"[1] Implementar algoritmo de obtencion de cambio\n";
	////////////////////////////////////////////////////////
	posicion++;

	PLACE(posicion++,10);
	std::cout<<"[2] Implementar el problema de la mochila\n";
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

/*--------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------*/

void implementarAlgoritmoCambio(){
	std::cout<<CLEAR_SCREEN;
	PLACE(3,1);
	std::cout<<"IMPLEMENTACION DEL ALGORITMO DE OBTENCION DE CAMBIO"<<std::endl;
	std::cout<<std::endl;
	std::cout<<"Este programa implementa un algoritmo de obtencion del cambio con numero minimo de monedas o billetes para una cantidad entera de euros introducida"<<std::endl;
	std::cout<<"\n\nPulsa enter para continuar"<<std::endl;
	std::cin.ignore();
	std::cout<<CLEAR_SCREEN;
	PLACE(3,1);

	float cantidad;
	Conjunto c;
	std::cout<<"Introduce la cantidad de euros deseada"<<std::endl;
	std::cin>>cantidad;

	//Leer el fichero que contiene los valores de los billetes y/o monedas (en céntimos)
	Conjunto valores;
	if(!leerFicheroConjunto(CONJUNTO,valores)){
		std::cin.ignore();
		return;
	}

	//Realizar algoritmo
	Conjunto resultado;
	cambio(cantidad*100,valores,resultado);

	//Imprimir resultado
	std::cout<<"Numero de monedas/billetes: "<<resultado.getElementos().size()<<std::endl;
	imprimirConjunto(resultado);
	std::cin.ignore();
}

void implementarAlgoritmoMochila(){
	std::cout<<CLEAR_SCREEN;
	PLACE(3,1);
	std::cout<<"IMPLEMENTACION DEL PROBLEMA DE LA MOCHILA"<<std::endl;
	std::cout<<std::endl;
	std::cout<<"Este programa implementa el algoritmo de la mochila"<<std::endl;
	std::cout<<"\n\nPulsa enter para continuar"<<std::endl;
	std::cin.ignore();
	std::cout<<CLEAR_SCREEN;
	PLACE(3,1);

	float volumen;
	std::cout<<"Introduce el valor del volumen de la mochila"<<std::endl;
	std::cin>>volumen;

	//Leer el fichero que contiene  el volumen, precio y etiqueta de los materiales
	std::vector<Material> materiales;
	if(!leerFicheroMochila(MOCHILA,materiales)){
		std::cin.ignore();
		return;
	}

	//Realizar algoritmo
	mochila(volumen,materiales);

	//Imprimir resultado
	imprimirMochila(volumen,materiales);
	std::cin.ignore();
}

/*--------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------*/

bool leerFicheroConjunto(std::string nombre,Conjunto &c){
	std::ifstream f(nombre.c_str());

	if(!f.is_open()){
		std::cout<<"Error al leer el fichero"<<std::endl;
		return false;
	}

	char valor[100];
	while(f.getline(valor,256,'\n')){
		c.insertarElemento(atoi(valor));
	}

	return true;
}

bool leerFicheroMochila(std::string nombre,std::vector<Material> &v){
	std::ifstream f(nombre.c_str());

	if(!f.is_open()){
		std::cout<<"Error al leer el fichero"<<std::endl;
		return false;
	}

	char volumen[100],precio[100];
	while(f.getline(volumen,256,' ')){
		f.getline(precio,256,'\n');

		Material m;
		m.setEtiqueta(v.size()+1);
		m.setVolumen(atoi(volumen));
		m.setPrecio(atoi(precio));

		v.push_back(m);
	}

	return true;
}

/*--------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------*/

void cambio(float n,Conjunto &valores,Conjunto &resultado){
	int s=0;
	int x;

	while(s!=n){
		x=maximoConjunto(valores,s,n);
		if(x==0){
			return;
		}

		resultado.insertarElemento(x);
		s=s+x;
	}
}

void mochila(float volumen,std::vector<Material> &v){
	float resto=volumen;
	float precioMax,materialMax;
	bool disponible;

	//Se marcan los materiales como no usados
	for(unsigned int i=0;i<v.size();i++){
		v[i].setUsado("nada");
	}

	do{
		precioMax=0;
		materialMax=0;
		disponible=false;

		//Se selecciona el material de máximo coste
		for(unsigned int i=0;i<v.size();i++){
			if(v[i].getUsado()=="nada"){
				disponible=true;
				if(v[i].getPrecio()>precioMax){
					precioMax=v[i].getPrecio();
					materialMax=i;
				}
			}
		}

		//Comprobamos si el material de máximo coste cabe en la mochila
		if(disponible==true){
			if(resto>=v[materialMax].getVolumen()){
				v[materialMax].setUsado("total");
				resto-=v[materialMax].getVolumen();
			}
			else{
				v[materialMax].setUsado("parcial");
				resto=0;
			}
		}
	}while(resto!=0 && disponible!=false);
}

/*--------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------*/

float maximoConjunto(Conjunto &c,float s,float n){
	std::vector<float> v=c.getElementos();
	int max=0;

	ordenacionFrecuencias(v);

	for(unsigned int i=0;i<v.size();i++){
		if((v[i]+s)<=n){
			max=v[i];
		}
	}

	return max;
}

void ordenacionFrecuencias(std::vector<float> & v){
	assert(!v.empty());

	std::vector<float> aux;
	float contador=0;

	aux.resize(100000,0);
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

/*--------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------*/

void imprimirConjunto(Conjunto &c){
	std::vector<float> v=c.getElementos();

	for(unsigned int i=0;i<v.size();i++){
		if(v[i]<100){
			std::cout<<v[i]<<"cts ";
		}
		else{
			std::cout<<v[i]/100<<"€ ";
		}
	}
	std::cout<<std::endl;
}

void imprimirMochila(int volumen,std::vector<Material> &v){
	float costeT=0;
	float volumenT=0;

	std::cout<<"Materiales empleados ([etiqueta]. volumen):\n"<<std::endl;
	for(unsigned int i=0;i<v.size();i++){
		if(v[i].getUsado()=="total"){
			std::cout<<"["<<v[i].getEtiqueta()<<"]. "<<v[i].getVolumen()<<std::endl;
			costeT+=v[i].getVolumen()*v[i].getPrecio();
			volumenT+=v[i].getVolumen();
		}
	}
	for(unsigned int i=0;i<v.size();i++){
		if(v[i].getUsado()=="parcial"){
			std::cout<<"["<<v[i].getEtiqueta()<<"]. "<<v[i].getVolumen()<<std::endl;
			costeT+=(volumen-volumenT)*v[i].getPrecio();
		}
	}

	std::cout<<"\nCoste final: "<<costeT<<std::endl;
}