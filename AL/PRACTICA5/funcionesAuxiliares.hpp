#ifndef _FUNCIONES_AUXILIARES_HPP
#define _FUNCIONES_AUXILIARES_HPP

#include <vector>
#include <string>
#include <cstdlib>
#include <fstream>
#include <cassert>
#include <limits>
#include <algorithm>
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
void cambio2(float n,Conjunto &valores,std::vector<std::vector<float> > &tabla);
void mochila2(float volumen,std::vector<Material> &v,std::vector<std::vector<float> > &tabla);
/*---------------------------------------------------------*/
float maximoConjunto(Conjunto &c,float s,float n);
float min(float n1,float n2);
float max(float n1,float n2);
int tam(std::vector<float> v);
int tam(std::vector<Material> v);
void ordenacionFrecuencias(std::vector<float> & v);
/*---------------------------------------------------------*/
void imprimirConjunto(std::vector<std::vector<float> > &c,float n,Conjunto &valores);
void imprimirMochila(std::vector<std::vector<float> > &c,int volumen,std::vector<Material> &v);

#endif
