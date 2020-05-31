#include <cstdlib>
#include <fstream>
#include "jugador.h"

void Jugador::setApuestas(){
	string nombref=getDNI()+".txt";
	ifstream fentrada(nombref.c_str());

	char tipo[10],valor[10],cantidad[10];

	Apuesta a;
	apuestas_.clear();

	while(fentrada.getline(tipo,256,',')){
		fentrada.getline(valor,256,',');
		fentrada.getline(cantidad,256,'\n');

		a.tipo=atoi(tipo);
		a.valor=valor;
		a.cantidad=atoi(cantidad);
		apuestas_.push_back(a);
	}
	fentrada.close();
}
