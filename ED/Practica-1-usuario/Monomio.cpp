/*!
   \file  Monomio.cpp
   \brief Fichero que contiene el código de las funciones de la clase Monomio
*/


//  Ficheros de cabecera
#include <iostream>

#include "Monomio.hpp"

// Operadores de asignación

// COMPLETAR

ed::Monomio & ed::Monomio::operator=(ed::Monomio const &m)
{
	setCoeficiente(m.getCoeficiente());
	setGrado(m.getGrado());
	// Se devuelve el objeto actual
	return *this;
}


ed::Monomio & ed::Monomio::operator=(double const &x)
{
	setCoeficiente(x);
	setGrado(0);
	// Se devuelve el objeto actual
	return *this;
}



//////////////////////////////////////////////////////////////

// Operadores aritméticos y asignación

// COMPLETAR

ed::Monomio & ed::Monomio::operator+=(ed::Monomio const &m)
{
	#ifndef NDEBUG
	assert(getGrado()==m.getGrado());
	#endif
	setCoeficiente(getCoeficiente()+m.getCoeficiente());
	//setGrado(getGrado()+m.getGrado());
	#ifndef NDEBUG
	#endif
	// Se devuelve el objeto actual
	return *this;
}
ed::Monomio & ed::Monomio::operator-=(ed::Monomio const &m){
	#ifndef NDEBUG
	assert(getGrado()==m.getGrado());
	#endif
	setCoeficiente(getCoeficiente()-m.getCoeficiente());
	//setGrado(getGrado()+m.getGrado());
	#ifndef NDEBUG
	#endif
	// Se devuelve el objeto actual
	return *this;
}
ed::Monomio & ed::Monomio::operator*=(ed::Monomio const &m){
	setCoeficiente(getCoeficiente()*m.getCoeficiente());
	setGrado(getGrado()+m.getGrado());
	#ifndef NDEBUG
	#endif
	// Se devuelve el objeto actual
	return *this;
}
ed::Monomio & ed::Monomio::operator/=(ed::Monomio const &m){
	assert(m.getGrado()<=getGrado());
	assert(m.getCoeficiente()!=0.0);
	setCoeficiente(getCoeficiente()/m.getCoeficiente());
	setGrado(getGrado()-m.getGrado());
	return *this;

}


// COMPLETAR EL RESTO DE OPERADORES



///////////////////////////////////////////////////////////////////////

// Funciones lectura y escritura de la clase Monomio

ed::Monomio ed::Monomio::leerMonomio(){
	double c;
	int g;
	std::cout << "Introduzca el coeficiente: " ;
	std::cin >> c;
	//m.setCoeficiente(c);
	std::cout << "Introduzca el grado: " ;
	std::cin >> g;
	//m.setGrado(g);
	ed::Monomio m(c,g);
	assert(m.getGrado()>=0);
	return m;
}
void ed::Monomio::escribirMonomio(const ed::Monomio &m){
	if(m.getCoeficiente()==1){
		std::cout << "X" <<getGrado()<< '\n';
	}
	else if(m.getCoeficiente()==-1){
		std::cout << "-X"<<getGrado()<<'\n' ;
	}
	else{
		if(m.getGrado()==0){
			std::cout << getCoeficiente() << '\n';
		}
		else if(m.getGrado()==1){
			std::cout << getCoeficiente()<<"X" << '\n';
		}
		else{
			std::cout << getCoeficiente()<<"X"<<getGrado() << '\n';
		}

	}
}



///////////////////////////////////////////////////////////////////////

// Funciones auxiliares de la clase Monomio

double ed::Monomio::calcularValor(const double &x){
	return getCoeficiente()*pow(x,getGrado());
}
