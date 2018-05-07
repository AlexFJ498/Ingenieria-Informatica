/*!
  \file   funcionesAuxiliares.cpp
  \brief  Código de las funciones auxiliares para el programa principal de la práctica 1
  \author Alejandro Fuerte Jurado
  \date   07-05-2018
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#include "funcionesAuxiliares.hpp"
#include "MonticuloMediciones.hpp"
#include "Medicion.hpp"
#include "macros.hpp"

int ed::menu(){
	int opcion;
	int posicion;

	posicion=2;

	std::cout<<CLEAR_SCREEN;

	PLACE(1,10);
	std::cout << BIBLUE;
	std::cout << "Programa principial | Opciones del menú";
	std::cout << RESET;

	//////////////////////////////////////////////////////////////////////////////
	posicion++;

	PLACE(posicion++,10);
	std::cout <<  "[1] Comprobar si el monticulo tiene mediciones";

	//////////////////////////////////////////////////////////////////////////////
	posicion++;

	PLACE(posicion++,10);
	std::cout << "[2] Cargar el monticulo desde un fichero";

	PLACE(posicion++,10);
	std::cout << "[3] Grabar el monticulo en un fichero";

	//////////////////////////////////////////////////////////////////////////////
	posicion++;
 
	PLACE(posicion++,10);
	std::cout << "[4] Mostrar mediciones del monticulo";

	PLACE(posicion++,10);
	std::cout <<  "[5] Calcular tamano del monticulo";

	PLACE(posicion++,10);
	std::cout << "[6] Borrar todas las mediciones del monticulo";

	//////////////////////////////////////////////////////////////////////////////
	posicion++;

	PLACE(posicion++,10);
	std::cout << "[7] Modificar la cima del monticulo";

	PLACE(posicion++,10);
	std::cout << "[8] Insertar una medicion";

	PLACE(posicion++,10);
	std::cout << "[9] Borrar la cima del monticulo";

	//////////////////////////////////////////////////////////////////////////////
	posicion++;

	PLACE(posicion++,10);
	std::cout << BIRED << "[0] Salir";

	//////////////////////////////////////////////////////////////////////////////
	posicion++;

	PLACE(posicion++,10);
	std::cout << BIGREEN;
	std::cout << "Opción: ";
	std::cout << RESET;

	// Se lee el número de opción
	std::cin >> opcion;

    // Se elimina el salto de línea del flujo de entrada
    std::cin.ignore();

	return opcion;
}

void ed::comprobarMonticuloVacio(ed::MonticuloMediciones &monticulo){
	if(monticulo.isEmpty()==true){
		std::cout<<"El monticulo esta vacio."<<std::endl;
	}
	else{
		std::cout<<"El monticulo contiene elementos."<<std::endl;
	}
}

void ed::cargarMonticuloDeFichero(std::string const & nombreFichero,ed::MonticuloMediciones & monticulo){
	std::ifstream f;
	f.open(nombreFichero.c_str());
	if(!f.is_open()){
		std::cout<<"ERROR al abrir el fichero de mediciones\n"<<std::endl;
			std::cin.ignore();
	}
	else{
		Medicion aux;
		Fecha aux2;
		char dia[10],mes[10],anio[10],precipitacion[10];
	
		while(f.getline(dia,256,'-')){
			f.getline(mes,256,'-');
			f.getline(anio,256,' ');
			f.getline(precipitacion,256,'\n');
	
			aux2.setDia(atoi(dia));
			aux2.setMes(atoi(mes));
			aux2.setAgno(atoi(anio));
			aux.setFecha(aux2);
			aux.setPrecipitacion(atoi(precipitacion));
	
			monticulo.insert(aux);
		}
		f.close();

		std::cout<<"Monticulo cargado"<<std::endl;
		std::cin.ignore();
	}
}

void ed::grabarMonticuloEnFichero(std::string const & nombreFichero,ed::MonticuloMediciones const & monticulo){
	if(monticulo.size()==0){
		std::cout<<"El monticulo esta vacio."<<std::endl;
		std::cin.ignore();
	}
	else{
		std::ofstream f;
		f.open(nombreFichero.c_str());
		if(!f.is_open()){
			std::cout<<"ERROR al abrir el fichero\n"<<std::endl;
		}
		else{
			ed::MonticuloMediciones aux=monticulo;
			for(;!(aux.isEmpty());aux.remove()){
				f<<aux.top().getFecha()<<" "<<aux.top().getPrecipitacion()<<"\n";
			}
			f.close();
		
			std::cout<<"Se han grabado las mediciones en el fichero "<<nombreFichero<<std::endl;
			std::cin.ignore();
		}
	}
}

void ed::mostrarMedicionesDeMonticulo(ed::MonticuloMediciones &monticulo){
	monticulo.print();
	return;
}

void ed::calcularTamano(ed::MonticuloMediciones &monticulo){
	std::cout<<"El tamano del monticulo es de "<<monticulo.size()<<std::endl;
}

void ed::borrarTodasLasMedicionesDeMonticulo(ed::MonticuloMediciones &monticulo){
	monticulo.removeAll();
	std::cout<<"Mediciones borradas."<<std::endl;
}

void ed::modificarMedicionDeMonticulo(ed::MonticuloMediciones &monticulo){
	if(monticulo.size()==0){
		std::cout<<"El monticulo esta vacio."<<std::endl;
	}
	else{
		Medicion aux;
		Fecha aux2;
		int dia,mes,agno,precipitacion;
	
		std::cout<<"Nueva fecha:\n";
		std::cout<<"Dia: ";
		std::cin>>dia;
		aux2.setDia(dia);
	
		std::cout<<"Mes: ";
		std::cin>>mes;
		aux2.setMes(mes);
	
		std::cout<<"agno: ";
		std::cin>>agno;
		aux2.setAgno(agno);
		aux.setFecha(aux2);
	
		std::cout<<"\n";
		std::cout<<"Nueva precipitacion: ";
		std::cin>>precipitacion;
		aux.setPrecipitacion(precipitacion);
	
		monticulo.modify(aux);

		std::cout<<"Arbol actualizado."<<std::endl;
	}
}

void ed::insertarMedicionDeMonticulo(ed::MonticuloMediciones &monticulo){
	Medicion aux;
	Fecha aux2;
	int dia,mes,agno,precipitacion;

	std::cout<<"Insertar fecha:\n";
	std::cout<<"Dia: ";
	std::cin>>dia;
	aux2.setDia(dia);

	std::cout<<"Mes: ";
	std::cin>>mes;
	aux2.setMes(mes);

	std::cout<<"agno: ";
	std::cin>>agno;
	aux2.setAgno(agno);
	aux.setFecha(aux2);

	std::cout<<"\n";
	std::cout<<"Insertar precipitacion: ";
	std::cin>>precipitacion;
	aux.setPrecipitacion(precipitacion);

	monticulo.insert(aux);

	std::cout<<"Medicion insertada."<<std::endl;
}

void ed::borrarMedicionDeMonticulo(ed::MonticuloMediciones &monticulo){
	if(monticulo.size()!=0){
		monticulo.remove();
		std::cout<<"Medicion borrada."<<std::endl;
	}
	else{
		std::cout<<"El monticulo esta vacio."<<std::endl;
	}
}
