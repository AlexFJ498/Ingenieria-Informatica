/*!
  \file   funcionesAuxiliares.hpp
  \brief  Funciones auxiliares para el programa principal de la práctica 3
  \author Alejandro Fuerte Jurado
  \date  
*/

#ifndef _FuncionesAuxiliares_HPP_
#define _FuncionesAuxiliares_HPP_

#include "MonticuloMediciones.hpp"

// SE DEBEN INCLUIR LOS COMENTARIOS DE DOXYGEN

namespace ed{
	int menu();

	void cargarMonticuloDeFichero(std::string const & nombreFichero, ed::MonticuloMediciones & monticulo); 

	void grabarMonticuloEnFichero (std::string const & nombreFichero, ed::MonticuloMediciones const & monticulo); 

	void comprobarMonticuloVacio(ed::MonticuloMediciones &monticulo);

	void mostrarMedicionesDeMonticulo(ed::MonticuloMediciones &monticulo);

	void calcularTamano(ed::MonticuloMediciones &monticulo);

	void borrarTodasLasMedicionesDeMonticulo(ed::MonticuloMediciones &monticulo);

	void modificarMedicionDeMonticulo(ed::MonticuloMediciones &monticulo);

	void insertarMedicionDeMonticulo(ed::MonticuloMediciones &monticulo);

	void borrarMunicipioDeMonticulo(ed::MonticuloMediciones &monticulo);


} // Fin del espacio de nombre de la asignatura: ed

// Fin de _FuncionesAuxiliares_HPP_
#endif

