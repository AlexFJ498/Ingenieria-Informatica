#ifndef METODOS_HPP
#define METODOS_HPP

#include <vector>
#include "funcionesAuxiliares.hpp"
#include "ClaseTiempo.hpp"
#include "sistemaEcuaciones.hpp"

void metodo(int opcion);
void polinomioPrimerGrado(int ene,std::vector<double> &n,std::vector<double> &t,std::vector<double> &tEstimados);
void polinomioSegundoGrado(int ene,std::vector<double> &n,std::vector<double> &t,std::vector<double> &tEstimados);

#endif
