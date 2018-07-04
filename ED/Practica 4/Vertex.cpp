#include "Vertex.hpp"


namespace ed{
std::ostream & operator<<(std::ostream &stream,Vertex const &v){
	stream<<v.getData().getX();
	stream<<" ";
	stream<<v.getData().getY();

	return stream;
}

std::istream & operator>>(std::istream &stream,Vertex const &v){
	std::string x,y;

	std::getline(stream,x,' ');
	std::getline(stream,y,'\n');

	v.getData().setX(atof(x.c_str()));
	v.getData().setY(atof(y.c_str()));

	return stream;
}
}
