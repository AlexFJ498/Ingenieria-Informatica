#ifndef _FUNCIONES_AUXILIARES_
#define _FUNCIONES_AUXILIARES_

#include <iostream>
#include <cstdlib>
#include <vector>
#include "macros.hpp"

struct Reina{
	std::vector<int> solucion;
};

int menu();
void reinasBacktracking(bool unaSolucion);
bool lugar(int k,std::vector<int> &x);
void imprimirReinas(std::vector<Reina> &x);
void imprimirReinas(std::vector<int> &x);
void repetirVegas();
void repetirVegas(int n,int &intentos);
bool reinasVegas(int n,std::vector<int> &x);
void ampliacionVegas();

#endif
