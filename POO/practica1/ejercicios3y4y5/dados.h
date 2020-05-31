#ifndef DADOS_H
#define DADOS_H

class Dados{
	private:
		float d1_;
		float d2_;
		float nlanzamientos1_;
		float nlanzamientos2_;
		float media1_;
		float media2_;
		float v1_[5];
		float v2_[5];
	public:
		Dados();		                //el constructor no devuelve nada
		float getDado1();		        //devuelve el valor del primer dado
		float getDado2();	  	        //devuelve el valor del segundo dado
		void lanzamiento();	            //obtiene un nuevo valor aleatorio para los 2 dados
		bool setDado1(float r1)         //asigna un valor al primer dado entre 1 y 6
		bool setDado2(float r2);        //asigna un valor al segundo dado entre 1 y 6
		int getSuma();		            //devuelve el valor de la suma de los dos dados
		int getDiferencia();            //devuelve el valor de la resta de los dos dados
		int getLanzamiento1();          //devuelve el número de lanzamientos del dado 1
		int getLanzamiento2();          //devuelve el número de lanzamientos del dado 2
		float getMedia1();	            //devuelve la media de los valores del dado 1
		float getMedia2();	            //devuelve la media de los valores del dado 2
		void getUltimos1(float v1[5]);  //5 últimos valores del primer dado
		void getUltimos2(float v2[5]);  //5 últimos valores del segundo dado	
		void operacionesUltimos1();
		void operacionesUltimos2();
};

#endif
