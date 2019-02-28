/*!
	\file operadoresExternosMonomios.hpp
	\brief Ficheros con los prototipos de los operadores externos de la clase Monomio
*/

#ifndef _OperadoresExternosMonomios_HPP_
#define _OperadoresExternosMonomios_HPP_

// Facilita la entrada y salida
#include <iostream>

#include "Monomio.hpp"

// Para la sobrecarga de los operadores de flujo: << y >>
using std::istream;
using std::ostream;

// Espacio de nombre de la asigantura: ed
namespace ed
{
//////////////////////////////////////////////////////////////////////////////////////
	// Operadores externos que no pertenecen a la clase Monomio

	//! \name Operadores de igualdad

	// COMPLETAR LOS COMENTARIOS DE DOXYGEN
	bool operator==(ed::Monomio const & m1, ed::Monomio const & m2);
	/*
	\fn bool operator==(ed::Monomio const & m1, ed::Monomio const & m2)
	\brief comprueba si dos monomios son iguales
	\param	Dos bjetos de la clase Monomio
	\return	Dato de tipo booleano
	\author	Javier Ortiz Aragones
	\date	27/02/2019
	\post	Devuelve verdadero si los dos son iguales
	\post Devuelve falso si no lo son
	*/

	bool operator==(ed::Monomio const & m1, const double c);
	/*
	\fn bool operator==(ed::Monomio const & m1, const double c)
	\brief Comprueba si un monomio es igual a un numero real
	\param	Objeto de la clase Monomio y un numero real
	\return	Dato de tipo booleano
	\author	Javier Ortiz Aragones
	\date	27/02/2019
	\post	Devuelve verdadero si es monomio es de grado 0 y el coeficiente igual al numero real
	\post Devuelve falso si no se cumple lo anterior
	*/

	bool operator==(const double c, ed::Monomio const & m1);
	/*
	\fn bool operator==(const double c, ed::Monomio const & m1)
	\brief Comprueba si un numero real es igual a un monomio
	\param Un numero real y un objero de la clase Monomio
	\return	Dato de tipo booleano
	\author	Javier Ortiz Aragones
	\date	27/02/2019
	\post	Devuelve verdadero si es monomio es de grado 0 y el coeficiente igual al numero real
	\post Devuelve falso si no se cumple lo anterior
	*/

	//! \name Operadores de desigualdad

	// COMPLETAR LOS COMENTARIOS DE DOXYGEN
	bool operator!=(ed::Monomio const & m1, ed::Monomio const & m2);
	/*
	\fn bool operator!=(ed::Monomio const & m1, ed::Monomio const & m2)
	\brief Comprueba si dos monomios son distintos
	\param	Dos objetos de la clase Monomio
	\return Dato de tipo booleano
	\author	Javier Ortiz Aragones
	\date	27/02/2019
	\post	Devuelve verdadero si no tienen el mismo grado o no tienen el mismo coeficiente
	\post Devuelve falso si no se cumple lo anterior
	*/

	bool operator!=(const double c, ed::Monomio const & m1);
	/*
	\fn bool operator!=(const double c, ed::Monomio const & m1)
	\brief Comprueba si un monomio es distinto a un numero real
	\param	Un numero real y un objero de la clase Monomio
	\return	Dato de tipo booleano
	\author	Javier Ortiz Aragones
	\date	27/02/2019
	\post	Devuelve verdadero si el monomio no tiene grado 0 o si su coeficiente no es igual al numero real
	\post Devuelve falso si no se cumple lo anterior
	*/

	bool operator!=(ed::Monomio const & m1, const double c);
	/*
	\fn bool operator!=(ed::Monomio const & m1, const double c)
	\brief Comprueba si un monomio es distinto de un numero real
	\param	Objeto de la clase Monomio y un numero real
	\return	Objeto de la clase Monomio
	\author	Javier Ortiz Aragones
	\date	27/02/2019
	\post	Devuelve verdadero si el monomio no tiene grado 0 o si su coeficiente no es igual al numero real
	\post Devuelve falso si no se cumple lo anterio
	*/

	///////////////////////////////////////////////////

	//! \name Operadores unarios prefijos

	// COMPLETAR LOS COMENTARIOS DE DOXYGEN

	ed::Monomio & operator+(ed::Monomio const & m);
	/*
	\fn ed::Monomio & operator+(ed::Monomio const & m)
	\brief Devuelve una copia del monomio
	\param	Objeto de la clase Monomio
	\return	Objeto de la clase Monomio
	\author	Javier Ortiz Aragones
	\date	27/02/2019
	\post el monomio devuelto es igual al actual
	*/

	ed::Monomio & operator-(ed::Monomio const & m);
	/*
	\fn ed::Monomio & operator-(ed::Monomio const & m)
	\brief Devuelve el monomio opuesto
	\param	Objeto de la clase Monomio
	\return	Objeto de la clase Monomio
	\author	Javier Ortiz Aragones
	\date	27/02/2019
	\post El monomio devuelto tiene el mismo grado pero coeficiente opuesto
	*/


	//////////////////////////////////////////////////////////

	//! \name Operador binario de la suma

	// COMPLETAR LOS COMENTARIOS DE DOXYGEN
	 ed::Monomio & operator+ (ed::Monomio const &m1, ed::Monomio const &m2);
	 /*
	 \fn ed::Monomio & operator+ (ed::Monomio const &m1, ed::Monomio const &m2)
	 \brief Devuelve la suma de dos monomios
	 \param	2 objetos de la clase Monomio
	 \return	Objeto de la clase Monomio
	 \author	Javier Ortiz Aragones
	 \date	27/02/2019
	 \pre Los dos monomios tienen el mismo grado
	 \post El monomio devuelto tiene el mismo grado
	 \post El coeficiente es la suma de los dos
	 */


	//////////////////////////////////////////////////////////
	//! \name Operador binario de la resta

	ed::Monomio & operator-(ed::Monomio const &m1, ed::Monomio const &m2);
	/*
	\fn ed::Monomio & operator-(ed::Monomio const &m1, ed::Monomio const &m2
	\brief Devuelve la resta de dos monomios
	\param	2 objetos de la clase Monomio
	\return	Objeto de la clase Monomio
	\author	Javier Ortiz Aragones
	\date	27/02/2019
	\pre Los monomios tienen el mismo grado
	\post	El monomio devuelto tiene el mismo grado
 	\post El coeficiente es la resta de los dos
	*/


	///////////////////////////////////////////////////////////////////////////
	//! \name Operadores binarios de la multiplicación

	ed::Monomio &operator *(const ed::Monomio &m1, const ed::Monomio &m2);
	/*
	\fn ed::Monomio &operator *(const ed::Monomio &m1, const ed::Monomio &m2)
	\brief Multiplicación de dos monomios
	\param	2 objetos de la clase Monomio
	\return	Objeto de la clase Monomio
	\author	Javier Ortiz Aragones
	\date	27/02/2019
	\post	El monomio devuelto tiene ecomo grado la suma de los dos grados
	\post El coeficiente del monomio es el producto de los dos
	*/

	ed::Monomio &operator *(const ed::Monomio &m1, const double c);
	/*
	\fn ed::Monomio &operator *(const ed::Monomio &m1, const double c)
	\brief Multiplicación de un monomio y un real
	\param	Objeto de la clase Monomio y un numero real
	\return	Objeto de la clase Monomio
	\author	Javier Ortiz Aragones
	\date	27/02/2019
	\post	El monomio devuelto tiene el mismo grado
	\post El coeficiente del monomio es el producto del coeficiente del monomio y del numero real
	*/

	ed::Monomio &operator *(const double c, const ed::Monomio &m1);
	/*
	\fn ed::Monomio &operator *(const double c, const ed::Monomio &m1)
	\brief Multiplicación de un real y un monomio
	\param	Objeto de la clase Monomio y un numero real
	\return	Objeto de la clase Monomio
	\author	Javier Ortiz Aragones
	\date	27/02/2019
	\post	El monomio devuelto tiene el mismo grado
	\post El coeficiente del monomio es el producto del coeficiente del monomio y del numero real
	*/

	///////////////////////////////////////////////////////////////////////////

	//! \name Operadores binarios de la división

	ed::Monomio &operator /(const ed::Monomio &m1, const ed::Monomio &m2);
	/*
	\fn ed::Monomio &operator /(const ed::Monomio &m1, const ed::Monomio &m2)
	\brief División de dos monomios
	\param	2 objetos de la clase Monomio
	\return	Objeto de la clase Monomio
	\author	Javier Ortiz Aragones
	\date	27/02/2019
	\post	El monomio devuelto tiene como grado la resta de los dos grados
	\post El coeficiente del monomio es el cociente de los dos
	*/

	ed::Monomio &operator /(const ed::Monomio &m1, const double c);
	/*
	\fn ed::Monomio &operator /(const ed::Monomio &m1, const double c)
	\brief División de un monomio y un real
	\param	Objeto de la clase Monomio y un numero real
	\return	Objeto de la clase Monomio
	\author	Javier Ortiz Aragones
	\date	27/02/2019
	\post	El monomio devuelto tiene el mismo grado
	\post El coeficiente del monomio es el cociente del coeficiente del monomio y del numero real
	*/

	ed::Monomio &operator /(const double c, const ed::Monomio &m1);
	/*
	\fn ed::Monomio &operator /(const double c, const ed::Monomio &m1)
	\brief División de un real y un monomio
	\param	Objeto de la clase Monomio y un numero real
	\return	Objeto de la clase Monomio
	\author	Javier Ortiz Aragones
	\date	27/02/2019
	\post	El monomio devuelto tiene el mismo grado
	\post El coeficiente del monomio es el cociente del coeficiente del monomio y del numero real
	*/

	/////////////////////////////////////////////////////////////////////////////

	//! \name Sobrecarga de los operadores de entrada y salida

	// COMPLETAR LOS COMENTARIOS DE DOXYGEN
	 istream &operator>>(istream &stream, ed::Monomio &m);
	 /*
	 \fn istream &operator>>(istream &stream, ed::Monomio &m)
	 \brief Lee desde el flujo de entrada los atributos de un monomio separados por un espacio
	 \param	Flujo de entrada y un objeto de la clase Monomio
	 \return	Flujo de entrada
	 \author	Javier Ortiz Aragones
	 \date	27/02/2019
	 */

	// COMPLETAR LOS COMENTARIOS DE DOXYGEN
	 ostream &operator<<(ostream &stream, ed::Monomio const &m);
	 /*
	 \fn ostream &operator<<(ostream &stream, ed::Monomio &m)
	 \brief Escribe en el flujo de salida los atributos de un monomio separados por un espacio
	 \param	Flujo de entrada y un objeto de la clase Monomio
	 \return	Flujo de salida
	 \author	Javier Ortiz Aragones
	 \date	27/02/2019
	 */

}  // Fin de namespace ed.

#endif // _OperadoresExternosMonomios_HPP_
