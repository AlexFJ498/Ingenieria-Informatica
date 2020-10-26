#ifndef _AUXILIARES_
#define _AUXILIARES_

#include "util.h"


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>  // To establish the seed srand() and generate pseudorandom numbers rand()
#include <limits>
#include <math.h>
#include <vector>


using namespace imc;
using namespace std;
using namespace util;

// Fichero contenedor de todo tipo de funcinalidades auxiliares

//STOII: funcion sustituta de stoi
int stoii(string aux){
  int valor = atoi(aux.c_str());
  return valor;
}

//STODD: funcion sustita de stod
double stodd(string aux){
  double valor = double(atof(aux.c_str()));
  return valor;
}

// SPLIT: separar el contenido de una cadena de enteros, y devolverlos en forma de vector
vector<double> split(string cadena){
  char separador = ' ';

  vector<double> valores;

  //Obtenemos las posiciones de los espacios
  vector<int> espacios;
  for(int i = 0; i < int(cadena.length()); i++){
  	if(cadena[i] == separador){
      espacios.push_back(i);
    }
  }


  //Obtenemos los valores
  if(espacios.size() == 1){
    int pos = espacios[0];
    int pos_final;
    pos_final = cadena.length()-1;
    valores.push_back(stodd(cadena.substr(0, pos)));
    valores.push_back(stodd(cadena.substr(pos, pos_final)));
  }
  else{
    for (int i = 0; i < int(espacios.size()); ++i)
    {
      int pos = espacios[i];
      int pos_final;
      if(i == 0){
        pos_final = espacios[i+1];
        valores.push_back(stodd(cadena.substr(0, pos)));
        pos_final = espacios[i+1];
        valores.push_back(stodd(cadena.substr(pos, pos_final)));
      }
      else if (i < (int(espacios.size())-1)){
        pos_final = espacios[i+1];
        valores.push_back(stodd(cadena.substr(pos, pos_final)));
      }
      else{
        pos_final = cadena.length()-1;
        valores.push_back(stodd(cadena.substr(pos, pos_final)));
      }
    }
  }


  return valores;
}

// RESERVA: reserva la memoria para una matriz de valores de tipo double
void reserva(double** &m, int filas, int columnas)
{
  m = new double * [filas];
  for(int i = 0; i < filas; i++){
    m[i] = new double [columnas];
  }
}

// RELLENA: rellena una matriz de doubles con valores '1.5'
void rellena(double** m, int filas, int columnas){
  for(int i = 0; i < filas; i++){
    for(int j = 0; j < columnas; j++){
      m[i][j] = 1.5;
    }
  }
}

// PRINTVECTOR: usada en print network
void printVector(double *v, int n){
  cout<<"{ ";
  for (int i = 0; i < n; i++) {
    if(i == (n-1)){ // Ultimo valor
      cout<<v[i]<<" }";
    }
    else{
      cout<<v[i]<<" , ";
    }
  }
}

// PRINTDATASET
void printDataset(Dataset* d){
  cout<<"Numero de patrones: "<<d->nOfPatterns<<endl;
  cout<<"Numero de valores input: "<<d->nOfInputs<<endl;
  cout<<"Numero de valores output: "<<d->nOfOutputs<<endl;
  cout<<"Matriz de inputs: "<<endl;
  for(int i = 0; i < d->nOfPatterns; i++){
    printVector(d->inputs[i], d->nOfInputs); cout<<endl;
  }
  cout<<"Matriz de outputs: "<<endl;
  for(int i = 0; i < d->nOfPatterns; i++){
    printVector(d->outputs[i], d->nOfOutputs); cout<<endl;
  }
}


// copiarDataset
void copiarDataset(Dataset* d, Dataset* copia){
  copia->nOfPatterns = d->nOfPatterns;
  copia->nOfInputs = d->nOfInputs;
  copia->nOfOutputs = d->nOfOutputs;
  reserva(copia->inputs, copia->nOfPatterns, copia->nOfInputs);
  reserva(copia->outputs, copia->nOfPatterns, copia->nOfOutputs);
  for(int i = 0; i < d->nOfPatterns; i++){
    for (int j = 0; j < copia->nOfInputs; j++) {
      copia->inputs[i][j] = d->inputs[i][j];
    }
  }
  for(int i = 0; i < d->nOfPatterns; i++){
    for (int j = 0; j < copia->nOfOutputs; j++) {
      copia->outputs[i][j] = d->outputs[i][j];
    }
  }
}

// MAYOR: devuelve la posicion del mayor valor de un vector
int mayor(double* v, int num){
  int mayor_pos = 0;
  for (int i = 1; i < num; i++) {
    if(v[mayor_pos] < v[i]){
      mayor_pos = i;
    }
  }
  return mayor_pos;
}

#endif
