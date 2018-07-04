#include <limits>
#include "Graph.hpp"

#define MAX 32000.0

///////////////////////////////////////////////////////////////////////////////////////////
//OBSERVADORES//

ed::Graph::Graph(int capacidad,bool isDirected){
	capacidad_=capacidad;
	isDirected_=isDirected;
	cursorV_=-1;
	numVertices_=0;
	cursorL_=-1;
	vertices_.clear();
	lados_.clear();

	//Se asigna la capacidad a la matriz
	matriz_= new double *[capacidad_];
	for(int i=0;i<capacidad_;i++){
		matriz_[i]=new double [capacidad_];
	}

	for(int j=0;j<capacidad_;j++){
		for(int k=0;k<capacidad_;k++){
			if(j==k){
				matriz_[j][k]=0; //Mismo vértice
			}
			else{
				matriz_[j][k]=MAX; //Distintos vértices
			}
		}
	}
}

bool ed::Graph::isEmpty()const{
	return vertices_.empty();
}

bool ed::Graph::adjacent(Vertex const &u,Vertex const &v)const{
	#ifndef NDEBUG
		assert(this->find(u));
		assert(this->find(v));
	#endif

	if(matriz_[u.getLabel()][v.getLabel()]!=MAX && matriz_[u.getLabel()][v.getLabel()]!=0){
		return true;
	}
	return false;
}

bool ed::Graph::hasCurrVertex()const{
	if(cursorV_!=-1){
		return true;
	}
	return false;
}

ed::Vertex ed::Graph::currVertex()const{
	#ifndef NDEBUG
		assert(this->hasCurrVertex());
	#endif

	return vertices_[cursorV_];
}

bool ed::Graph::hasCurrEdge()const{
	if(cursorL_!=-1){
		return true;
	}
	return false;
}

ed::Edge ed::Graph::currEdge()const{
	#ifndef NDEBUG
		assert(this->hasCurrEdge());
	#endif

	return lados_[cursorL_];
}

bool ed::Graph::find(Vertex const &v)const{
	for(int i=0;i<capacidad_;i++){
		if(v==vertices_[i]){
			return true;
		}
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////////
//MODIFICADORES//

void ed::Graph::addVertex(Point2D const &p){
	//La etiqueta del nuevo vértice es igual al tamaño actual del vector, porque es uno más
	int label=vertices_.size();

	#ifndef NDEBUG
		assert(label<capacidad_);
	#endif

	Vertex aux(p,label);
	vertices_.push_back(aux);
	cursorV_=label; //Se coloca el cursor
	numVertices_++;

	#ifndef NDEBUG
		assert(this->hasCurrVertex());
		assert(this->currVertex().getData()==p);
	#endif
}

void ed::Graph::addEdge(Vertex const &u,Vertex const &v,double data){
	#ifndef NDEBUG
		assert(this->find(u));
		assert(this->find(v));
	#endif

	Edge aux(u,v,data);
	lados_.push_back(aux);
	cursorL_=lados_.size()-1; //Se coloca el cursor

	matriz_[u.getLabel()][v.getLabel()]=data; //Se registra el lado en la matriz

	if(isDirected_==false){ //Se no es dirigida, el lado opuesto es el mismo, por lo que se registra
		matriz_[v.getLabel()][u.getLabel()]=data;
	}

	#ifndef NDEBUG
		assert(this->hasCurrEdge());

/*std::cout<<"first: "<<this->currEdge().getFirst()<<std::endl;
std::cout<<"second: "<<this->currEdge().getSecond()<<std::endl;
std::cout<<"v: "<<v<<std::endl;*/
		assert(this->currEdge().has(v));
		assert(this->currEdge().other(v)==u);
/*std::cout<<"currEdge().getData(): "<<this->currEdge().getData()<<std::endl;
std::cout<<"data: "<<data<<std::endl;*/
		assert(this->currEdge().getData()==data);
		if(this->isDirected()){
			assert(this->currEdge().getFirst()==u);
			assert(this->currEdge().getSecond()==v);
		}
	#endif
}

void ed::Graph::removeVertex(){
	#ifndef NDEBUG
		assert(this->hasCurrVertex());
	#endif

	//Elimina los lados que contengan el vértice que se va a borrar
	for(unsigned i=0;i<lados_.size();i++){
		if(lados_[i].has(vertices_[cursorV_])){ 
			lados_.erase(lados_.begin()+i);
			i--;
		}
	}

	//Actualiza la matriz
	for(int j=0;j<capacidad_;j++){
		if(j!=matriz_[vertices_[cursorV_].getLabel()][j]){
			matriz_[vertices_[cursorV_].getLabel()][j]=MAX;
		}
	}
	for(int i=0;i<capacidad_;i++){
		if(i!=matriz_[i][vertices_[cursorV_].getLabel()]){
			matriz_[i][vertices_[cursorV_].getLabel()]=MAX;
		}
	}

	vertices_.erase(vertices_.begin()+cursorV_-1);
	cursorV_=-1;
	numVertices_++;
}

void ed::Graph::removeEdge(){
	#ifndef NDEBUG
		assert(this->hasCurrEdge());
	#endif

	//Se cogen las etiquetas de los vértices del lado para la matriz
	matriz_[lados_[cursorL_].getFirst().getLabel()][lados_[cursorL_].getSecond().getLabel()]=MAX;

	if(this->isDirected()==false){ //Si no es dirigida se coge el opuesto también
			matriz_[lados_[cursorL_].getSecond().getLabel()][lados_[cursorL_].getFirst().getLabel()]=MAX;
	}

	lados_.erase(lados_.begin()+cursorL_-1);
	cursorL_=-1;
}

/*----------------------------------------------CURSORES----------------------------------------------*/
bool ed::Graph::findFirstVertex(Point2D const &p){
	bool state=false;
	cursorV_=-1;

	for(unsigned i=0;i<vertices_.size();i++){
		if(vertices_[i].getData()==p){
			cursorV_=i; //Colocamos el cursor donde encontramos el vértice con el mismo data
			state=true;
		}
	}

	#ifndef NDEBUG
		if(this->hasCurrVertex()){
			assert(this->currVertex().getData()==p);
		}
	#endif
	return state;
}

bool ed::Graph::findNextVertex(Point2D const &p){
	bool state=false;
	int aux=cursorV_;
	cursorV_=-1;

	for(int i=aux;i<vertices_.back().getLabel();i++){
		if(vertices_[i].getData()==p){
			cursorV_=i; //Colocamos el cursor donde encontramos el vértice con el mismo data
			state=true;
		}
	}

	#ifndef NDEBUG
		if(this->hasCurrVertex()){
			assert(this->currVertex().getData()==p);
		}
	#endif
	return state;
}

bool ed::Graph::findFirstEdge(double data){
	#ifndef NDEBUG
		assert(this->hasCurrVertex());
	#endif

	bool state=false;
	cursorL_=-1;

	for(unsigned i=0;i<lados_.size();i++){
		if(lados_[i].getData()==data){
			cursorL_=i; //Colocamos el cursor donde encontramos el lado con el mismo data
			state=true;
		}
	}

	#ifndef NDEBUG
		if(this->hasCurrEdge()){
			assert(this->currEdge().getData()==data);
		}
	#endif
	return state;
}

bool ed::Graph::findNextEdge(double data){
	#ifndef NDEBUG
		assert(this->hasCurrVertex());
	#endif

	bool state=false;
	int aux=cursorL_;
	cursorL_=-1;

	for(unsigned i=aux;i<lados_.size();i++){
		if(lados_[i].getData()==data){
			state=true;
			cursorL_=i; //Colocamos el cursor donde encontramos el lado con el mismo data
		}
	}

	#ifndef NDEBUG
		if(this->hasCurrEdge()){
			assert(this->currEdge().getData()==data);
		}
	#endif
	return state;
}

void ed::Graph::goToVertex(Vertex const &v){
	#ifndef NDEBUG
		assert(this->find(v));
	#endif

	cursorV_=v.getLabel();

	#ifndef NDEBUG
		assert(this->currVertex().getData()==v.getData());
	#endif
}

void ed::Graph::goToEdge(Vertex const &u,Vertex const &v){
	#ifndef NDEBUG
		assert(this->find(u));
		assert(this->find(v));
	#endif

	cursorL_=-1;

	for(unsigned i=0;i<lados_.size();i++){
		if(matriz_[u.getLabel()][v.getLabel()]==lados_[i].getData()){
			cursorL_=i;
			cursorV_=u.getLabel();
			break;
		}
	}

	#ifndef NDEBUG
		if(this->hasCurrEdge()){
			assert(this->currVertex()==u);
			//assert(this->currEdge().getFirst()==u);
			//assert(this->currEdge().getSecond()==v);
		}
	#endif
}

void ed::Graph::goToFirstVertex(){
	if(this->isEmpty()){
		cursorV_=-1;
	}
	else{
		cursorV_=0;
	}

	#ifndef NDEBUG
		if(this->isEmpty()){
			assert(this->hasCurrVertex()==false);
		}
	#endif
}

bool ed::Graph::nextVertex(){
	#ifndef NDEBUG
		assert(this->hasCurrVertex());
	#endif

	if(cursorV_<vertices_.back().getLabel()){
		cursorV_++;
		return true;
	}
	else{return false;}
}

void ed::Graph::goToFirstEdge(){
	#ifndef NDEBUG
		assert(this->hasCurrVertex());
	#endif

	if(lados_.size()==0){
		cursorL_=-1;
	}
	else{
		cursorL_=0;
//		cursorV_=0;
	}

/*	#ifndef NDEBUG
		if(this->hasCurrEdge() && this->isDirected()){
			assert(this->currVertex()==this->currEdge().getFirst());
		}
	#endif
*/
}

bool ed::Graph::nextEdge(){
	#ifndef NDEBUG
		assert(this->hasCurrEdge());
	#endif

	if((unsigned int)cursorL_<lados_.size()){
		cursorL_++;
		return true;
//		cursorV_++;
	}
	else{return false;}

/*	#ifndef NDEBUG
		if(this->hasCurrEdge() && this->isDirected()){
			assert(this->currVertex()==this->currEdge().getFirst());
		}
		if(this->hasCurrEdge() && this->isDirected()==false){
			assert(this->currEdge().has(this->currVertex()));
		}
	#endif
*/
}
