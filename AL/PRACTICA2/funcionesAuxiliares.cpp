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
	std::cout<<"[1] Calcular numeros combinatorios\n";
	////////////////////////////////////////////////////////
	posicion++;

	PLACE(posicion++,10);
	std::cout<<"[2] Calcular numero de movimientos Torres de Hanoi\n";
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

	aux.resize(10000,0);
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

void polinomioPrimerGrado(int ene,std::vector<double> &n,std::vector<double> &t,std::vector<double> &tEstimados){
	double sumN,sumNcuadrado,sumT,sumNT;
	int grado=2;

	//Declarar y reservar matriz A nxn
	std::vector<std::vector<double> > A;
	A=std::vector<std::vector<double> >(2,std::vector<double>(2));

	//Declarar y reservar matriz B nx1
	std::vector<std::vector<double> > B;
	B=std::vector<std::vector<double> >(2,std::vector<double>(1));

	//Reservar matriz X nx1
	std::vector<std::vector<double> > X;
	X=std::vector<std::vector<double> >(2,std::vector<double>(1));

	//Sumatorios
	sumN=calcularSumatorio(n);
	sumNcuadrado=calcularSumatorioCuadrado(n);
	sumT=calcularSumatorio(t);
	sumNT=0;

	for(unsigned int i=0;i<n.size();i++){
		sumNT=sumNT+n[i]*t[i];
	}

	//Rellenar matriz nxn
	A[0][0]=ene;
	A[0][1]=sumN;
	A[1][0]=sumN;
	A[1][1]=sumNcuadrado;

	//Rellenar matriz nx1
	B[0][0]=sumT;
	B[1][0]=sumNT;

	//Guardar en X los valores de las variables
	resolverSistemaEcuaciones(A,B,grado,X);

	//Guardar en tEstimados los valores de los tiempos
	double aux;
	for(unsigned int i=0;i<n.size();i++){
		aux=n[i]*X[1][0]+X[0][0];
		tEstimados.push_back(aux);
	}

	//Imprimir ecuación y coeficiente de determinacion y preguntar por una estimación de tiempos para un determinado valor
	std::cout<<"Ecuacion de la curva ajustada por minimos cuadrados:"<<std::endl;
	std::cout<<X[1][0]<<"*x+"<<X[0][0]<<std::endl;
	std::cout<<std::endl;
	std::cout<<"Coeficiente de determinacion:"<<std::endl;
	double vT,vTE;
	vT=calcularVarianza(t);
	vTE=calcularVarianza(tEstimados);
	std::cout<<vTE/vT<<std::endl;
	std::cout<<std::endl;

	std::cout<<"\n\n\n";
	std::cout<<"¿Desea hacer una estimacion de tiempos para un determinado valor? [S/N]"<<std::endl;
	string opcion;
	std::cin>>opcion;
	if(opcion=="S" || opcion=="s"){
		double valor;
		double dias;
		do{
			std::cout<<"Introduzca el valor (0 si desea terminar): ";
			std::cin>>valor;
			if(valor!=0){
				dias=X[1][0]*valor+X[0][0];
				dias=dias/86400000000; //Para pasar de microsegundos a dias
				std::cout<<std::endl;
				std::cout<<"N: "<<valor<<std::endl;
				std::cout<<"Tiempo estimado: "<<dias<<" dias"<<std::endl;
			}
		}while(valor!=0);
	}
}

void polinomioSegundoGrado(int ene,std::vector<double> &n,std::vector<double> &t,std::vector<double> &tEstimados){
	double sumN,sumNcuadrado,sumNcubo,sumNcuadruple,sumT,sumNT,sumNcuadradoT;
	int grado=3;

	//Declarar y reservar matriz A nxn
	std::vector<std::vector<double> > A;
	A=std::vector<std::vector<double> >(3,std::vector<double>(3));

	//Declarar y reservar matriz B nx1
	std::vector<std::vector<double> > B;
	B=std::vector<std::vector<double> >(3,std::vector<double>(1));

	//Reservar matriz X nx1
	std::vector<std::vector<double> > X;
	X=std::vector<std::vector<double> >(3,std::vector<double>(1));

	//Sumatorios
	sumN=calcularSumatorio(n);
	sumNcuadrado=calcularSumatorioCuadrado(n);
	sumNcubo=calcularSumatorioCubo(n);
	sumNcuadruple=calcularSumatorioCuadruple(n);
	sumT=calcularSumatorio(t);
	sumNT=0;
	sumNcuadradoT=0;

	for(unsigned int i=0;i<n.size();i++){
		sumNT=sumNT+n[i]*t[i];
		sumNcuadradoT=sumNcuadradoT+n[i]*n[i]*t[i];
	}

	//Rellenar matriz nxn
	A[0][0]=ene;
	A[0][1]=sumN;
	A[0][2]=sumNcuadrado;
	A[1][0]=sumN;
	A[1][1]=sumNcuadrado;
	A[1][2]=sumNcubo;
	A[2][0]=sumNcuadrado;
	A[2][1]=sumNcubo;
	A[2][2]=sumNcuadruple;

	//Rellenar matriz nx1
	B[0][0]=sumT;
	B[1][0]=sumNT;
	B[2][0]=sumNcuadradoT;

	//Guardar en X los valores de las variables
	resolverSistemaEcuaciones(A,B,grado,X);

	//Guardar en tEstimados los valores de los tiempos
	double aux;
	for(unsigned int i=0;i<n.size();i++){
		aux=n[i]*n[i]*X[2][0]+n[i]*X[1][0]+X[0][0];
		tEstimados.push_back(aux);
	}

	//Imprimir ecuación y coeficiente de determinacion y preguntar por una estimación de tiempos para un determinado valor
	std::cout<<"\n\n\n";
	std::cout<<"Ecuacion de la curva ajustada por minimos cuadrados:"<<std::endl;
	std::cout<<X[2][0]<<"*x2+"<<X[1][0]<<"*x+"<<X[0][0]<<std::endl;
	std::cout<<std::endl;
	std::cout<<"Coeficiente de determinacion:"<<std::endl;
	double vT,vTE;
	vT=calcularVarianza(t);
	vTE=calcularVarianza(tEstimados);
	std::cout<<vTE/vT<<std::endl;
	std::cout<<std::endl;

	std::cout<<"¿Desea hacer una estimacion de tiempos para un determinado valor? [S/N]"<<std::endl;
	string opcion;
	std::cin>>opcion;
	if(opcion=="S" || opcion=="s"){
		double valor;
		double dias;
		do{
			std::cout<<"Introduzca el valor (0 si desea terminar): ";
			std::cin>>valor;
			if(valor!=0){
				dias=X[2][0]*valor*valor+X[1][0]*valor+X[0][0];
				dias=dias/86400000000; //Para pasar de microsegundos a dias
				std::cout<<std::endl;
				std::cout<<"N: "<<valor<<std::endl;
				std::cout<<"Tiempo estimado: "<<dias<<" dias"<<std::endl;
			}
		}while(valor!=0);
	}
}

void regresionExponencial(int ene,std::vector<double> &n,std::vector<double> &t,std::vector<double> &tEstimados){
	double sumN,sumNcuadrado,sumT,sumNT;
	int grado=2;

	//Declarar y reservar matriz A nxn
	std::vector<std::vector<double> > A;
	A=std::vector<std::vector<double> >(2,std::vector<double>(2));

	//Declarar y reservar matriz B nx1
	std::vector<std::vector<double> > B;
	B=std::vector<std::vector<double> >(2,std::vector<double>(1));

	//Reservar matriz X nx1
	std::vector<std::vector<double> > X;
	X=std::vector<std::vector<double> >(2,std::vector<double>(1));

	//Sumatorios
	sumN=calcularSumatorio(n);
	sumNcuadrado=calcularSumatorioCuadrado(n);
	sumT=calcularSumatorio(t);
	sumNT=0;

	for(unsigned int i=0;i<n.size();i++){
		sumNT=sumNT+n[i]*t[i];
	}

	//Rellenar matriz nxn
	A[0][0]=ene;
	A[0][1]=sumN;
	A[1][0]=sumN;
	A[1][1]=sumNcuadrado;

	//Rellenar matriz nx1
	B[0][0]=sumT;
	B[1][0]=sumNT;

	//Guardar en X los valores de las variables
	resolverSistemaEcuaciones(A,B,grado,X);

	//Guardar en tEstimados los valores de los tiempos
	double aux;
	for(unsigned int i=0;i<n.size();i++){
		aux=(n[i]*X[1][0])+X[0][0];
		tEstimados.push_back(aux);
	}

	//Imprimir ecuación y coeficiente de determinacion y preguntar por una estimación de tiempos para un determinado valor
	std::cout<<"Ecuacion de la curva ajustada por minimos cuadrados:"<<std::endl;
	std::cout<<X[1][0]<<"*x+"<<X[0][0]<<std::endl;
	std::cout<<std::endl;
	std::cout<<"Coeficiente de determinacion:"<<std::endl;
	double vT,vTE;
	vT=calcularVarianza(t);
	vTE=calcularVarianza(tEstimados);
	std::cout<<vTE/vT<<std::endl;
	std::cout<<std::endl;

	std::cout<<"\n\n\n";
	std::cout<<"¿Desea hacer una estimacion de tiempos para un determinado valor? [S/N]"<<std::endl;
	string opcion;
	std::cin>>opcion;
	if(opcion=="S" || opcion=="s"){
		double valor;
		double dias;
		do{
			std::cout<<"Introduzca el valor (0 si desea terminar): ";
			std::cin>>valor;
			if(valor!=0){
				dias=(X[1][0]*valor)+X[0][0];
				dias=dias/86400000000; //Para pasar de microsegundos a dias
				std::cout<<std::endl;
				std::cout<<"N: "<<valor<<std::endl;
				std::cout<<"Tiempo estimado: "<<dias<<" dias"<<std::endl;
			}
		}while(valor!=0);
	}
}

double numCombRecursivo(long double n,long double k){
	if(k==0 || k==n){
		return 1;
	}
	else{
		return numCombRecursivo(n-1,k-1) + numCombRecursivo(n-1,k);
	}
}

double numCombRecursivoTablas(std::vector<std::vector<long double> >&matriz,long double n,long double k){
	if(k==0 || k==n){
		return 1;
	}
	else{
		if(matriz[n][k]!=0){return matriz[n][k];}
		else{
			long double resultado=numCombRecursivoTablas(matriz,n-1,k-1) + numCombRecursivoTablas(matriz,n-1,k);
			matriz[n][k]=resultado;
			return resultado;
		}
	}
}

double numCombIterativo(long double n,long double k){
	if((k==0) || (k==n)){
		return 1;
	}
	double resultado=n;
	double s=1;

	for(int i=n-1;i>k;i--){
		resultado=resultado*i;
	}
	for(int i=2;i<n-k;i++){
		s=s*i;
	}

	return resultado/s;
}

int factorial(int n){
	int resultado=n;

	for(int i=n-1;i<0;i--){
		resultado=resultado*i;
	}

	return resultado;
}

void movimientosTorresHanoi(int m,int i,int j){
	if(m>1){
		movimientosTorresHanoi(m-1,i,6-i-j);
		j=i;
		movimientosTorresHanoi(m-1,6-i-j,j);
	}
}

double calcularSumatorio(std::vector<double> v){
	double tam=0;

	for(unsigned int i=0;i<v.size();i++){
		tam=tam+v[i];
	}

	return tam;
}

double calcularSumatorioCuadrado(std::vector<double> v){
	double tam=0;

	for(unsigned int i=0;i<v.size();i++){
		tam=tam+v[i]*v[i];
	}

	return tam;
}

double calcularSumatorioCubo(std::vector<double> v){
	double tam=0;

	for(unsigned int i=0;i<v.size();i++){
		tam=tam+v[i]*v[i]*v[i];
	}

	return tam;
}

double calcularSumatorioCuadruple(std::vector<double> v){
	double tam=0;

	for(unsigned int i=0;i<v.size();i++){
		tam=tam+v[i]*v[i]*v[i]*v[i];
	}

	return tam;
}
