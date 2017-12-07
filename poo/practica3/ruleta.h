#ifndef RULETA_H
#define RULETA_H

#include "crupier.h"
#include "jugador.h"

/*La clase Ruleta contiene la cantidad de dinero de la banca, el número que sale en la ruleta en cada jugada, una lista de jugadores(clase Jugador) y un crupier(clase Crupier)*/

class Ruleta{
	private:
		int banca_;
		int bola_;
		list <Jugador> jugadores_;
		Crupier crupier_;
		int nLanzamientos_;	//número de lanzamientos de la bola
		int cantGanada_;  //cantidad ganada de la banca (negativa si pierde)

		string color(int n);
		string parImpar(int n);
		string altoBajo(int n);
		
	public:
		Ruleta(Crupier c):banca_(1000000),bola_(-1),crupier_(c),nLanzamientos_(0),cantGanada_(0){} //Constructor: inicia la bola a -1 y la banca a 1 millón de euros. Parámetro obligatorio: objeto de tipo Crupier

		inline int getBanca(){return banca_;}                     //Devolver dinero de la banca
		inline int getBola(){return bola_;}                       //Devolver número de la ruleta
		inline Crupier getCrupier(){return crupier_;}             //Devolver crupier
		inline list <Jugador> getJugadores(){return jugadores_;}  //Devolver jugador
		void getEstadoRuleta(int &nJug,int &dineroMesa, int &nLanzamientos, int &dineroBanca);  //Guarda el número de jugadores, la suma de dinero (jugadores y banca), número de lanzamientos y la cantidad ganada de la banca en un momento dado en la ruleta
		bool setBanca(int ba);                                    //Modificar dinero de la banca
		bool setBola(int bo);                                     //Modificar número de la ruleta
		inline void setCrupier(Crupier c){crupier_=c;}            //Modificar crupier
		bool addJugador(class Jugador j);                         //Añadir jugador a la lista y crear fichero DNI.txt de apuestas vacío (si no existe)
		int deleteJugador(string dni);                            //Borrar jugador de la lista (recibe su DNI)
		int deleteJugador(class Jugador j);                       //Borrar jugador de la lista (recibe el jugador)
		void escribeJugadores();                                  //Escribir los datos de la lista de jugadores en jugadores.txt (cada vez que se escribe se borra su contenido anterior)
		void leeJugadores();                                      //Leer datos de los jugadores de jugadores.txt y meterlos en la lista de jugadores (la lista se borra antes de añadir los jugadores)
		void giraRuleta();                                        //Girar la ruleta y obtener un número entre 0 y 36
		void getPremios();                                        //Recorrer la lista de jugadores y actualizar el dinero de cada jugador en función de la apuesta (si se ha ganado o no)
};

#endif
