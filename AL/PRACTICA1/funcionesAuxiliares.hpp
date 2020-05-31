#ifndef FUNCIONES_AUXILIARES_HPP
#define FUNCIONES_AUXILIARES_HPP

#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include "macros.hpp"

int menu();
void rellenarVector(std::vector<int> &v,int i);
void pedirValores(double &min,double &max,double &inc,double &rep);
void estaOrdenado(const std::vector<int> &v);
void almacenarMetodo(std::string nombre,std::vector<double> &n,std::vector<double> &t,std::vector<double> &tEstimados);
void ordenacionBurbuja(std::vector<int> &v);
void ordenacionFrecuencias(std::vector<int> &v);
double calcularVarianza(std::vector<double> v);

#endif
