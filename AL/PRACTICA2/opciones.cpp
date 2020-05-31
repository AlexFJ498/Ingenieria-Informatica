#include "opciones.hpp"

void numerosCombinatorios(){
	int opcion;

	std::cout<<"Elige el metodo para calcular:"<<std::endl;
	std::cout<<"[1] Usando recursividad"<<std::endl;
	std::cout<<"[2] Usando recursividad y almacenando en tablas los valores ya conocidos"<<std::endl;
	std::cout<<"[3] Algoritmo iterativo"<<std::endl;
	std::cin>>opcion;
	std::cout<<CLEAR_SCREEN;

	switch(opcion){
		case 1:{
			Clock time;
			int ene;
			double rep,tiempo;
			std::vector<double> n;
			std::vector<double> t;
			std::cout<<"[1] Usando recursividad"<<std::endl;
			std::cout<<std::endl;
			std::cout<<"Valor de n: ";
			std::cin>>ene;
			std::cout<<"Nº repeticiones: ";
			std::cin>>rep;
			std::cout<<std::endl;

			for(int i=1;i<=ene;i++){
				tiempo=0;

				for(int j=0;j<rep;j++){
					time.start(); //Medir tiempo
					for(int k=0;k<=i;k++){
						numCombRecursivo(i,k);
					}
					time.stop();

					tiempo+=time.elapsed();
				}

				//Guardar valores de k y t en los vectores
				n.push_back(i);
				t.push_back(tiempo/rep);
			}

			std::vector<double> tEstimados;
			std::vector<double> aux(ene,0);

			for(int i=0;i<ene;i++){
				aux[i]=pow(2,n[i]);
			}

			regresionExponencial(ene,aux,t,tEstimados);

			//Guardar resultados en un fichero de texto
			almacenarMetodo("recursivo.txt",n,t,tEstimados);
			system("./recursivo.sh");
		}break;

		case 2:{
			Clock time;
			int ene;
			double rep,tiempo;
			std::vector<double> n;
			std::vector<double> t;
			std::cout<<"[2] Usando recursividad y almacenando en tablas los valores ya conocidos"<<std::endl;
			std::cout<<std::endl;
			std::cout<<"Valor de n: ";
			std::cin>>ene;
			std::cout<<"Nº repeticiones: ";
			std::cin>>rep;
			std::cout<<std::endl;

			for(int i=1;i<=ene;i++){
				tiempo=0;

				for(int j=0;j<rep;j++){
					std::vector<std::vector<long double> >matriz(ene+1,std::vector<long double> (i+1,0));

					time.start(); //Medir tiempo
					for(int k=0;k<=i;k++){
						numCombRecursivoTablas(matriz,i,k);
					}
					time.stop();

					tiempo+=time.elapsed();
				}

				//Guardar valores de k y t en los vectores
				n.push_back(i);
				t.push_back(tiempo/rep);
			}

			std::vector<double> tEstimados;

			polinomioSegundoGrado(ene,n,t,tEstimados);

			//Guardar resultados en un fichero de texto
			almacenarMetodo("recursivoTablas.txt",n,t,tEstimados);
			system("./recursivoTablas.sh");
		}break;

		case 3:{
			Clock time;
			int ene;
			double rep,tiempo;
			std::vector<double> n;
			std::vector<double> t;
			std::cout<<"[3] Algoritmo iterativo"<<std::endl;
			std::cout<<std::endl;
			std::cout<<"Valor de n: ";
			std::cin>>ene;
			std::cout<<"Nº repeticiones: ";
			std::cin>>rep;
			std::cout<<std::endl;

			for(int i=1;i<=ene;i++){
				tiempo=0;

				for(int j=0;j<rep;j++){
					time.start(); //Medir tiempo
					for(int k=0;k<=i;k++){
						numCombIterativo(i,k);
					}
					time.stop();

					tiempo+=time.elapsed();
				}

				//Guardar valores de k y t en los vectores
				n.push_back(i);
				t.push_back(tiempo/rep);
			}

			std::vector<double> tEstimados;

			polinomioSegundoGrado(ene,n,t,tEstimados);

			//Guardar resultados en un fichero de texto
			almacenarMetodo("iterativo.txt",n,t,tEstimados);
			system("./iterativo.sh");
		}break;
	}
}

void torresHanoi(){
	int ene;
	double rep,tiempo;
	std::vector<double> n;
	std::vector<double> t;
	Clock time;

	std::cout<<"Numero de discos: ";
	std::cin>>ene;
	std::cout<<"Numero de repeticiones: ";
	std::cin>>rep;

	for(int i=1;i<=ene;i++){
		tiempo=0;
		for(int j=0;j<rep;j++){
			time.start(); //Medir tiempo
			movimientosTorresHanoi(i,1,2);
			time.stop();

			tiempo+=time.elapsed();
		}

		//Guardar valores de n y t en los vectores
		n.push_back(i);
		t.push_back(tiempo/rep);
	}

	std::vector<double> tEstimados;
	std::vector<double> aux(ene,0);

	for(int i=0;i<ene;i++){
		aux[i]=pow(2,n[i]);
	}

	regresionExponencial(ene,aux,t,tEstimados);

	//Guardar resultados en un fichero de texto
	almacenarMetodo("torresHanoi.txt",n,t,tEstimados);
	system("./torresHanoi.sh");
}
