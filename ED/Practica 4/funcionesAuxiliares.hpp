/*!
	\file funcionesAuxiliares.hpp
	\brief archivo con funciones auxiliares para el menu
*/

#ifndef _FUNCIONES_AUXILIARES_HPP_
#define _FUNCIONES_AUXILIARES_HPP_

#include <string>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <cmath>

#include "macros.hpp"
#include "Graph.hpp"
#include "Vertex.hpp"
#include "Edge.hpp"
#include "Point2D.hpp"

namespace ed{

	/*!
		\brief		menu del programa
	*/
	int menu();

	/*!
		\brief		carga vertices de un fichero
		\param		nombreFichero: nombre del fichero (tipos string)
	*/
	void cargarFichero(Graph *&grafo);

	double calcularDistancia(Vertex const &v1,Vertex const &v2);

	/*!
		\brief		muestra el grafo por pantalla
	*/
	void mostrarGrafoPantalla(Graph &grafo);

	/*!
		\brief		aplica el algoritmo de Prim
	*/
	Graph aplicarAlgoritmoPrim(Graph &grafo);

	/*!
		\brief		aplica el algoritmo de Kruskal
	*/
	Graph aplicarAlgoritmoKruskal(Graph &grafo);

	static bool sortEdge(Edge l1,Edge l2){return l1.getData()<l2.getData();}
	/*!
		\brief		muestra el arbol abarcador de coste minimo
	*/
	void mostrarAbarcadorCosteMinimo(Graph &grafo,double **matrizPrim,double **matrizKruskal,bool prim,bool kruskal);

	/*!
		\brief		muestra la longitud del arbol abarcador de coste minimo
	*/
	void mostrarLongitudAbarcadorCosteMinimo(Graph &grafo);
}

#endif
