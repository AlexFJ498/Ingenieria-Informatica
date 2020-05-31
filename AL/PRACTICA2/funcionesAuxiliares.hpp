#ifndef FUNCIONES_AUXILIARES_HPP
#define FUNCIONES_AUXILIARES_HPP

#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include "macros.hpp"
#include "sistemaEcuaciones.hpp"

int menu();
/*----------------------------------------*/
void rellenarVector(std::vector<int> &v,int i);
void pedirValores(double &min,double &max,double &inc,double &rep);
void estaOrdenado(const std::vector<int> &v);
void almacenarMetodo(std::string nombre,std::vector<double> &n,std::vector<double> &t,std::vector<double> &tEstimados);
/*----------------------------------------*/
void ordenacionBurbuja(std::vector<int> &v);
void ordenacionFrecuencias(std::vector<int> &v);
/*----------------------------------------*/
double calcularSumatorio(std::vector<double> v);
double calcularSumatorioCuadrado(std::vector<double> v);
double calcularSumatorioCubo(std::vector<double> v);
double calcularSumatorioCuadruple(std::vector<double> v);
double calcularVarianza(std::vector<double> v);
int factorial(int n);
void polinomioPrimerGrado(int ene,std::vector<double> &n,std::vector<double> &t,std::vector<double> &tEstimados);
void polinomioSegundoGrado(int ene,std::vector<double> &n,std::vector<double> &t,std::vector<double> &tEstimados);
void regresionExponencial(int ene,std::vector<double> &n,std::vector<double> &t,std::vector<double> &tEstimados);
/*----------------------------------------*/
double numCombRecursivo(long double n,long double k);
double numCombRecursivoTablas(std::vector<std::vector<long double> >&matriz,long double n,long double k);
double numCombIterativo(long double n,long double k);
void movimientosTorresHanoi(int m,int i,int j);

#endif
