#ifndef _MATERIAL_
#define _MATERIAL_

class Material{
	private:
		int _etiqueta;
		float _volumen;
		float _precio;
		std::string _usado;

	public:
		/*Constructor*/
		Material(){
			_etiqueta=-1;
			_volumen=0;
			_precio=0;
		}

		/*Observadores*/
		inline int getEtiqueta(){return _etiqueta;}
		inline float getVolumen(){return _volumen;}
		inline float getPrecio(){return _precio;}
		inline std::string getUsado(){return _usado;}

		/*Modificadores*/
		void setEtiqueta(int etiqueta){_etiqueta=etiqueta;}
		void setVolumen(float volumen){_volumen=volumen;}
		void setPrecio(float precio){_precio=precio;}
		void setUsado(std::string usado){_usado=usado;}
};

#endif
