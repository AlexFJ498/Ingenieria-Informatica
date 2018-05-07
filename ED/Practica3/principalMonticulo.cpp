/*!
 \mainpage Implementación de un montículo de mediciones
 \author   Alejandro Fuerte Jurado
 \date     2018-3-7
 \version  1.0
*/

/*!
	\file principalMediciones.cpp
	\brief Programa principal de la practica 3 de Estructuras de Datos
*/

#include <iostream>
#include <string>

#include "funcionesAuxiliares.hpp"
#include "MonticuloMediciones.hpp"
#include "Medicion.hpp"
#include "macros.hpp"

/*! 
		\brief   Programa principal de la práctica 2: montículo de mediciones
		\return  int
*/
int main(){
	ed::MonticuloMediciones monticulo;

	int opcion;
	std::string nombreFicheroEntrada;
	std::string nombreFicheroSalida;

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
				std::cout<<"[1] Comprobar si el monticulo tiene mediciones"<<std::endl;

				ed::comprobarMonticuloVacio(monticulo);
			break;

			case 2:
				std::cout<<"[2] Cargar el monticulo desde un fichero"<<std::endl;
				std::cout<<"Introduce el nombre del fichero que contiene las mediciones" <<std::endl;
				std::cin>>nombreFicheroEntrada;
				ed::cargarMonticuloDeFichero(nombreFicheroEntrada,monticulo);
			break;

			case 3:
				std::cout<<"[3] Grabar el monticulo en un fichero"<<std::endl;
				std::cout<<"Introduce el fichero donde grabar el monticulo"<<std::endl;
				std::cin>>nombreFicheroSalida;
				ed::grabarMonticuloEnFichero(nombreFicheroSalida,monticulo);
			break;

			case 4:
				std::cout<<"[4] Mostrar mediciones del monticulo: "<<std::endl;
				ed::mostrarMedicionesDeMonticulo(monticulo);
			break;

			case 5:
				std::cout<<"[5] Calcular tamano del monticulo"<<std::endl;
				ed::calcularTamano(monticulo);
			break;

			case 6:
				std::cout<<"[6] Borrar todas las mediciones del monticulo"<<std::endl;
				ed::borrarTodasLasMedicionesDeMonticulo(monticulo);
			break;

			case 7:
				std::cout<<"[7] Modificar la cima del monticulo"<<std::endl;
				ed::modificarMedicionDeMonticulo(monticulo);
			break;

			case 8:
				std::cout<<"[8] Insertar una medicion"<<std::endl;
				ed::insertarMedicionDeMonticulo(monticulo);
			break;

			case 9:
				std::cout<<"[9] Borrar la cima del monticulo"<<std::endl;
				ed::borrarMedicionDeMonticulo(monticulo);
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
