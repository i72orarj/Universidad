/*!
   \file Polinomio.hpp
   \brief Definición de la clase Polinomio
*/

#ifndef _POLINOMIO_HPP_
#define _POLINOMIO_HPP_

// Control de asertos
#include <cassert>

// Lista de STL
#include <list>

// Para usar la función abs
#include <cmath>

#include "PolinomioInterfaz.hpp"
#include "../Practica-1-i72orarj/Monomio.hpp"
#include "../Practica-1-i72orarj/operadoresExternosMonomios.hpp"
#include "auxiliar_ordenacion.hpp"


// Se incluye la clase Polinomio dentro del espacio de nombre de la asigantura: ed
namespace ed {

//!  Definición de la clase Polinomio que hereda de PolinomioInterfaz
class Polinomio//: public ed::PolinomioInterfaz
{

  //! \name Atributos privados de la clase Polinomio
   private:
     std::list<Monomio> list_;
   //! \name Funciones o métodos públicos de la clase Polinomio
   public:

	//! \name Constructores de la clase Polinomio

  inline Polinomio(){
    Monomio* m=new Monomio();
    m->setGrado(0);
    m->setCoeficiente(0.0);
    //list_.clear();
    this->list_.push_back(*m);
    #ifndef NDEBUG
    //assert(!esNulo());
    #endif
  }
  inline Polinomio(const Polinomio &p){
    list_=p.list_;
  }

  //! \name Observadores: funciones de consulta de la clase Polinomio

	inline bool esNulo()const{
    #ifndef NDEBUG
    assert(list_.size()!=1&&!list_.empty());
    #endif
    if(list_.empty()) return true;
    else if(list_.size()==1){
      if(list_.front().getGrado()==0 && std::abs(list_.front().getCoeficiente())<COTA_ERROR){
        return true;
      }
    }
    return false;
  }
  inline int getGrado()const{
    //list_.sort(ordena_grado);
    return list_.back().getGrado();
  }
  inline int getNumeroMonomios()const{
    return list_.size();
  }
  bool existeMonomio(int g)/*const*/{
    #ifndef NDEBUG
      assert(!esNulo());
    #endif
    std::list<Monomio>::iterator it;
    for(it=this->list_.begin();it!=this->list_.end();it++){
      if(it->getGrado()==g){
        return true;
      }
    }
    return false;
  }
  Monomio & getMonomio(int g)/*const*/{
    #ifndef NDEBUG
      assert(!esNulo());
    #endif
    ed::Monomio *nuevo = new ed::Monomio();
    //Monomio m(0.0,0);
    std::list<Monomio>::iterator it;
    for(it=list_.begin();it!=list_.end();it++){
      if(it->getGrado()==g){
        return *it;
      }
    }
    nuevo->setCoeficiente(0.0);
    nuevo->setGrado(0);
    //Monomio m(0.0,0);
    return *nuevo;
  }
  std::list<Monomio> getList()const{
    return list_;
  }

	//! \name Funciones de modificación de la clase Polinomio

  void sumarRepetidos(){
    int g=getGrado()+1;
    double v[g];
    Monomio m;
    int aux;
    for(int i=0;i<g;i++){
      v[i]=0;
    }
    std::list<Monomio>::iterator it;
    for(it=list_.begin();it!=list_.end();it++){
      aux=(*it).getGrado();
      v[aux]=v[aux]+(*it).getCoeficiente();
    }
    list_.clear();
    for(int i=0;i<g;i++){
      if(v[i]!=0){
        m.setGrado(i);
        m.setCoeficiente(v[i]);
        list_.push_back(m);
      }
    }
  }

  void setList(std::list<Monomio> &l){
    list_=l;
  }
  void sort();

 	////////////////////////////////////////////////////////////////

   //! \name Operadores de la clase Polinomio

	// COMPLETAR LOS COMENTARIOS DE DOXYGEN
	Polinomio & operator=(Polinomio &p);

	// COMPLETAR LOS COMENTARIOS DE DOXYGEN
	Polinomio & operator=(Monomio const &m);

	// COMPLETAR LOS COMENTARIOS DE DOXYGEN
	Polinomio & operator=(double const &x);

  // Operadores aritméticos y asignación

		// COMPLETAR LOS COMENTARIOS DE DOXYGEN
  Polinomio & operator+=(Polinomio &p);
  Polinomio & operator+=(Monomio const &m);
  Polinomio & operator+=(double const &x);
  Polinomio & operator-=(Polinomio &p);
  Polinomio & operator-=(Monomio const &m);
  Polinomio & operator-=(double const &x);
  Polinomio & operator*=(Polinomio &p);
  Polinomio & operator*=(Monomio const &m);
  Polinomio & operator*=(double const &x);
  Polinomio & operator/=(Polinomio &p);
  Polinomio & operator/=(Monomio const &m);
  Polinomio & operator/=(double const &x);

  /////////////////////////////////////////////////////////////////////////////////////

	//! \name Funciones lectura y escritura de la clase Polinomio

  void leerPolinomio();

	void escribirPolinomio();

	///////////////////////////////////////////////////////////////////////

	//! \name Funciones auxiliares de la clase Polinomio

	double calcularValor(const double &x);

  //bool ordena_grado(const Monomio &a, const Monomio &b);

}; // Fin de la definición de la clase Polinomio

} // \brief Fin de namespace ed.

//  _POLINOMIO_HPP_
#endif
