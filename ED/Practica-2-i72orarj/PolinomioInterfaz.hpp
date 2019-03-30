/*!
   \file PolinomioInterfaz.hpp
   \brief Definición de la interfaz de la clase Polinomio
*/

#ifndef _POLINOMIOINTERFAZ_HPP_
#define _POLINOMIOINTERFAZ_HPP_

#include "../Practica-1-i72orarj/Monomio.hpp"

// Se incluye la clase PolinomioInterfaz dentro del espacio de nombre de la asigantura: ed
namespace ed {

//!  Definición de la clase PolinomioInterfaz
class PolinomioInterfaz
{

   //! \name Funciones o métodos públicos de la clase
   public:

	//! \name Observadores: funciones de consulta

	// COMPLETAR LOS COMENTARIOS DE DOXYGEN
	virtual bool esNulo() const = 0;

  // COMPLETAR LOS COMENTARIOS DE DOXYGEN
  virtual int getGrado()const = 0;

  // COMPLETAR LOS COMENTARIOS DE DOXYGEN
  virtual int getNumeroMonomios()const = 0;


  // COMPLETAR LOS COMENTARIOS DE DOXYGEN
  virtual bool existeMonomio(int g) = 0;


  // COMPLETAR LOS COMENTARIOS DE DOXYGEN
  virtual Monomio & getMonomio(int g) = 0;



}; // Fin de la definición de la clase PolinomioInterfaz


} // \brief Fin de namespace ed.

//  _POLINOMIOINTERFAZ_HPP_
#endif
