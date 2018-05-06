/*!
  \file   funcionesAuxiliares.cpp
  \brief  Código de las funciones auxiliares para el programa principal de la práctica 1
  \author Alejandro Fuerte Jurado
  \date   
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#include "funcionesAuxiliares.hpp"
#include "MonticuloMediciones.hpp"
#include "Medicion.hpp"
#include "macros.hpp"

void ed::cargarMonticuloDeFichero(std::string const & nombreFichero,ed::MonticuloMediciones & monticulo){
	std::ifstream f;
	f.open(nombreFichero.c_str());
	if(!f.is_open()){
		std::cout<<"ERROR al abrir el fichero de mediciones\n"<<std::endl;
		return;
	}

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
	return;
}

void ed::grabarMonticuloEnFichero(std::string const & nombreFichero,ed::MonticuloMediciones const & monticulo){
	//COMPLETAR
	std::ofstream f;
	f.open(nombreFichero.c_str());
	if(!f.is_open()){
		std::cout<<"ERROR al abrir el fichero para ordenar las mediciones\n"<<std::endl;
		return;
	}

	ed::MonticuloMediciones aux=monticulo;
	for(;!(aux.isEmpty());aux.remove()){
		f<<aux.top().getFecha()<<" "<<aux.top().getPrecipitacion()<<"\n";
	}
	f.close();
	return;
}
