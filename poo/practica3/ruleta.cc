#include <cstdlib>
#include <fstream>
#include "ruleta.h"

bool Ruleta::setBanca(int ba){
	if(ba<0){
		return false;
	}
	else{
		banca_=ba;
		return true;
	}
	
}

bool Ruleta::setBola(int bo){
	if((bo>36)||(bo<0)){
		return false;
	}
	else{
		bola_=bo;
		return true;
	}
}

bool Ruleta::addJugador(class Jugador j){
	string fnombre=j.getDNI()+".txt";

	list<Jugador>::iterator i;
	for(i=jugadores_.begin();i!=jugadores_.end();i++){
		if(i->getDNI()==j.getDNI()){
			return false;
		}
	}

	jugadores_.push_back(j);

	ifstream fentrada(fnombre.c_str());
	if(!fentrada){
		ofstream fentrada(fnombre.c_str());
	}
	fentrada.close();
	return true;
	
}

int Ruleta::deleteJugador(string dni){
	if(jugadores_.size()==0){
		return -1;
	}

	list <Jugador>::iterator i;

	for(i=jugadores_.begin();i!=jugadores_.end();i++){
		if(i->getDNI()==dni){
			jugadores_.erase(i);
			return 1;
		}
	}

	return -2;
}

int Ruleta::deleteJugador(class Jugador j){
	return deleteJugador(j.getDNI());
}

void Ruleta::escribeJugadores(){
	ofstream fsalida("jugadores.txt");

	list <Jugador>::iterator i;

	for(i=jugadores_.begin();i!=jugadores_.end();i++){
		fsalida<<i->getDNI()<<","<<i->getCodigo()<<","<<i->getNombre()<<","<<i->getApellidos()<<","<<i->getDireccion()<<","<<i->getLocalidad()<<","<<i->getProvincia()<<","<<i->getPais()<<","<<i->getDinero()<<"\n";
	}
	fsalida.close();
}

void Ruleta::leeJugadores(){
	ifstream fentrada("jugadores.txt");

	jugadores_.clear();

	char dni[10],codigo[10],nombre[10],apellidos[10],direccion[10],localidad[10],provincia[10],pais[10],dinero[10];

	Jugador j("pruebadni","pruebacodigo");

	while(fentrada.getline(dni,256,',')){		
		fentrada.getline(codigo,256,',');
		fentrada.getline(nombre,256,',');
		fentrada.getline(apellidos,256,',');
		fentrada.getline(direccion,256,',');
		fentrada.getline(localidad,256,',');
		fentrada.getline(provincia,256,',');
		fentrada.getline(pais,256,',');
		fentrada.getline(dinero,256,'\n');

		j.setDNI(dni);
		j.setCodigo(codigo);
		j.setNombre(nombre);
		j.setApellidos(apellidos);
		j.setDireccion(direccion);
		j.setLocalidad(localidad);
		j.setProvincia(provincia);
		j.setPais(pais);
		j.setDinero(atoi(dinero));
		jugadores_.push_back(j);
	}
	fentrada.close();
}

void Ruleta::giraRuleta(){
	srand(time(NULL));

	bola_=rand()%37;

	nLanzamientos_++;
}

void Ruleta::getPremios(){
	list<Jugador>::iterator j;
	list<Apuesta>::iterator p;

	list<Apuesta> aux;

	for(j=jugadores_.begin();j!=jugadores_.end();j++){
		j->setApuestas();
		aux=j->getApuestas();

		for(p=aux.begin();p!=aux.end();p++){
			switch(p->tipo){
				case 1:{
					if(atoi((p->valor).c_str())==bola_){
						j->setDinero(j->getDinero()+(p->cantidad*35));
						banca_-=p->cantidad*35;
						cantGanada_-=p->cantidad*35;
					}
					else{
						j->setDinero(j->getDinero()-p->cantidad);
						banca_+=p->cantidad;
						cantGanada_+=p->cantidad;
					}
				}break;

				case 2:{
					if(bola_!=0 && p->valor==color(bola_)){
						j->setDinero(j->getDinero()+p->cantidad);
						banca_-=p->cantidad;
						cantGanada_-=p->cantidad;
					}
					else{
						j->setDinero(j->getDinero()-p->cantidad);
						banca_+=p->cantidad;
						cantGanada_+=p->cantidad;
					}
				}break;

				case 3:{
					if(bola_!=0 && p->valor==parImpar(bola_)){
						j->setDinero(j->getDinero()+p->cantidad);
						banca_-=p->cantidad;
						cantGanada_-=p->cantidad;
					}
					else{
						j->setDinero(j->getDinero()-p->cantidad);
						banca_+=p->cantidad;
						cantGanada_+=p->cantidad;
					}
				}break;

				case 4:{
					if(bola_!=0 && p->valor==altoBajo(bola_)){
						j->setDinero(j->getDinero()+p->cantidad);
						banca_-=p->cantidad;
						cantGanada_-=p->cantidad;
					}
					else{
						j->setDinero(j->getDinero()-p->cantidad);
						banca_+=p->cantidad;
						cantGanada_+=p->cantidad;
					}
				}break;
			}
		}
	}
}

string Ruleta::color(int n){
	switch(n){
		case 1:
		case 3:
		case 5:
		case 7:
		case 9:
		case 12:
		case 14:
		case 16:
		case 18:
		case 19:
		case 21:
		case 23:
		case 25:
		case 27:
		case 30:
		case 32:
		case 34:
		case 36:
			return "rojo";
		default:
			return "negro";
	}
}

string Ruleta::parImpar(int n){
	if(n%2==0){
		return "par";
	}
	else{
		return "impar";
	}
}

string Ruleta:: altoBajo(int n){
	if(n>0 && n<19){
		return "bajo";
	}
	else{
		return "alto";
	}
}

void Ruleta::getEstadoRuleta(int &nJug,int &dineroMesa, int &nLanzamientos, int &dineroBanca){
	dineroMesa=0;

	//número de jugadores
	nJug=jugadores_.size();

	//suma de dinero en la mesa
	list<Apuesta>::iterator a;
	list<Jugador>::iterator j;
	
	list<Apuesta> aux;

	for(j=jugadores_.begin();j!=jugadores_.end();j++){
		j->setApuestas();
		aux=j->getApuestas();

		for(a=aux.begin();a!=aux.end();a++){
			dineroMesa+=a->cantidad;
		}
	}
	dineroMesa+=banca_;

	//número de lanzamientos de la bola
	nLanzamientos=nLanzamientos_;

	//Cantidad ganada o perdida de la banca
	dineroBanca=cantGanada_;
}
