#ifndef PERSONA_H
#define PERSONA_H

#include <string>

using namespace std;

/*La clase Persona gestiona los diferentes datos de tipo string de una persona, y contiene funciones de tipo modificadores y observadores para cada dato*/
class Persona{
	private:
		string dni_;
		string nombre_;
		string apellidos_;
		string direccion_;
		string localidad_;
		string provincia_;
		string pais_;
		string apellidosynombre_;

	public:
		Persona(string dni,string n="",string a="",string d="",string l="",string p="",string pa="");     //Constructor, parámetro obligatorio: DNI
		inline void setDNI(string dni){dni_=dni;}         //Modificar DNI
		inline void setNombre(string n){nombre_=n;}       //Modificar nombre
		inline void setApellidos(string a){apellidos_=a;} //Modificar apellidos
		inline void setDireccion(string d){direccion_=d;} //Modificar dirección
		inline void setLocalidad(string l){localidad_=l;} //Modificar localidad
		inline void setProvincia(string p){provincia_=p;} //Modificar provincia
		inline void setPais(string pa){pais_=pa;}         //Modificar país
		inline string getDNI() const {return dni_;}              //Devolver DNI
		inline string getNombre() const {return nombre_;}        //Devolver nombre
		inline string getApellidos() const {return apellidos_;}  //Devolver apellidos
		inline string getDireccion() const {return direccion_;}  //Devolver dirección
		inline string getLocalidad() const {return localidad_;}  //Devolver localidad
		inline string getProvincia() const {return provincia_;}  //Devolver provincia
		inline string getPais() const {return pais_;}            //Devolver país
		string getApellidosyNombre();                     //Devolver formato "apellidos,nombre"
};

#endif
