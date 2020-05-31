/*!
 \mainpage Menú del grafo
 \author   Alejandro Fuerte Jurado
 \date     2018-5-30
 \version  1.0
*/

/*!
	\file main.cpp
	\brief Programa principal de la practica 4 de Estructuras de Datos
*/

#include <iostream>
#include <string>

#include "funcionesAuxiliares.hpp"
#include "Graph.hpp"
#include "Vertex.hpp"
#include "Edge.hpp"
#include "macros.hpp"

int main(){
	int opcion;
	ed::Graph *grafo=NULL;
	bool prim=false;
	bool kruskal=false;
	ed::Graph grafoPrim;
	ed::Graph grafoKruskal;

	do{
		opcion=ed::menu();

		std::cout<<CLEAR_SCREEN;
		PLACE(3,1);

		switch(opcion){
			case 0:
				std::cout<<INVERSE;
				std::cout<<"Fin del programa"<<std::endl;
				std::cout<<RESET;
			break;

			case 1:
				std::cout<<"[1] Cargar vértices desde un fichero\n";

				ed::cargarFichero(grafo);
			break;

			case 2:
				std::cout<<"[2] Mostrar el grafo por pantalla\n";
				if(grafo!=NULL){
					ed::mostrarGrafoPantalla(*grafo);
				}
				else{std::cout<<"Grafo vacio"<<std::endl;}
			break;

			case 3:
				std::cout<<"[3] Aplicar el algoritmo de Prim\n";
				if(grafo!=NULL){
					grafoPrim=ed::aplicarAlgoritmoPrim(*grafo);
					prim=true;
				}
				else{std::cout<<"Grafo vacio"<<std::endl;}
			break;

			case 4:
				std::cout<<"[4] Aplicar el algoritmo de Kruskal\n";
				if(grafo!=NULL){
					grafoKruskal=ed::aplicarAlgoritmoKruskal(*grafo);
					kruskal=true;
				}
				else{std::cout<<"Grafo vacio"<<std::endl;}
			break;

			case 5:
				std::cout<<"[5] Mostrar el arbol abarcador de coste minimo\n";
				if(grafo!=NULL && ((prim==true)|(kruskal==true))){
					ed::mostrarAbarcadorCosteMinimo(*grafo,grafoPrim.getMatriz(),grafoKruskal.getMatriz(),prim,kruskal);
				}
				else{
					if(prim==false && kruskal==false && grafo!=NULL){std::cout<<"No se ha aplicado ningun algoritmo (Prim/Kruskal)"<<std::endl;}
					else{std::cout<<"Grafo vacio"<<std::endl;}
				}
			break;

			case 6:
				std::cout<<"[6] Mostrar la longitud total del arbol abarcador de coste minimo\n";
				if(grafo!=NULL && prim==true){
//					ed::mostrarLongitudAbarcadorCosteMinimo(*grafo);
				}
				else{
					if(prim==false && kruskal==false && grafo!=NULL){std::cout<<"No se ha aplicado ningun algoritmo (Prim/Kruskal)"<<std::endl;}
					else{std::cout<<"Grafo vacio"<<std::endl;}
				}
			break;

			default:
				std::cout << BIRED;
				std::cout << "Opción incorrecta ";
				std::cout << RESET;
				std::cout << "--> ";
			  	std::cout << ONIRED;
				std::cout << opcion << std::endl;
				std::cout << RESET;
		}

		if (opcion !=0){
			PLACE(25,1);
			std::cout << "Pulse ";
			std::cout << BIGREEN;
			std::cout << "ENTER";
			std::cout << RESET;
			std::cout << " para mostrar el ";
			std::cout << INVERSE;
			std::cout << "menú"; 
			std::cout << RESET;

			// Pausa
			std::cin.ignore();

			std::cout << CLEAR_SCREEN;
    	}
	}while(opcion!=0);

	return 0;
}
