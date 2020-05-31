#include <iostream>
#include "metodos.hpp"
#include "macros.hpp"
#include "funcionesAuxiliares.hpp"

int main(){
	int opcion;

	do{
		opcion=menu();
		std::cout<<CLEAR_SCREEN;
		PLACE(3,1);

		switch(opcion){
			case 0:
				std::cout<<INVERSE;
				std::cout<<"Fin del programa"<<std::endl;
				std::cout<<RESET;
			break;

			case 1:
				std::cout<<"[1] Metodo burbuja\n";
				metodo(1);
			break;

			case 2:
				std::cout<<"[2] Metodo por contabilizacion de frecuencias\n";
				metodo(2);
			break;

			default:
				std::cout<<BIRED;
				std::cout<<"Opcion incorrecta ";
				std::cout<<RESET;
				std::cout<<"--> ";
				std::cout<<ONIRED;
				std::cout<<opcion<<std::endl;
				std::cout<<RESET;
		}

		if(opcion!=0){
			PLACE(25,1);
			std::cout<<"Pulse ";
			std::cout<<BIGREEN;
			std::cout<<"ENTER";
			std::cout<<RESET;
			std::cout<<" para mostrar el ";
			std::cout<<INVERSE;
			std::cout<<"menu";
			std::cout<<RESET;

			//Pausa
			std::cin.ignore();
			std::cout<<CLEAR_SCREEN;
		}

	}while(opcion!=0);

	return 0;
}
