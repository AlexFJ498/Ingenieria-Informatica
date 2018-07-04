#include "Edge.hpp"

bool ed::Edge::has(Vertex const &v)const{
	if(v1_==v || v2_==v){
		return true;
	}
	return false;
}

ed::Vertex ed::Edge::other(Vertex const &v)const{
	#ifndef NDEBUG
		assert(this->has(v));
	#endif

	Vertex aux;
	if(v1_==v){
		aux=v2_;
	}
	else{aux=v1_;}

	#ifndef NDEBUG
		assert(this->has(aux));
//		assert(other(aux)==v);
	#endif

	return aux;
}
