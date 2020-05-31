#include <iostream>
#include <cstdlib>
#include <string>
#include "funcionesAuxiliares.hpp"
#include "conjunto.hpp"
#include "macros.hpp"

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
				implementarAlgoritmoCambio();
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
