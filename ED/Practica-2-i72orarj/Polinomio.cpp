/*!
   \file Polinomio.cpp
   \brief Fichero que contiene el código de las funciones de la clase Polinomio
*/


// Ficheros de cabecera
#include <iostream>
#include <list>

#include "Polinomio.hpp"
#include "auxiliar_ordenacion.hpp"
#include "operadoresExternosPolinomios.hpp"
#include "../Practica-1-i72orarj/Monomio.hpp"
#include "../Practica-1-i72orarj/operadoresExternosMonomios.hpp"

// Operadores de asignación

/////////////////////////////////////////////////////////////

ed::Polinomio & ed::Polinomio::operator=(ed::Polinomio &p)
{
	#ifndef NDEBUG
		assert(*this!=p);
	#endif
	std::list<Monomio>::iterator it;
	list_.clear();
	for(it=p.list_.begin();it!=p.list_.end();it++){
		list_.push_back(*it);
	}
	#ifndef NDEBUG
		assert(*this==p);
	#endif
	// Se devuelve el objeto actual
	return *this;
}


ed::Polinomio & ed::Polinomio::operator=(ed::Monomio const &m)
{
	#ifndef NDEBUG
		assert(*this!=m);
	#endif
	list_.clear();
	list_.push_back(m);
	#ifndef NDEBUG
		assert(list_.size()==1);
	#endif
	// Se devuelve el objeto actual
	return *this;
}


ed::Polinomio & ed::Polinomio::operator=(double const &x)
{
	#ifndef NDEBUG
		assert(*this!=x);
	#endif
	Monomio m(x,0);
	list_.clear();
	list_.push_back(m);
	// Se devuelve el objeto actual
	return *this;
}

//////////////////////////////////////////////////////////////

ed::Polinomio & ed::Polinomio::operator+=(ed::Polinomio &p)
{
	//Polinomio aux();
	std::list<Monomio>::iterator it;
	std::list<Monomio> auxlist;
	//std::list<Monomio>::iterator it2;
	//aux.list_.clear();
	for(it=this->list_.begin();it!=this->list_.end();it++){
		// aux.list_.push_back((*it));
		auxlist.push_back((*it));
	}
	for(it=p.list_.begin();it!=p.list_.end();it++){
		// aux.list_.push_back((*it));
		auxlist.push_back((*it));
	}
	this->setList(auxlist);
	this->sumarRepetidos();
	// aux.sumarRepetidos();
	//aux.list_.sort(ordena_grado);
	// Se devuelve el objeto actual
	return *this;
}

ed::Polinomio & ed::Polinomio::operator+=(ed::Monomio const &m)
{
	std::list<Monomio>::iterator it;
	if(esNulo()){
		list_.clear();
		list_.push_back(m);
		return *this;
	}
	//Polinomio p();
	for(it=this->list_.begin();it!=this->list_.end();it++){
		if((*it).getGrado()==m.getGrado()){
			(*it).setCoeficiente((*it).getCoeficiente()+m.getCoeficiente());
			//Monomio maux((*it).getCoeficiente()+m.getCoeficiente(),m.getGrado());
			//p.list_.push_back(maux);
		}
	}
	return *this;
}

ed::Polinomio & ed::Polinomio::operator+=(double const &x){
	std::list<Monomio>::iterator it;
	//Polinomio p();
	Monomio m(x,0);
	if(esNulo()){
		list_.clear();
		list_.push_back(m);
		return *this;
	}
	for(it=this->list_.begin();it!=this->list_.end();it++){
		if((*it).getGrado()==0){
			(*it).setCoeficiente((*it).getCoeficiente()+x);
			//Monomio m((*it).getCoeficiente()+x,(*it).getGrado());
			//p.list_.push_back(m);
		}
	}
	return *this;
}

ed::Polinomio & ed::Polinomio::operator-=(ed::Polinomio &p)
{
	//Polinomio aux();
	std::list<Monomio> auxlist;
	std::list<Monomio>::iterator it;
	//std::list<Monomio>::iterator it2;
	//aux.list_.clear();
	for(it=this->list_.begin();it!=this->list_.end();it++){
		// aux.list_.push_back((*it));
		auxlist.push_back((*it));
	}
	for(it=p.list_.begin();it!=p.list_.end();it++){
		// aux.list_.push_back((*it));
		auxlist.push_back((*it));
	}
	this->setList(auxlist);
	//aux.sumarRepetidos();
	//aux.list_.sort(ordena_grado);
	// Se devuelve el objeto actual
	return *this;
}

ed::Polinomio & ed::Polinomio::operator-=(ed::Monomio const &m)
{
	std::list<Monomio>::iterator it;
	if(esNulo()){
		list_.clear();
		list_.push_back(-m);
		return *this;
	}
	//Polinomio p();
	for(it=this->list_.begin();it!=this->list_.end();it++){
		if((*it).getGrado()==m.getGrado()){
			(*it).setCoeficiente((*it).getCoeficiente()-m.getCoeficiente());
			//Monomio maux((*it).getCoeficiente()+m.getCoeficiente(),m.getGrado());
			//p.list_.push_back(maux);
		}
	}
	return *this;;
}

ed::Polinomio & ed::Polinomio::operator-=(double const &x){
	std::list<Monomio>::iterator it;
	//Polinomio p();
	Monomio m(x,0);
	if(esNulo()){
		list_.clear();
		list_.push_back(m);
		return *this;
	}
	for(it=this->list_.begin();it!=this->list_.end();it++){
		if((*it).getGrado()==0){
			(*it).setCoeficiente((*it).getCoeficiente()+x);
			//Monomio m((*it).getCoeficiente()+x,(*it).getGrado());
			//p.list_.push_back(m);
		}
	}
	return *this;
}
ed::Polinomio & ed::Polinomio::operator*=(ed::Polinomio &p)
{
	std::list<Monomio>::iterator it1;
	std::list<Monomio>::iterator it2;
	std::list<Monomio> auxlist;
	//Polinomio aux();
	for(it1=this->list_.begin();it1!=this->list_.end();it1++){
		for(it2=p.list_.begin();it2!=p.list_.end();it2++){
			//Monomio m((*it1).getCoeficiente()*(*it2).getCoeficiente(),(*it1).getGrado()+(*it2).getGrado());
			//Monomio m((*it1)*(*it2));
			//aux.list_.push_back(m);
			auxlist.push_back((*it1)*(*it2));
		}
	}
	this->setList(auxlist);
	this->sumarRepetidos();
	//aux.sumarRepetidos();
	//usar vector aux para sumar los de mismo grado con el tamaño exacto
	//sumar monomios con igual grado
	// Se devuelve el objeto actual
	return *this;
}

ed::Polinomio & ed::Polinomio::operator*=(ed::Monomio const &m)
{
	std::list<Monomio>::iterator it;
	//Polinomio p();
	for(it=this->list_.begin();it!=this->list_.end();it++){
		//Monomio maux((*it).getCoeficiente()*m.getCoeficiente(),m.getGrado()+(*it).getGrado());
		// Monomio maux((*it)*m);
		// p.list_.push_back(maux);
		(*it)=(*it)*m;
	}
	//p.sumarRepetidos();
	return *this;
}

ed::Polinomio & ed::Polinomio::operator*=(double const &x){
	std::list<Monomio>::iterator it;
	// Polinomio p();
	for(it=this->list_.begin();it!=this->list_.end();it++){
		//Monomio m((*it).getCoeficiente()*x,(*it).getGrado());
		// Monomio m((*it)*x);
		// p.list_.push_back(m);
		(*it)=(*it)*x;
	}
	return *this;
}

ed::Polinomio & ed::Polinomio::operator/=(ed::Polinomio &p)
{
	#ifndef NDEBUG
	assert(this->getGrado()<=p.getGrado());
	assert(p.esNulo()==false);
	#endif
	std::list<Monomio>::iterator it1;
	std::list<Monomio>::iterator it2;
	std::list<Monomio> auxlist;
	//Polinomio aux();
	for(it1=this->list_.begin();it1!=this->list_.end();it1++){
		for(it2=p.list_.begin();it2!=p.list_.end();it2++){
			//Monomio m((*it1).getCoeficiente()/(*it2).getCoeficiente(),(*it1).getGrado()-(*it2).getGrado());
			// Monomio m((*it1)/(*it2));
			// aux.push_back(m);
			auxlist.push_back((*it1)/(*it2));
		}
	}
	this->setList(auxlist);
	// aux.sumarRepetidos();
	//sumar monomios con igual grado
	// Se devuelve el objeto actual
	return *this;
}

ed::Polinomio & ed::Polinomio::operator/=(ed::Monomio const &m)
{
	#ifndef NDEBUG
	assert(this->getGrado()<=m.getGrado());
	assert(this->esNulo()==false);
	#endif
	std::list<Monomio>::iterator it;
	std::list<Monomio> auxlist;
	//Polinomio p();
	for(it=this->list_.begin();it!=this->list_.end();it++){
		//Monomio maux((*it).getCoeficiente()/m.getCoeficiente(),(*it).getGrado()-m.getGrado());
		// Monomio maux((*it)/m);
		// p.list_.push_back(maux);
		auxlist.push_back((*it)/m);
	}
	this->setList(auxlist);
	return *this;
}

ed::Polinomio & ed::Polinomio::operator/=(double const &x){
	std::list<Monomio>::iterator it;
	// Polinomio p();
	std::list<Monomio> auxlist;
	for(it=this->list_.begin();it!=this->list_.end();it++){
		//Monomio m((*it).getCoeficiente()/x,(*it).getGrado());
		// Monomio m((*it)/x);
		// p.list_.push_back(m);
		auxlist.push_back((*it)/x);
	}
	this->setList(auxlist);
	return *this;
}

///////////////////////////////////////////////////////////////////////

// Funciones lectura y escritura de la clase Polinomio#include "auxiliar_ordenacion.h"

void ed::Polinomio::leerPolinomio(){
//preguntar cuantos o preguntar si continuar
//ordenar por grado al terminar
//comprobar monomio nuevo que no existe uno con ese grado
	int n;
	Monomio m;
	std::cout << "Introduzca el numero de monomios del Polinomio" << '\n';
	std::cin >> n;
	for(int i=0;i<n;i++){
		m.leerMonomio();
		this->list_.push_back(m);
	}
	this->sort();
}
void ed::Polinomio::escribirPolinomio(){
	std::list<Monomio>::iterator it;
	for(it=this->list_.begin();it!=this->list_.end();it++){
		(*it).escribirMonomio();
		if(it++!=this->list_.end()){
			std::cout << " + " ;
		}
	}
}

///////////////////////////////////////////////////////////////////////

// Funciones auxiliares de la clase Polinomio

double ed::Polinomio::calcularValor(const double &x){
	double suma=0;
	std::list<Monomio>::iterator it;
	for(it=this->list_.begin();it!=this->list_.end();it++){
		suma+=(*it).calcularValor(x);
	}
	return suma;
}
/*
bool ed::Polinomio::ordena_grado(const ed::Monomio &a, const ed::Monomio &b){
  return (a.getGrado()>b.getGrado());
}*/
