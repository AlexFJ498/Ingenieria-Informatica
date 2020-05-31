/*!
	\file  Point2D.hpp
	\brief Clase para un punto con coordenadas x e y
*/

#ifndef _POINT2D_HPP_
#define _POINT2D_HPP_

namespace ed{

//! Definición de la clase Point2D
class Point2D{
	private:
		double x_; //!< Coordenada x
		double y_; //!< Coordenada y

	public:
		/*!
			\brief    Constructor de la clase Point2D
			\param x: Coordenada x (tipo int)
			\param y: Coordenada y (tipo int)
			\note     Parámetros con valores predeterminados de 0
		*/
		Point2D(double x=0,double y=0){
			x_=x;
			y_=y;
		}

		/*!
			\brief  Observador de la coordenada x
			\note   Función inline
			\note   Función constante
			\return Coordenada x (tipo int)
		*/
		inline double getX()const{return x_;}

		/*!
			\brief  Observador de la coordenada y
			\note   Función inline
			\note   Función constante
			\return Coordenada y (tipo int)
		*/
		inline double getY()const{return y_;}

		/*!
			\brief    Modificador de la coordenada x
			\note     Función inline
			\param x: Coordenada x (tipo int)
		*/
		inline void setX(double x){x_=x;}

		/*!
			\brief    Modificador de la coordenada x
			\note     Función inline
			\param y: Coordenada y (tipo int)
		*/
		inline void setY(double y){y_=y;}

		/*!
			\brief    Operador de igualdad
			\note     Función inline
			\param p: Punto a comparar
			\return   true si son iguales, false si no
		*/
		inline bool operator==(Point2D const &p){
			if(this->getX()==p.getX() && this->getY()==p.getY()){
				return true;
			}
			return false;
		}

};
} // \brief Fin de namespace ed.

#endif
