/*!
   \file operadoresExternosPolinomios.cpp
   \brief Fichero que contiene el código de las funciones de la clase Polinomio
*/


// Ficheros de cabecera
#include <iostream>

#include "operadoresExternosPolinomios.hpp"

#include "../Practica-1-i72orarj/operadoresExternosMonomios.hpp"

// Se incluyen los operadores sobrecargados dentro del espacio de nombres de ed

namespace ed
{

bool operator==(ed::Polinomio const & p1, ed::Polinomio const & p2)
{
		if(p1.getNumeroMonomios()!=p2.getNumeroMonomios()){
			return false;
		}
		if(p1.getGrado()!=p2.getGrado()){
			return false;
		}
		std::list<Monomio>::iterator it1;
		std::list<Monomio>::iterator it2;
		it2=p2.getList().begin();
		for(it1=p1.getList().begin();it1!=p1.getList().end();it1++){
			if((*it1)!=(*it2)){
				return false;
			}
			it2++;
		}

		return true;
}


bool operator==(ed::Polinomio const & p, ed::Monomio const & m){
	if(p.getNumeroMonomios()!=1){
		return false;
	}
	else if(p.getList().front()==m){
			return true;
	}
	else{
		return false;
	}
}
bool operator==(ed::Monomio const & m, ed::Polinomio const & p){
	if(p.getNumeroMonomios()!=1){
		return false;
	}
	else if(p.getList().front()==m){
			return true;
	}
	else{
		return false;
	}
}
bool operator==(ed::Polinomio const & p, double const & x){
	if(p.getNumeroMonomios()!=1){
		return false;
	}
	else if(p.getList().front()==x){
			return true;
	}
	else{
		return false;
	}
}
bool operator==(double const & x, ed::Polinomio const & p){
	if(p.getNumeroMonomios()!=1){
		return false;
	}
	else if(p.getList().back()==x){
			return true;
	}
	else{
		return false;
	}
}


////////////////////////////////////////////////////////////////////////////////////
// Operadores de desigualdad
bool operator!=(ed::Polinomio const & p1, ed::Polinomio const & p2)
{
	if(p1.getNumeroMonomios()!=p2.getNumeroMonomios()){
		return true;
	}
	if(p1.getGrado()!=p2.getGrado()){
		return true;
	}
	std::list<Monomio>::iterator it1;
	std::list<Monomio>::iterator it2;
	it2=p2.getList().begin();
	for(it1=p1.getList().begin();it1!=p1.getList().end();it1++){
		if((*it1)!=(*it2)){
			return true;
		}
		it2++;
	}

	return false;
}
bool operator!=(ed::Polinomio const & p, ed::Monomio const & m){
	if(p.getNumeroMonomios()!=1){
		return true;
	}
	else if(*(p.getList().end())==m){
			return false;
	}
	else{
		return true;
	}
}
bool operator!=(ed::Monomio const & m, ed::Polinomio const & p){
	if(p.getNumeroMonomios()!=1){
		return true;
	}
	else if(*(p.getList().end())==m){
			return false;
	}
	else{
		return true;
	}
}
bool operator!=(ed::Polinomio const & p, double const & x){
	if(p.getNumeroMonomios()!=1){
		return true;
	}
	else if(p.getList().front()==x){
			return false;
	}
	else{
		return true;
	}
}
bool operator!=(double const & x, ed::Polinomio const & p){
	if(p.getNumeroMonomios()!=1){
		return true;
	}
	else if(p.getList().front()==x){
			return false;
	}
	else{
		return true;
	}
}

//////////////////////////////////////////////////////////////////////////////////////

// Operadores unarios

// COMPLETAR
ed::Polinomio & operator+(ed::Polinomio const & p)
{
	// Se crea un nuevo objeto
	ed::Polinomio *nuevo = new ed::Polinomio(p);
	#ifndef NDEBUG
	assert(p==(*nuevo));
	#endif
	// Se devuelve el resultado
	return *nuevo;
}
ed::Polinomio & operator-(ed::Polinomio const & p)
{
	// Se crea un nuevo objeto
	ed::Polinomio *nuevo = new ed::Polinomio();
	std::list<Monomio>::iterator it;
	std::list<Monomio> auxlist;
	for(it=p.getList().begin();it!=p.getList().end();it++){
		//nuevo->list_.push_back(-(*it));
		auxlist.push_back(-(*it));
	}
	nuevo->setList(auxlist);
	// Se devuelve el resultado
	return *nuevo;
}

//////////////////////////////////////////////////////////////////////////////////////

// Operadores binarios de la suma
ed::Polinomio & operator+(ed::Polinomio const &p1,  ed::Polinomio const &p2)
{
	// COMPLETAR Y MODIFICAR
	// Se crea un nuevo objeto
	ed::Polinomio *nuevo = new ed::Polinomio;
	std::list<Monomio>::iterator it;
	std::list<Monomio> auxlist;
	//std::list<Monomio>::iterator it2;
	for(it=p1.getList().begin();it!=p1.getList().end();it++){
		// nuevo->list_.push_back((*it));
		auxlist.push_back((*it));
	}
	for(it=p2.getList().begin();it!=p2.getList().end();it++){
		// nuevo->list_.push_back((*it));
		auxlist.push_back((*it));
	}
	nuevo->setList(auxlist);
	nuevo->sumarRepetidos();
	nuevo->sort();
	// Se devuelve el resultado
	return *nuevo;
}

ed::Polinomio & operator+(ed::Polinomio const &p,  ed::Monomio const &m)
{
	// COMPLETAR Y MODIFICAR
	// Se crea un nuevo objeto
	ed::Polinomio *nuevo = new ed::Polinomio;
	std::list<Monomio>::iterator it;
	std::list<Monomio> auxlist;
	for(it=p.getList().begin();it!=p.getList().end();it++){
		// nuevo->list_.push_back((*it));
		auxlist.push_back((*it));
	}
	// nuevo->list_.push_back(m);
	auxlist.push_back(m);
	nuevo->setList(auxlist);
	nuevo->sumarRepetidos();
	nuevo->sort();
	// Se devuelve el resultado
	return *nuevo;
}
ed::Polinomio & operator+(ed::Monomio const &m,  ed::Polinomio const &p)
{
	// COMPLETAR Y MODIFICAR
	// Se crea un nuevo objeto
	ed::Polinomio *nuevo = new ed::Polinomio;
	std::list<Monomio>::iterator it;
	std::list<Monomio> auxlist;
	for(it=p.getList().begin();it!=p.getList().end();it++){
		// nuevo->list_.push_back((*it));
		auxlist.push_back((*it));
	}
	// nuevo->list_.push_back(m);
	auxlist.push_back((*it));
	nuevo->setList(auxlist);
	nuevo->sumarRepetidos();
	nuevo->sort();
	// Se devuelve el resultado
	return *nuevo;
}
ed::Polinomio & operator+(ed::Polinomio const &p,  double const &x)
{
	// COMPLETAR Y MODIFICAR
	// Se crea un nuevo objeto
	ed::Polinomio *nuevo = new ed::Polinomio;
	std::list<Monomio>::iterator it;
	std::list<Monomio> auxlist;
	for(it=p.getList().begin();it!=p.getList().end();it++){
		// nuevo->list_.push_back((*it));
		auxlist.push_back((*it));
	}
	Monomio m(x,0);
	// nuevo->list_.push_back(m);
	auxlist.push_back(m);
	nuevo->setList(auxlist);
	nuevo->sumarRepetidos();
	nuevo->sort();
	// Se devuelve el resultado
	return *nuevo;
}
ed::Polinomio & operator+(double const &x,  ed::Polinomio const &p)
{
	// COMPLETAR Y MODIFICAR
	// Se crea un nuevo objeto
	ed::Polinomio *nuevo = new ed::Polinomio;
	std::list<Monomio>::iterator it;
	std::list<Monomio> auxlist;
	for(it=p.getList().begin();it!=p.getList().end();it++){
		// nuevo->list_.push_back((*it));
		auxlist.push_back((*it));
	}
	Monomio m(x,0);
	// nuevo->list_.push_back(m);
	auxlist.push_back((m));
	nuevo->setList(auxlist);
	nuevo->sumarRepetidos();
	nuevo->sort();
	// Se devuelve el resultado
	return *nuevo;
}


	// COMPLETAR LOS OTROS OPERADORES DE SUMA

	////////////
	// Resta
	ed::Polinomio & operator-(ed::Polinomio const &p1,  ed::Polinomio const &p2)
	{
		// COMPLETAR Y MODIFICAR
		// Se crea un nuevo objeto
		ed::Polinomio *nuevo = new ed::Polinomio;
		std::list<Monomio>::iterator it;
		std::list<Monomio> auxlist;
		//std::list<Monomio>::iterator it2;
		for(it=p1.getList().begin();it!=p1.getList().end();it++){
			// nuevo->list_.push_back((*it));
			auxlist.push_back((*it));
		}
		for(it=p2.getList().begin();it!=p2.getList().end();it++){
			// nuevo->list_.push_back(-(*it));
			auxlist.push_back(-(*it));
		}
		nuevo->setList(auxlist);
		nuevo->sumarRepetidos();
		nuevo->sort();
		// Se devuelve el resultado
		return *nuevo;
	}

	ed::Polinomio & operator-(ed::Polinomio const &p,  ed::Monomio const &m)
	{
		// COMPLETAR Y MODIFICAR
		// Se crea un nuevo objeto
		ed::Polinomio *nuevo = new ed::Polinomio;
		std::list<Monomio>::iterator it;
		std::list<Monomio> auxlist;
		for(it=p.getList().begin();it!=p.getList().end();it++){
			// nuevo->list_.push_back((*it));
			auxlist.push_back((*it));
		}
		// nuevo->list_.push_back(-m);
		auxlist.push_back(-m);
		nuevo->setList(auxlist);
		nuevo->sumarRepetidos();
		nuevo->sort();
		// Se devuelve el resultado
		return *nuevo;
	}
	ed::Polinomio & operator-(ed::Monomio const &m,  ed::Polinomio const &p)
	{
		// COMPLETAR Y MODIFICAR
		// Se crea un nuevo objeto
		ed::Polinomio *nuevo = new ed::Polinomio;
		std::list<Monomio>::iterator it;
		std::list<Monomio> auxlist;
		for(it=p.getList().begin();it!=p.getList().end();it++){
			// nuevo->list_.push_back(-(*it));
			auxlist.push_back(-(*it));
		}
		// nuevo->list_.push_back(m);
		auxlist.push_back(m);
		nuevo->setList(auxlist);
		nuevo->sumarRepetidos();
		nuevo->sort();
		// Se devuelve el resultado
		return *nuevo;
	}
	ed::Polinomio & operator-(ed::Polinomio const &p,  double const &x)
	{
		// COMPLETAR Y MODIFICAR
		// Se crea un nuevo objeto
		ed::Polinomio *nuevo = new ed::Polinomio;
		std::list<Monomio>::iterator it;
		std::list<Monomio> auxlist;
		for(it=p.getList().begin();it!=p.getList().end();it++){
			// nuevo->list_.push_back((*it));
			auxlist.push_back((*it));
		}
		Monomio m(-x,0);
		// nuevo->list_.push_back(m);
		auxlist.push_back(m);
		nuevo->setList(auxlist);
		nuevo->sumarRepetidos();
		nuevo->sort();
		// Se devuelve el resultado
		return *nuevo;
	}
	ed::Polinomio & operator-(double const &x,  ed::Polinomio const &p)
	{
		// COMPLETAR Y MODIFICAR
		// Se crea un nuevo objeto
		ed::Polinomio *nuevo = new ed::Polinomio;
		std::list<Monomio>::iterator it;
		std::list<Monomio> auxlist;
		for(it=p.getList().begin();it!=p.getList().end();it++){
			// nuevo->list_.push_back(-(*it));
			auxlist.push_back(-(*it));
		}
		Monomio m(x,0);
		// nuevo->list_.push_back(m);
		auxlist.push_back(m);
		nuevo->setList(auxlist);
		nuevo->sumarRepetidos();
		nuevo->sort();
		// Se devuelve el resultado
		return *nuevo;
	}
	//////////////////
	// Multiplicación
	ed::Polinomio & operator*(ed::Polinomio const &p1,  ed::Polinomio const &p2)
	{
		// COMPLETAR Y MODIFICAR
		// Se crea un nuevo objeto
		ed::Polinomio *nuevo = new ed::Polinomio;
		std::list<Monomio>::iterator it1;
		std::list<Monomio>::iterator it2;
		std::list<Monomio> auxlist;
		for(it1=p1.getList().begin();it1!=p1.getList().end();it1++){
			for(it2=p2.getList().begin();it2!=p2.getList().end();it2++){
				// nuevo->list_.push_back((*it1)*(*it2));
				auxlist.push_back((*it1)*(*it2));
			}
		}
		nuevo->setList(auxlist);
		nuevo->sumarRepetidos();
		nuevo->sort();
		// Se devuelve el resultado
		return *nuevo;
	}

	ed::Polinomio & operator*(ed::Polinomio const &p,  ed::Monomio const &m)
	{
		// COMPLETAR Y MODIFICAR
		// Se crea un nuevo objeto
		ed::Polinomio *nuevo = new ed::Polinomio;
		std::list<Monomio>::iterator it;
		std::list<Monomio> auxlist;
		for(it=p.getList().begin();it!=p.getList().end();it++){
			// nuevo->list_.push_back((*it)*m);
			auxlist.push_back((*it)*m);
		}
		nuevo->setList(auxlist);
		//nuevo->sumarRepetidos();
		//nuevo->sort();
		// Se devuelve el resultado
		return *nuevo;
	}
	ed::Polinomio & operator*(ed::Monomio const &m,  ed::Polinomio const &p)
	{
		// COMPLETAR Y MODIFICAR
		// Se crea un nuevo objeto
		ed::Polinomio *nuevo = new ed::Polinomio;
		std::list<Monomio>::iterator it;
		std::list<Monomio> auxlist;
		for(it=p.getList().begin();it!=p.getList().end();it++){
			// nuevo->list_.push_back((*it)*m);
			auxlist.push_back((*it)*m);
		}
		nuevo->setList(auxlist);
		//nuevo->sumarRepetidos();
		//nuevo->sort();
		// Se devuelve el resultado
		return *nuevo;
	}
	ed::Polinomio & operator*(ed::Polinomio const &p,  double const &x)
	{
		// COMPLETAR Y MODIFICAR
		// Se crea un nuevo objeto
		ed::Polinomio *nuevo = new ed::Polinomio;
		std::list<Monomio>::iterator it;
		std::list<Monomio> auxlist;
		for(it=p.getList().begin();it!=p.getList().end();it++){
			// nuevo->list_.push_back((*it)*x);
			auxlist.push_back((*it)*x);
		}
		nuevo->setList(auxlist);
		//nuevo->sumarRepetidos();
		//nuevo->sort();
		// Se devuelve el resultado
		return *nuevo;
	}
	ed::Polinomio & operator*(double const &x,  ed::Polinomio const &p)
	{
		// COMPLETAR Y MODIFICAR
		// Se crea un nuevo objeto
		ed::Polinomio *nuevo = new ed::Polinomio;
		std::list<Monomio>::iterator it;
		std::list<Monomio> auxlist;
		for(it=p.getList().begin();it!=p.getList().end();it++){
			// nuevo->list_.push_back((*it)*x);
			auxlist.push_back((*it)*x);
		}
		nuevo->setList(auxlist);
		//nuevo->sumarRepetidos();
		//nuevo->sort();
		// Se devuelve el resultado
		return *nuevo;
	}

	////////////
	// División
	ed::Polinomio & operator/(ed::Polinomio const &p1,  ed::Polinomio const &p2)
	{
		// COMPLETAR Y MODIFICAR
		// Se crea un nuevo objeto
		#ifndef NDEBUG
		assert(p1.getGrado()>p2.getGrado());
		#endif
		ed::Polinomio *nuevo = new ed::Polinomio;
		std::list<Monomio>::iterator it1;
		std::list<Monomio>::iterator it2;
		std::list<Monomio> auxlist;
		for(it1=p1.getList().begin();it1!=p1.getList().end();it1++){
			for(it2=p2.getList().begin();it2!=p2.getList().end();it2++){
				// nuevo->list_.push_back((*it1)/(*it2));
				auxlist.push_back((*it1)/(*it2));
			}
		}
		nuevo->setList(auxlist);
		nuevo->sumarRepetidos();
		nuevo->sort();
		// Se devuelve el resultado
		return *nuevo;
	}

	ed::Polinomio & operator/(ed::Polinomio const &p,  ed::Monomio const &m)
	{
		// COMPLETAR Y MODIFICAR
		// Se crea un nuevo objeto
		#ifndef NDEBUG
		assert(p.getGrado()>m.getGrado());
		#endif
		ed::Polinomio *nuevo = new ed::Polinomio;
		std::list<Monomio>::iterator it;
		std::list<Monomio> auxlist;
		for(it=p.getList().begin();it!=p.getList().end();it++){
			// nuevo->list_.push_back((*it)/m);
			auxlist.push_back((*it)/m);
		}
		nuevo->setList(auxlist);
		//nuevo->sumarRepetidos();
		//nuevo->sort();
		// Se devuelve el resultado
		return *nuevo;
	}
	ed::Polinomio & operator/(ed::Monomio const &m,  ed::Polinomio const &p)
	{
		// COMPLETAR Y MODIFICAR
		// Se crea un nuevo objeto
		#ifndef NDEBUG
		assert(m.getGrado()>p.getGrado());
		#endif
		ed::Polinomio *nuevo = new ed::Polinomio;
		std::list<Monomio>::iterator it;
		std::list<Monomio> auxlist;
		for(it=p.getList().begin();it!=p.getList().end();it++){
			// nuevo->list_.push_back((*it)/m);
			auxlist.push_back((*it)/m);
		}
		nuevo->setList(auxlist);
		//nuevo->sumarRepetidos();
		//nuevo->sort();
		// Se devuelve el resultado
		return *nuevo;
	}
	ed::Polinomio & operator/(ed::Polinomio const &p,  double const &x)
	{
		// COMPLETAR Y MODIFICAR
		// Se crea un nuevo objeto
		#ifndef NDEBUG
		assert(x!=0.0);
		#endif
		ed::Polinomio *nuevo = new ed::Polinomio;
		std::list<Monomio>::iterator it;
		std::list<Monomio> auxlist;
		for(it=p.getList().begin();it!=p.getList().end();it++){
			// nuevo->list_.push_back((*it)/x);
			auxlist.push_back((*it)/x);
		}
		nuevo->setList(auxlist);
		//nuevo->sumarRepetidos();
		//nuevo->sort();
		// Se devuelve el resultado
		return *nuevo;
	}
	ed::Polinomio & operator/(double const &x,  ed::Polinomio const &p)
	{
		// COMPLETAR Y MODIFICAR
		// Se crea un nuevo objeto
		#ifndef NDEBUG
		assert(p.getGrado()==0);
		assert(std::abs(p.getList().front().getCoeficiente()-0.0)<COTA_ERROR);
		#endif
		ed::Polinomio *nuevo = new ed::Polinomio;
		std::list<Monomio>::iterator it;
		std::list<Monomio> auxlist;
		for(it=p.getList().begin();it!=p.getList().end();it++){
			// nuevo->list_.push_back((*it)/x);
			auxlist.push_back((*it)/x);
		}
		nuevo->setList(auxlist);
		//nuevo->sumarRepetidos();
		//nuevo->sort(ordena_grado);
		// Se devuelve el resultado
		return *nuevo;
	}


////////////////////////////////////////////////////////////////////////////

// Sobrecarga del operador de entrada
istream &operator>>(istream &stream, Polinomio &p)
{
	std::list<Monomio>::iterator it;
	for(it=p.getList().begin();it!=p.getList().end();it++){
		stream>>(*it);
	}
	// Se devuelve el flujo de entrada
  return stream;
}



// Sobrecarga del operador de salida
ostream &operator<<(ostream &stream, Polinomio const &p)
{
	std::list<Monomio>::iterator it;
	for(it=p.getList().begin();it!=p.getList().end();it++){
		stream<<(*it);
	}

	// Se devuelve el flujo de salida
  return stream;
}


} // Fin del espacio de nombres ed
