#include "persona.h"

Persona::Persona(string dni,string n,string a,string d,string l,string p,string pa){
	dni_=dni;
	nombre_=n;
	apellidos_=a;
	direccion_=d;
	localidad_=l;
	provincia_=p;
	pais_=pa;
}


string Persona::getApellidosyNombre(){
	apellidosynombre_=apellidos_+", "+nombre_;

	return apellidosynombre_;
}
