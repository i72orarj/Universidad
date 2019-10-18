#ifndef __GRAFO_HPP__
#define __GRAFO_HPP__

#include <cassert>
#include <iostream>

using namespace std;

namespace ed
{

	template <class G_Nodo, class G_Lado>
	class Grafo
	{
	private:

		G_Nodo *_nodos;
		G_Lado **_lados;
		int _dimension;

	public:

		// constructores
		Grafo(){
			this->setNodos(NULL);
			this->setLados(NULL);
			// this->setDimension(0);
		}
		Grafo(int n){
			this->setDimension(n);
			_nodos=new G_Nodo[n];
			_lados=new G_Lado*[n];
			for(int i=0;i<n;i++){
				_lados[i]=new G_Lado[n];
			}
			//reservando memoria dinamica para n elemntos en vector y en matriz
		}
		Grafo(const Grafo<G_Nodo,G_Lado> &g){
			*this=g;
		}
		// destructor
		~Grafo(){
			std::cout << "Usando destructor" << '\n';
			borrarGrafo();
			std::cout << "Destructor usado" << '\n';
		}

		// funciones
		void setNodos(G_Nodo* v){
			this->_nodos=v;
		}
		void setLados(G_Lado** m){
			this->_lados=m;
		}
		void setDimension(const int &x){
			this->_dimension=x;
		}
		G_Nodo* getNodos()const{
			return _nodos;
		}
		G_Lado** getLados()const{
			return _lados;
		}
		int getDimension()const{
			return _dimension;
		}
		void borrarGrafo() {	// cabecera indicada para que compile
			delete[] _nodos;
			int n=this->getDimension();
			for(int i=0;i<n;i++){
				delete[] _lados[i];
			}
			delete[] _lados;
		}
		Grafo &operator =(const Grafo<G_Nodo,G_Lado> &g){
			this->setNodos(g.getNodos());
			this->setLados(g.getLados());
			this->setDimension(g.getDimension());
			return *this;
		}
		// bool cargarGrafo(Grafo<G_Nodo, G_Lado> * &g);
	};
}

#endif
