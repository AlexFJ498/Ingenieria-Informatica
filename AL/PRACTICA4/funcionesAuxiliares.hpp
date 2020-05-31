#ifndef _FUNCIONES_AUXILIARES_HPP
#define _FUNCIONES_AUXILIARES_HPP

#include <vector>
#include <string>
#include <cstdlib>
#include <fstream>
#include <cassert>
#include "conjunto.hpp"
#include "material.hpp"
#include "macros.hpp"

int menu();
/*---------------------------------------------------------*/
void implementarAlgoritmoCambio();
void implementarAlgoritmoMochila();
/*---------------------------------------------------------*/
bool leerFicheroConjunto(std::string nombre,Conjunto &c);
bool leerFicheroMochila(std::string nombre,std::vector<Material> &v);
/*---------------------------------------------------------*/
void cambio(float n,Conjunto &cvalores,Conjunto &resultado);
void mochila(float volumen,std::vector<Material> &v);
/*---------------------------------------------------------*/
float maximoConjunto(Conjunto &c,float s,float n);
void ordenacionFrecuencias(std::vector<float> & v);
/*---------------------------------------------------------*/
void imprimirConjunto(Conjunto &c);
void imprimirMochila(int volumen,std::vector<Material> &v);

#endif
