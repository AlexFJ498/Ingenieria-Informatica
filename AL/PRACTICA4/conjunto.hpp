#ifndef _CONJUNTO_
#define _CONJUNTO_

#include <vector>
#include <iostream>

class Conjunto{
	private:
		std::vector<float> _elementos;

	public:
		/*Constructor*/
		Conjunto(){
			std::vector<float> v;
			this->_elementos=v;
		}

		/*Observadores*/
		inline std::vector<float> getElementos(){return this->_elementos;}

		/*Modificadores*/
		inline void setElementos(std::vector<float> v){this->_elementos=v;}
		inline void insertarElemento(int ele){_elementos.push_back(ele);}
        inline void modificarElemento(int ele,int n){_elementos[n]=ele;}
		inline void borrarElemento(int posicion){_elementos.erase(_elementos.begin()+posicion-1);}
		inline int accederElemento(int posicion){return _elementos.at(posicion);}
		inline int primerElemento(){return _elementos[0];}
		inline int ultimoElemento(){return _elementos.size();}
};

#endif
