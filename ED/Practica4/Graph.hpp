#ifndef _GRAPH_HPP_
#define _GRAPH_HPP_

#include <vector>
#include <iostream>

#include "Vertex.hpp"
#include "Edge.hpp"

namespace ed{
class Graph{
	private:
		double** matriz_; //Matriz
		std::vector<Vertex> vertices_; //Vector de vértices
		std::vector<Edge> lados_; //Vector de lados
		int cursorV_;
		int numVertices_;
		int cursorL_;
		int capacidad_;
		bool isDirected_;

	public:
		//Constructor
		Graph(int capacidad=0,bool isDirected=false);

		//Observadores
		bool isEmpty()const;
		inline bool isDirected()const{return isDirected_;}
		bool adjacent(Vertex const &u,Vertex const &v)const;
		bool hasCurrVertex()const;
		Vertex currVertex()const;
		bool hasCurrEdge()const;
		Edge currEdge()const;
		bool find(Vertex const &v)const;
		inline int getCursorV()const{return cursorV_;}
		inline int getCapacidad()const{return capacidad_;}
		inline double **getMatriz()const{return matriz_;}
		inline std::vector<Vertex> getVertices()const{return vertices_;}
		inline int getNumVertices()const{return numVertices_;}

		//Modificadores
		void addVertex(Point2D const &p);
		void addEdge(Vertex const &u,Vertex const &v,double data);
		void removeVertex();
		void removeEdge();
		inline void setCapacidad(int c){capacidad_=c;}
		/*-----Cursores-----*/
		bool findFirstVertex(Point2D const &p);
		bool findNextVertex(Point2D const &p);
		bool findFirstEdge(double data);
		bool findNextEdge(double data);
		void goToVertex(Vertex const &v);
		void goToEdge(Vertex const &u,Vertex const &v);
		void goToFirstVertex();
		bool nextVertex();
		void goToFirstEdge();
		bool nextEdge();
};
}

#endif
