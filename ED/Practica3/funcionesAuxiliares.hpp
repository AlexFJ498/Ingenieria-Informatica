/*!
  \file   funcionesAuxiliares.hpp
  \brief  Funciones auxiliares para el programa principal de la práctica 3
  \author Alejandro Fuerte Jurado
  \date  07-05-2018
*/

#ifndef _FuncionesAuxiliares_HPP_
#define _FuncionesAuxiliares_HPP_

#include "MonticuloMediciones.hpp"

namespace ed{
	/*
	\brief Función para el funcionamiento del menú
	\pre Ninguna
	\post Ninguna
	*/
	int menu();

	/*
	\brief Cargar un montículo en un fichero
	\param nombreFichero: nombre del fichero (tipo string)
	\param monticulo: montículo (tipo MonticuloMediciones)
	\pre Ninguna
	\post Ninguna
	*/
	void cargarMonticuloDeFichero(std::string const & nombreFichero,ed::MonticuloMediciones & monticulo); 

	/*
	\brief grabar un montículo en un fichero
	\param nombreFichero: nombre del fichero (tipo string)
	\param monticulo: montículo (tipo MonticuloMediciones)
	\pre Ninguna
	\post Ninguna
	*/
	void grabarMonticuloEnFichero (std::string const & nombreFichero,ed::MonticuloMediciones const & monticulo); 

	/*
	\brief Comprobar si un montículo está vacío
	\param monticulo: montículo (tipo MonticuloMediciones)
	\pre Ninguna
	\post Ninguna
	*/
	void comprobarMonticuloVacio(ed::MonticuloMediciones &monticulo);

	/*
	\brief Mostrar por pantalla las mediciones de un montículo
	\param monticulo: montículo (tipo MonticuloMediciones)
	\pre Ninguna
	\post Ninguna
	*/
	void mostrarMedicionesDeMonticulo(ed::MonticuloMediciones &monticulo);

	/*
	\brief Calcular el tamaño de un montículo
	\param monticulo: montículo (tipo MonticuloMediciones)
	\pre Ninguna
	\post Ninguna
	*/
	void calcularTamano(ed::MonticuloMediciones &monticulo);

	/*
	\brief Borrar las mediciones de un montículo
	\param monticulo: montículo (tipo MonticuloMediciones)
	\pre Ninguna
	\post Ninguna
	*/
	void borrarTodasLasMedicionesDeMonticulo(ed::MonticuloMediciones &monticulo);

	/*
	\brief Modificar el top de un montículo
	\param monticulo: montículo (tipo MonticuloMediciones)
	\pre Ninguna
	\post Ninguna
	*/
	void modificarMedicionDeMonticulo(ed::MonticuloMediciones &monticulo);

	/*
	\brief Insertar medición en un montículo
	\param monticulo: montículo (tipo MonticuloMediciones)
	\pre Ninguna
	\post Ninguna
	*/
	void insertarMedicionDeMonticulo(ed::MonticuloMediciones &monticulo);

	/*
	\brief Borrar medición
	\param monticulo: montículo (tipo MonticuloMediciones)
	\pre Ninguna
	\post Ninguna
	*/
	void borrarMedicionDeMonticulo(ed::MonticuloMediciones &monticulo);


} // Fin del espacio de nombre de la asignatura: ed

// Fin de _FuncionesAuxiliares_HPP_
#endif

