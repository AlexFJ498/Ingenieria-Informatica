#include <string>
#include <cstdlib>
#include "metodos.hpp"

void metodo(int opcion){
	//Declarar e introducir mínimo, máximo, incremento y número de repeticiones
	double min,max,inc,rep;
	double tiempo;
	double ele;

	pedirValores(min,max,inc,rep);

	//Declarar vector de valores de n y de valores de t
	int ene=((max-min)/inc)+1;
	std::vector<double> n;
	std::vector<double> t;
	for(ele=min;ele<=max;ele=ele+inc){
		tiempo=0;

		for(int j=0;j<rep;j++){
			Clock time;
			std::vector<int> v;
			//Rellenar vector de n elementos
			rellenarVector(v,ele);

			//Ordenar vector y medir tiempo
			if(opcion==1){
				time.start(); //Se empieza a medir el tiempo
				ordenacionBurbuja(v);
				time.stop(); //Se termina de medir el tiempo
			} else{
				time.start(); //Se empieza a medir el tiempo
				ordenacionFrecuencias(v);
				time.stop(); //Se termina de medir el tiempo
			}

			//Comprobar que la ordenación se ha realizado correctamente
			estaOrdenado(v);
			tiempo+=time.elapsed();
		}

		//Guardar la media de los tiempos en vector de tiempos y la n correspondiente en el vector de n
		t.push_back(tiempo/rep);
		n.push_back(ele);
	}

	//Sacar ecuación y sacar los tiempos estimados
	std::vector<double> tEstimados;

	if(opcion==1){
		polinomioSegundoGrado(ene,n,t,tEstimados);
	} else{
		polinomioPrimerGrado(ene,n,t,tEstimados);
	}

	//Guardar en un fichero de texto los valores de n, t y tEstimados y generar gráfica
		if(opcion==1){
		almacenarMetodo("burbuja.txt",n,t,tEstimados);
		system("./burbuja.sh");
	} else{
		almacenarMetodo("frecuencias.txt",n,t,tEstimados);
		system("./frecuencias.sh");
	}
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
	sumN=0;
	sumNcuadrado=0;
	sumT=0;
	sumNT=0;

	for(unsigned int i=0;i<n.size();i++){
		sumN=sumN+n[i];
		sumNcuadrado=sumNcuadrado+n[i]*n[i];
		sumT=sumT+t[i];
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
	sumN=0;
	sumNcuadrado=0;
	sumNcubo=0;
	sumNcuadruple=0;
	sumT=0;
	sumNT=0;
	sumNcuadradoT=0;

	for(unsigned int i=0;i<n.size();i++){
		sumN=sumN+n[i];
		sumNcuadrado=sumNcuadrado+n[i]*n[i];
		sumNcubo=sumNcubo+n[i]*n[i]*n[i];
		sumNcuadruple=sumNcuadruple+n[i]*n[i]*n[i]*n[i];
		sumT=sumT+t[i];
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
