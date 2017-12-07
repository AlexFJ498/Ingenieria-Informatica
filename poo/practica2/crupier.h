#ifndef CRUPIER_H
#define CRUPIER_H

#include "persona.h"

/*La clase Crupier hereda de la clase Persona y le añade un código alfanumérico de empleado del casino*/

class Crupier:public Persona{

	private:
		string codigo_;

	public:
		Crupier(string dni,string c,string n="",string a="",string d="",string l="",string p="",string pa=""):Persona(dni,n,a,d,l,p,pa),codigo_(c){} //Constructor, parámetros obligatorios: DNI y código de empleado

		inline string getCodigo() const {return codigo_;}   //Devolver código de empleado
		void setCodigo(string c);                           //Modificar código de empleado

};

#endif
