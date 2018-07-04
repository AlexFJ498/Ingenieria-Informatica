/*!
  \file   funcionesAuxiliares.cpp
  \brief  Código de las funciones auxiliares para el programa principal de la práctica 4
*/

#include <limits>
#include <algorithm>
#include <iterator>

#include "funcionesAuxiliares.hpp"

#define MAX 32000.0

int ed::menu(){
	int opcion;
	int posicion;

	posicion=2;

	std::cout<<CLEAR_SCREEN;

	PLACE(1,10);
	std::cout<<BIBLUE;
	std::cout<<"Programa principal | Opciones del menu";
	std::cout<<RESET;

	//////////////////////////////////////////////////////////////////////////////
	posicion++;

	PLACE(posicion++,10);
	std::cout<<"[1] Cargar vértices desde un fichero";
	//////////////////////////////////////////////////////////////////////////////
	posicion++;

	PLACE(posicion++,10);
	std::cout<<"[2] Mostrar el grafo por pantalla";
	//////////////////////////////////////////////////////////////////////////////
	posicion++;

	PLACE(posicion++,10);
	std::cout<<"[3] Aplicar el algoritmo de Prim";
	
	PLACE(posicion++,10);
	std::cout<<"[4] Aplicar el algoritmo de Kruskal";

	PLACE(posicion++,10);
	std::cout<<"[5] Mostrar el arbol abarcador de coste minimo";

	PLACE(posicion++,10);
	std::cout<<"[6] Mostrar la longitud total del arbol abarcador de coste minimo";

	//////////////////////////////////////////////////////////////////////////////
	posicion++;

	PLACE(posicion++,10);
	std::cout << BIGREEN;
	std::cout << "Opción: ";
	std::cout << RESET;

	// Se lee el número de opción
	std::cin >> opcion;

    // Se elimina el salto de línea del flujo de entrada
    std::cin.ignore();

	return opcion;
}

void ed::cargarFichero(Graph *&grafo){
	std::string nombreFichero;
	std::cout<<"\nNombre del fichero: "<<std::endl;
	std::cin>>nombreFichero;
	std::ifstream f(nombreFichero.c_str());

	if(!f.is_open()){
		std::cout<<"Error al abrir el fichero!"<<std::endl;
			std::cin.ignore();
		return;
	}

	int n=0;
	double x,y;
	char cache[1000];
	Point2D punto;
	Vertex vertice1,vertice2;

	while(f.getline(cache,256,'\n')){
		n++;
	}

	grafo=new Graph(n,false); //Creamos un grafo no dirigido con el tamaño igual al número de nodos del fichero

	f.clear( );
	f.seekg( 0, std::ios::beg ); //Volver al comienzo del fichero

	for(int i=0;i<n;i++){
		f >> x >> y;
		punto.setX(x);
		punto.setY(y);

		grafo->addVertex(punto); //Insertamos los vértices
	}

	//Insertamos los lados
	grafo->goToFirstVertex();
	for(int j=0;j<n;j++){
		vertice1=grafo->currVertex(); //Hacemos que cada vértice se compare con el resto
		grafo->goToFirstVertex();
		for(int k=0;k<n;k++){
			vertice2=grafo->currVertex();
			double distancia=calcularDistancia(vertice1,vertice2);
			grafo->addEdge(vertice1,vertice2,distancia);
			grafo->nextVertex();
		}
		grafo->goToVertex(vertice1);
		if(vertice1.getLabel()==n-1){break;}
		grafo->nextVertex();
	}

	f.close();
	std::cout<<"Fichero cargado correctamente\n";
	std::cin.ignore();
}

double ed::calcularDistancia(Vertex const &v1,Vertex const &v2){
	double distancia,x,y;

	x=pow(v1.getData().getX()-v2.getData().getX(),2);
	y=pow(v1.getData().getY()-v2.getData().getY(),2);

	distancia=sqrt(x+y);

	return distancia;
}

void ed::mostrarGrafoPantalla(Graph &grafo){
double temp;
double **aux=grafo.getMatriz();

	for( int i=0;i<grafo.getNumVertices();i++){
		std::cout<<"|";
		for( int j=0;j<grafo.getNumVertices();j++){
			if(aux[i][j]!=32000.0){std::cout<<" "<<aux[i][j];}
			else{std::cout<<" "<<"0";}
			if(modf(aux[i][j],&temp)==0){std::cout<<"\t";}
			std::cout<<"\t";
		}
		std::cout<<"|\n|\t\t\t\t\t\t\t\t\t\t|\n";
	}
}

ed::Graph ed::aplicarAlgoritmoPrim(Graph &grafo){
	Graph aux(grafo.getCapacidad(),false);
	Point2D punto;
	std::vector<int> vistos;  //U
	std::vector<int> por_ver; //NU

	std::vector<Vertex> vertices=grafo.getVertices();

	//Insertar vértices en el nuevo grafo
	grafo.goToFirstVertex();
	do{
		punto.setX(grafo.currVertex().getData().getX());
		punto.setY(grafo.currVertex().getData().getY());
		aux.addVertex(punto);
	}while(grafo.nextVertex());

	//Nodo 0 en vistos
	vistos.push_back(0); 

	//Resto de nodos en por_ver
	for(int i=1;i<grafo.getCapacidad();i++){
		por_ver.push_back(i);
	}

	while(!por_ver.empty()){
		int Vvisto=-1; //Vértice de vistos que pertenece al lado
		int Vpor_ver=-1; //Vértice de por_ver que pertenece al lado
		double peso=MAX; //Menor peso
		std::vector<int>::iterator erase; //Copia del iterator que se borrará de por_ver

		for(std::vector<int>::iterator it=por_ver.begin();it!=por_ver.end();it++){
			for(std::vector<int>::iterator jt=vistos.begin();jt!=vistos.end();jt++){
				if(grafo.adjacent(vertices[*it],vertices[*jt])){
					grafo.goToEdge(vertices[*it],vertices[*jt]);
					if(grafo.currEdge().getData()<peso){
						peso=grafo.currEdge().getData();
						Vvisto=*jt;
						Vpor_ver=*it;
						erase=it;
					}
				}
			}
		}

		if(Vvisto!=-1 && Vpor_ver!=-1){
			aux.addEdge(vertices[Vvisto],vertices[Vpor_ver],calcularDistancia(vertices[Vvisto],vertices[Vpor_ver]));
			por_ver.erase(erase);
			vistos.push_back(Vpor_ver);
		}
		//Si el primer elemento es 0
		else{
			vistos.push_back(0);
			por_ver.erase(por_ver.begin());
		}
	}

	return aux;




/*	std::vector<double> coste;
	std::vector<int> cercano;
	std::vector<int> U;
	std::vector<int> NU;

	double minimo;
	int tamanio=0; //size of U
	int x;
	int contador;
	double **matrizGrafo=grafo.getMatriz();
	double **matriz=grafo.getMatriz();

	//matriz
	for(int i=0;i<grafo.getCapacidad();i++){
		for(int j=0;j<grafo.getCapacidad();j++){
			matriz[i][j]=MAX;
		}
	}

	//U
	U.push_back(0);
	tamanio++;

	//NU
	for(int i=1;i<grafo.getCapacidad();i++){
		NU.push_back(i);
	}

	//1. Inicializar todos los elementos de cercano con 1
	cercano.push_back(0); //primer elemento cero
	for(int i=1;i<grafo.getCapacidad();i++){
		cercano.push_back(1);
	}

	//2. Inicializar los valores de coste con C(i,0), siendo C la matriz de conexión
	for(int i=1;i<grafo.getCapacidad();i++){
		coste.push_back(matrizGrafo[i][0]);
	}

	while(tamanio<grafo.getCapacidad()){
	std::cout<<"jajaaj\n";
		//3. Calcular el nodo x al que corresponde el mínimo del vector coste
		minimo=*std::min_element(coste.begin(),coste.end());
		std::vector<double>::iterator it;
		for(it=coste.begin(),contador=0;it!=coste.end();it++){
			if(*it==minimo){
				x=contador+1; //+1 porque el elemento 0 no lo hemos contado al inicializar
				break;
			}
			contador++;
		}
	
		//4. Pasar el nodo x al conjunto U
		U.push_back(x);
		tamanio++;
		NU.erase(NU.begin()+*std::find(coste.begin(),coste.end(),x)); //Borrar el nodo x de NU
	
		//5. Seleccionar los lados (x,cercano(x)) y (cercano(x),x) como lado de la solución
		matriz[x][cercano[x]]=matrizGrafo[x][cercano[x]];
		matriz[cercano[x]][x]=matrizGrafo[cercano[x]][x];
	
		//6. Para todos los nodos de NU, si el nodo x está más cerca de ellos que el anterior más cerc	ano:
		for(unsigned int i=0;i<NU.size();i++){
			if(coste[i+1]>grafo.getMatriz()[x][i]){
				coste[i+1]=grafo.getMatriz()[x][i]; //Corregir vector coste
				cercano[i+1]=x; //Corregir vector cercano
			}
		}
	}

	return matriz;
*/
}

ed::Graph ed::aplicarAlgoritmoKruskal(Graph &grafo){
	//Ordena los lados en orden ascendente
	std::vector<Edge> lados;
	grafo.goToFirstEdge();
	do{
		lados.push_back(grafo.currEdge());
	}while(grafo.nextEdge());

	std::sort(lados.begin(),lados.end(),sortEdge);

	ed::Graph aux(grafo.getCapacidad(),false);
	std::vector<bool> prueba;
	prueba.resize(grafo.getCapacidad(),false);

	grafo.goToFirstVertex();
	do{
		//Insertamos todos los vertices
		aux.addVertex(grafo.currVertex().getData());
	}while(grafo.nextVertex());

	//Si uno de los vértices no está unido, se une (para eso sirve el vector prueba)
	for(unsigned int i=0;i<lados.size();i++){
		if((prueba[lados[i].getFirst().getLabel()]==false)||(prueba[lados[i].getSecond().getLabel()]==false)){
			aux.addEdge(lados[i].getFirst(),lados[i].getSecond(),calcularDistancia(lados[i].getFirst(),lados[i].getSecond()));
			prueba[lados[i].getFirst().getLabel()]=true;
			prueba[lados[i].getSecond().getLabel()]=true;
		}
		//Si no, se prueban si pertenecen a arboles distintos y se añade en caso afirmativo
		else{
			if(!aux.adjacent(lados[i].getFirst(),lados[i].getSecond())){
				aux.addEdge(lados[i].getFirst(),lados[i].getSecond(),calcularDistancia(lados[i].getFirst(),lados[i].getSecond()));
			}
		}
	}

	return aux;
}

void ed::mostrarAbarcadorCosteMinimo(Graph &grafo,double **matrizPrim,double **matrizKruskal,bool prim,bool kruskal){
	int n;
	double temp;
	std::cout<<"Elige el algoritmo que deseas visualizar"<<std::endl;
	std::cout<<"----------------------------------------"<<std::endl;
	std::cout<<"     1.Prim       |       2.Kruskal     "<<std::endl;

	std::cin>>n;

	switch(n){
		case 1:{
			if(prim==false){
				std::cout<<"No se ha aplicado el algoritmo de prim con anterioridad"<<std::endl;
			}
			if(prim==true){
				for( int i=0;i<grafo.getNumVertices();i++){
					std::cout<<"|";
						for( int j=0;j<grafo.getNumVertices();j++){
							if(matrizPrim[i][j]==32000.0){std::cout<<" "<<"0";}
							else{std::cout<<" "<<matrizPrim[i][j];}
							if(modf(matrizPrim[i][j],&temp)==0){std::cout<<"\t";}
							std::cout<<"\t";
						}
					std::cout<<"|\n|\t\t\t\t\t\t\t\t\t\t|\n";
				}
			}
		}break;
		case 2:{
			if(kruskal==false){
				std::cout<<"No se ha aplicado el algoritmo de kruskal con anterioridad"<<std::endl;
			}
			if(kruskal==true){
				for( int i=0;i<grafo.getNumVertices();i++){
					std::cout<<"|";
						for( int j=0;j<grafo.getNumVertices();j++){
							if(modf(matrizKruskal[i][j],&temp)!=0){std::cout<<" "<<"0";}
							else{std::cout<<" "<<matrizKruskal[i][j];}
							std::cout<<"\t";
						}
					std::cout<<"|\n|\t\t\t\t\t|\n";
				}
			}
		}break;
	}
	std::cin.ignore();
}

void ed::mostrarLongitudAbarcadorCosteMinimo(Graph &grafo){

}


/*ed::Graph *cargarVerticesFichero(std::string &nombreFichero){
	std::ifstream f(nombreFichero.c_str());
	ed::Grafo *g;
	int n=0; //Tamaño del grafo
	double x,y,dist;
	ed::Point2D p,p2;
	ed::Vertice<ed::Point2D> v1,v2;

	char cache[1000];

	while(f.getline(cache,256,'\n')){
		n++;
	}

	g=new ed::Grafo(n,false); //Crear grafo con el número de vértices

	f.clear( );
	f.seekg( 0, std::ios::beg ); //Volver al comienzo del fichero

	for(int i=0;i<n;++i){
		f >> x >> y;
		p.setX(x);
		p.setY(y);
		g->addVertex(p); //Añadir los vértices
	}

	for(int i=0;i<n;++i){
		g->setCursorV(i);
		v1=g->currVertex();
		if(i==0){
			v1.setLabel(0);
		}
		g->setCursorV(i+1);
		v2=g->currVertex();
		dist=v1.getData()-v2.getData();
		g->addEdge(v1,v2,dist); //Añadir los lados
	}

	return g;
}

void ed::crearGrafo(){
	ed::Grafo **g;
	std::string nombreFichero;

	std::cout<<"Introduce el nombre del fichero: "; //nombre del fichero donde se guardan los vértices
	std::cin>>nombreFichero;
	std::cout<<std::endl;

	std::ifstream f(nombreFichero.c_str());
	f.open(nombreFichero.c_str());
	if(!f.is_open()){
		std::cout<<"Error al abrir el fichero"<<std::endl;
		return;
	}

	*g=cargarVerticesFichero(nombreFichero); //Se añaden los vértices con este función
	std::cout<<"Vertices cargados con exito"<<std::endl;

	f.close();
}*/

