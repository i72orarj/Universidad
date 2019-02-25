/*!
   \file  operadoresExternosMonomios.cpp
	\brief Ficheros con el código de los operadores externos de la clase Monomio
*/


//  Ficheros de cabecera
#include <iostream>

#include "operadoresExternosMonomios.hpp"


//  Se incluyen los operadores sobrecargados dentro del espacio de nombres ed
namespace ed
{
	// Operadores de igualdad

	// COMPLETAR

	bool operator==(ed::Monomio const & m1, ed::Monomio const & m2)
	{
		if(m1.getGrado()==m2.getGrado()){
			if(std::abs(m1.getCoeficiente()-m2.getCoeficiente())<COTA_ERROR){
				return true;
			}
		}
		return false;
	}

	// COMPLETAR LOS OTROS OPERADORES DE IGUALDAD
	bool operator==(ed::Monomio const & m1, const double c){
		if(m1.getGrado()==0){
			if(std::abs(m1.getCoeficiente()-c)<COTA_ERROR){
				return true;
			}
		}
		return false;
	}
	bool operator==(const double c, ed::Monomio const & m1){
		if(m1.getGrado()==0){
			if(std::abs(m1.getCoeficiente()-c)<COTA_ERROR){
				return true;
			}
		}
		return false;
	}

	// Operadores de desigualdad

	// COMPLETAR
	bool operator!=(ed::Monomio const & m1, ed::Monomio const & m2)
	{
		if(m1.getGrado()!=m2.getGrado()||m1.getCoeficiente()!=m2.getCoeficiente()){
			return true;
		}
		return false;
	}
	bool operator!=(const double c, ed::Monomio const & m1){
		if(m1.getGrado()!=0||m1.getCoeficiente()!=c){
			return true;
		}
		return false;
	}
	bool operator!=(ed::Monomio const & m1, const double c){
		if(m1.getGrado()!=0||m1.getCoeficiente()!=c){
			return true;
		}
		return false;
	}

	////////////////////////////////////////////////////////////

	// Operadores unarios prefijos

	// COMPLETAR
	ed::Monomio & operator+(ed::Monomio const & m)
	{
		// Se crea un nuevo objeto
		ed::Monomio *nuevo = new ed::Monomio();
		nuevo->setGrado(m.getGrado());
		nuevo->setCoeficiente(m.getCoeficiente());
		// Se devuelve el resultado
		return *nuevo;
	}
	ed::Monomio & operator-(ed::Monomio const & m)
	{
		// Se crea un nuevo objeto
		ed::Monomio *nuevo = new ed::Monomio();
		/*#ifndef NDEBUG
		assert(this->getGrado()==m.getGrado());
		#endif*/
		nuevo->setGrado(m.getGrado());
		nuevo->setCoeficiente(-m.getCoeficiente());
		// Se devuelve el resultado
		return *nuevo;
	}



	////////////////////////////////////////////////////////////
	// Operadores aritméticos binarios

	// Suma
	ed::Monomio & operator+ (ed::Monomio const &m1, ed::Monomio const &m2)
	{
		// Se crea un nuevo objeto
		ed::Monomio *nuevo = new ed::Monomio();
		#ifndef NDEBUG
		assert(m1.getGrado()==m2.getGrado());
		#endif
		nuevo->setGrado(m1.getGrado());
		nuevo->setCoeficiente(m1.getCoeficiente()+m2.getCoeficiente());
		// Se devuelve el resultado
		return *nuevo;
	}
	////////////
	// Resta
	ed::Monomio & operator-(ed::Monomio const &m1, ed::Monomio const &m2){
		// Se crea un nuevo objeto
		ed::Monomio *nuevo = new ed::Monomio();
		#ifndef NDEBUG
		assert(m1.getGrado()==m2.getGrado());
		#endif
		nuevo->setGrado(m1.getGrado());
		nuevo->setCoeficiente(m1.getCoeficiente()-m2.getCoeficiente());
		// Se devuelve el resultado
		return *nuevo;
	}
	//////////////////
	// Multiplicación
	ed::Monomio &operator *(const ed::Monomio &m1, const ed::Monomio &m2){
		ed::Monomio* nuevo=new ed::Monomio();
		nuevo->setGrado(m1.getGrado()+m2.getGrado());
		nuevo->setCoeficiente(m1.getCoeficiente()*m2.getCoeficiente());
		return *nuevo;
	}

	ed::Monomio &operator *(const ed::Monomio &m1, const double c){
		ed::Monomio* nuevo=new ed::Monomio();
		nuevo->setGrado(m1.getGrado());
		nuevo->setCoeficiente(m1.getCoeficiente()*c);
		return *nuevo;
	}

	ed::Monomio &operator *(const double c, const ed::Monomio &m1){
		ed::Monomio* nuevo=new ed::Monomio();
		nuevo->setGrado(m1.getGrado());
		nuevo->setCoeficiente(m1.getCoeficiente()*c);
		return *nuevo;
	}

	////////////
	// División
	ed::Monomio &operator /(const ed::Monomio &m1, const ed::Monomio &m2){
		#ifndef NDEBUG
		assert(m2.getGrado()<=m1.getGrado());
		assert(m2.getCoeficiente()!=0.0);
		#endif
		ed::Monomio* nuevo=new ed::Monomio();
		nuevo->setGrado(m1.getGrado()-m2.getGrado());
		nuevo->setCoeficiente(m1.getCoeficiente()/m2.getCoeficiente());
		return *nuevo;
	}

	ed::Monomio &operator /(const ed::Monomio &m1, const double c){
		#ifndef NDEBUG
		assert(m1.getCoeficiente()!=0.0);
		#endif
		ed::Monomio* nuevo=new ed::Monomio();
		nuevo->setGrado(m1.getGrado());
		nuevo->setCoeficiente(m1.getCoeficiente()/c);
		return *nuevo;
	}

	ed::Monomio &operator /(const double c, const ed::Monomio &m1){
		#ifndef NDEBUG
		assert(m1.getGrado()==0);
		assert(m1.getCoeficiente()!=0.0);
		#endif
		ed::Monomio* nuevo=new ed::Monomio();
		nuevo->setGrado(0);
		nuevo->setCoeficiente(c/m1.getCoeficiente());
		return *nuevo;
	}

	/////////////////////////////////////////////////////////////////////////////

	//  Sobrecarga del operador de entrada
	istream &operator>>(istream &stream, ed::Monomio &m)
	{
		double c;
		int g;
		//stream>>m.leerMonomio();
		stream>>c;
		//stream>>" ";
		stream>>g;
		//stream>>g;
		m.setCoeficiente(c);
		m.setGrado(g);
		// Se devuelve el flujo de entrada
		return stream;
	}


	//  Sobrecarga del operador de salida
	ostream &operator<<(ostream &stream, ed::Monomio const &m)
	{
		//double c;
		//int g;
		//stream<<m.escribirMonomio();
		stream<<m.getCoeficiente();
		stream<<" ";
		stream<<m.getGrado();
		// Se devuelve el flujo de salida
		return stream;
	}


}  // namespace ed
