/*!
	\file Monomio.hpp
	\brief Definición de la clase Monomio
*/

#ifndef _MONOMIO_HPP_
#define _MONOMIO_HPP_

// Para usar la funciones pow y std::abs
#include <cmath>

// Para controlar las pre y post condiciones mediante asertos
#include <cassert>

#define COTA_ERROR 1.0e-6  //!< Cota de error para la comparación números reales

// Se incluye la clase Monomio dentro del espacio de nombre de la asigantura: ed
namespace ed
{
//!  Definición de la clase Monomio:  \f$ coeficiente \hspace{1ex} X^{grado} \f$
class Monomio
{
	//! \name Atributos privados de la clase Monomio
	private:

		// COMPLETAR
		double coeficiente_;
		int grado_;

	//! \name Funciones o métodos públicos de la clase Monomio
	public:

	//! \name Constructores de la clase Monomio

	// COMPLETAR
		/*Monomio(double coeficiente=0.0,int grado=0){
			if(grado>=0){
				setGrado(grado);
				setCoeficiente(coeficiente);
			}
		}*/
		Monomio(double coeficiente=0.0,int grado=0){
			#ifndef NDEBUG
			assert(grado>=0);
			#endif
			setCoeficiente(coeficiente);
			setGrado(grado);
			#ifndef NDEBUG
			assert(std::abs(getCoeficiente()-coeficiente)<COTA_ERROR);
			assert(getGrado()==grado);
			#endif
		}


		Monomio(const Monomio &m){
			setCoeficiente(m.getCoeficiente());
			setGrado(m.getGrado());
		}



	//! \name Observadores: funciones de consulta de la clase Monomio

	// COMPLETAR
		inline double getCoeficiente()const{return coeficiente_;};
		inline int getGrado()const{return grado_;};

	//! \name Funciones de modificación de la clase Monomio

	// COMPLETAR
		inline void setCoeficiente(const double c){coeficiente_=c;};
		inline void setGrado(const int g){
			#ifndef NDEBUG
			assert(g>=0);
			#endif
			grado_=g;
		};

	/////////////////////////////////////////////////

	//! \name Operadores de la clase Monomio

	// Operadores de asignación

		// COMPLETAR LOS COMENTARIOS DE DOXYGEN
		Monomio & operator=(Monomio const &m);
		/*
		\fu Monomio & operator=(Monomio const &m)
		\brief Iguala un monomio a otro monomio
		\param	Objeto de la clase Monomio
		\return	Objeto de la clase Monomio
		\author	Javier Ortiz Aragones
		\date	27/02/2019
		\post	El coeficiente del monomio es igual al coeficiente del monomio pasado como parametro
		\post El grado del monomio es igual al grado del monomio pasado como parametro
		*/

		// COMPLETAR LOS COMENTARIOS DE DOXYGEN
		Monomio & operator=(double const &x);
		/*
		\fn Monomio & operator=(double const &x)
		\brief Iguala un monomio a un numero real
		\param Numero real
		\return	Objeto de la clase Monomio
		\author Javier Ortiz Aragones
		\date 27/02/2019
		\post	El grado del monomio es 0
		\post El coeficiente del monomio es igual al numero real pasado como parametro

		*/

	// Operadores aritméticos y asignación

		// COMPLETAR LOS COMENTARIOS DE DOXYGEN
		Monomio & operator+=(Monomio const &m);
		/*
		\fn Monomio & operator+=(Monomio const &m)
		\brief Suma a un monomio a otro monomio del mismo grado
		\param	Objeto de la clase Monomio
		\return	Objeto de la clase Monomio
		\author	Javier Ortiz Aragones
		\date	27/02/2019
		\pre Los dos monomios deben tener el mismo grado
		\post	El coeficiente se ha incrementado con el valor del coeficiente del monomio pasado como parametro
		\post El grado del monomio no se modifica
		*/
		Monomio & operator-=(Monomio const &m);
		/*
		\fn Monomio & operator-=(Monomio const &m)
		\brief Resta a un monomio a otro monomio del mismo grado
		\param	Objeto de la clase Monomio
		\return	Objeto de la clase Monomio
		\author	Javier Ortiz Aragones
		\date	27/02/2019
		\pre Los dos monomios deben tener el mismo grado
		\post	El coeficiente se ha decrementado con el valor del coeficiente del monomio pasado como parametro
		\post El grado del monomio no se modifica
		*/
		Monomio & operator*=(Monomio const &m);
		/*
		\fn Monomio & operator*=(Monomio const &m)
		\brief Multiplica un monomio con otro monomio
		\param	Objeto de la clase Monomio
		\return	Objeto de la clase Monomio
		\author	Javier Ortiz Aragones
		\date	27/02/2019
		\post	El coeficiente se ha multiplicado con el valor del coeficiente del monomio pasado como parametro
		\post El grado del monomio se ha incrementado con el valor del grado del monomio pasado como parametro
		*/
		Monomio & operator/=(Monomio const &m);
		/*
		\fn Monomio & operator/=(Monomio const &m)
		\brief Divide un monomio con otro monomio del mismo grado
		\param	Objeto de la clase Monomio
		\return	Objeto de la clase Monomio
		\author	Javier Ortiz Aragones
		\date	27/02/2019
		\pre El coeficiente del monomio parametro no puede ser 0.0
		\pre El grado del monomio parametro es igual o inferior al monomio actual
		\post	El coeficiente se ha dividido con el valor del coeficiente del monomio pasado como parametro
		\post El grado del monomio se ha decrementado con el valor del grado del  monomio pasado como parametro
		*/
		Monomio & operator*=(const double x);
		/*
		\fn Monomio & operator*=(const double x)
		\brief Multiplica un monomio con un numero real
		\param	Numero real
		\return	Objeto de la clase Monomio
		\author	Javier Ortiz Aragones
		\date	27/02/2019
		\post	El coeficiente se ha multiplicado con el valor del coeficiente del monomio pasado como parametro
		\post El grado del monomio no se ha modificado
		*/

		Monomio & operator/=(const double x);
			/*
			\fn Monomio & operator/=(const double x)
			\brief Divide un monomio con un nhmero real
			\param	Numero real
			\return	Objeto de la clase Monomio
			\author	Javier Ortiz Aragones
			\date	27/02/2019
			\pre El coeficiente del monomio parametro no puede ser 0.0
			\post	El coeficiente se ha dividido con el valor del coeficiente del monomio pasado como parametro
			\post El grado del monomio no se ha modificado
			*/
		// COMPLETAR EL RESTO DE OPERADORES


	/////////////////////////////////////////////////////////////////////////////////////

	//! \name Funciones lectura y escritura de la clase Monomio

	Monomio leerMonomio();
	/*
	\fn Monomio leerMonomio()
	\brief Lee un monomio desde teclado
	\return	Objeto de la clase Monomio
	\author	Javier Ortiz Aragones
	\date	27/02/2019
	\post El grado del monomio es mayor o igual a 0
	*/
	void escribirMonomio()const;
	/*
	\fn void escribirMonomio()
	\brief Muestra un monomio por pantalla
	\param	Objeto de la clase Monomio
	\return	Objeto de la clase Monomio
	\author	Javier Ortiz Aragones
	\date	27/02/2019
	*/


	///////////////////////////////////////////////////////////////////////

	//! \name Funciones auxiliares de la clase Monomio

	double calcularValor(const double &x);
	/*
	\fn double calcularValor(const double &x)
	\brief Calcula el valor del monomio para un numero real
	\param	Numero real
	\return	Numero real
	\author	Javier Ortiz Aragones
	\date	27/02/2019
	*/
	// COMPLETAR



};  // Fin de la definición de la clase Monomio

}  //  Fin de namespace ed.

// _MONOMIO_HPP_
#endif
