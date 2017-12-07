#ifndef JUGADOR_H
#define JUGADOR_H

#include <list>
#include "persona.h"

/*La clase Jugador hereda de la clase Persona, y contiene una variable de tipo int para el dinero en euros de las apuestas de los jugadores, un código de tipo string y una lista de apuestas para cada jugador. Las apuestas son estructuras formadas por el tipo de apuesta, el valor y la cantidad*/ 

struct Apuesta{
	int tipo;
	string valor;
	int cantidad;

};

class Jugador: public Persona{

	private:
		int dinero_;
		string codigo_;
		list <Apuesta> apuestas_;

	public:
		Jugador(string dni,string co,string n="",string a="",string d="",string l="",string p="",string pa=""): Persona(dni,n,a,d,l,p,pa),codigo_(co){dinero_=1000;};  //Constructor, parámetros obligatorios: DNI y código de jugador

		inline string getCodigo() const {return codigo_;}      //Devolver código de jugador
		inline int getDinero() const {return dinero_;}         //Devolver dinero
		inline list <Apuesta> getApuestas(){return apuestas_;} //Devolver apuestas
		inline void setCodigo(string co){codigo_=co;}          //Modificar código
		inline void setDinero(int di){dinero_=di;}             //Modificar dinero
		void setApuestas();                                    //Leer del fichero DNI.txt las nuevas apuestas

};

#endif
