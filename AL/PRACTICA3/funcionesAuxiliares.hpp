#ifndef _FUNCIONES_AUXILIARES_
#define _FUNCIONES_AUXILIARES_

#include <iostream>
#include <cstdlib>
#include "conjunto.hpp"

void kMenores(int iz,int de,int n,int k,Conjunto &c,Conjunto &cAux,int &contador);
void rellenarConjunto(Conjunto &c,int i);
bool encontrarValor(std::vector<int> v,int val);

#endif
