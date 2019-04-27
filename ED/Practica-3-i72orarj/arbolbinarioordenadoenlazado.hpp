#ifndef __ARBOLBINARIOORDENADO_HPP__
#define __ARBOLBINARIOORDENADOENLAZADO_HPP__

#include <iostream>
#include <cassert>
#include <vector>
#include "arbolbinarioordenado.hpp"
#include "operadornodo.hpp"

using namespace std;
/*!
\brief Espacio de nombres para la asignatura Estructura de datos.
*/
namespace ed
{
	/*!\brief Interfaz para definir un ArbolBinario ordenado.

	Define una interfaz para definir un ArbolBinarioOrdenado.

	\arg G define el campo de información a contener en el arbol.
	\pre G debe tener definidos los operadores < y ==.
	*/
	template<class G>
	class ArbolBinarioOrdenadoEnlazado:public ArbolBinarioOrdenado<G>
	{
	private:

		/*!\brief Define un nodo del arbol binario.*/
		class NodoArbolBinario
		{
		private:
			G _info;  //Valor informativo almacenado en el nodo
			NodoArbolBinario * _izquierdo;  //Puntero al hijo izquierdo
			NodoArbolBinario * _derecho;  //Puntero al hijo derecho

		public:
			NodoArbolBinario (const G &info)
			{
				this->setInfo(info);
				this->setIzquierdo(NULL);
				this->setDerecho(NULL);
				#ifndef NDEBUG
				assert(esHoja());
				#endif
			}

			NodoArbolBinario (const NodoArbolBinario &n)
			{
				this=n;
			}

			/*!\brief Observadores.*/
			const G & getInfo() const
			{
				return _info;
			}

			NodoArbolBinario *getIzquierdo() const
			{
				return _izquierdo;
			}

			NodoArbolBinario *getDerecho() const
			{
				return _derecho;
			}

			bool esHoja() const
			{
				if(getIzquierdo()==NULL && getDerecho()==NULL){
					return true;
				}
				else{
					return false;
				}
			}

			void recorridoPreOrden (OperadorNodo<G> &operador) const
			{
				operador.aplicar(this->getInfo());
				if(this->getIzquierdo()!=NULL){
					this->getIzquierdo()->recorridoPreOrden(operador);
				}
				if(this->getDerecho()!=NULL){
					this->getDerecho()->recorridoPreOrden(operador);
				}
			}

			void recorridoPostOrden (OperadorNodo<G> &operador) const
			{
				if(this->getIzquierdo()!=NULL){
					this->getIzquierdo()->recorridoPostOrden(operador);
				}
				if(this->getDerecho()!=NULL){
					this->getDerecho()->recorridoPostOrden(operador);
				}
				operador.aplicar(this->getInfo());
			}

			void recorridoInOrden (OperadorNodo<G> &operador) const
			{
				if(this->getIzquierdo()!=NULL){
					this->getIzquierdo()->recorridoInOrden(operador);
				}
				operador.aplicar(this->getInfo());
				if(this->getDerecho()!=NULL){
					this->getDerecho()->recorridoInOrden(operador);
				}
			}

			/*!\brief Modificadores. */
			void setInfo(const G &info)
			{
				_info=info;
			}

			void setIzquierdo(NodoArbolBinario *n)
			{
				_izquierdo=n;
			}

			void setDerecho(NodoArbolBinario *n)
			{
				_derecho=n;
			}

			NodoArbolBinario & operator=(const NodoArbolBinario &n)
			{
				#ifndef NDEBUG
				assert(this->getInfo()!=n.getInfo()
						|| this->getIzquierdo()!=n.getIzquierdo()
						|| this->getDerecho()!=n.getDerecho());
				#endif
				this->_info=n.getInfo;
				this->_izquierdo=n.getIzquierdo;
				this->_derecho=n.getDerecho;
				return *this;
			}

		}; //Fin clase NodoArbolBinario

		//Implementación de la raíz
		NodoArbolBinario * _raiz; /*!<La raiz del árbol*/
		NodoArbolBinario * _actual; /*!<Cursor al nodo actual*/
		NodoArbolBinario * _padre; /*!<Cursor al nodo actual*/

	public:

		ArbolBinarioOrdenadoEnlazado ()
		{
			this->_raiz=NULL;
			this->_actual=NULL;
			this->_padre=NULL;
			#ifndef NDEBUG
			assert(estaVacio());
			#endif
		}

		ArbolBinarioOrdenadoEnlazado (const ArbolBinarioOrdenadoEnlazado<G>& a)
		{
			this=a;
		}

		~ArbolBinarioOrdenadoEnlazado ()
		{
			if (not estaVacio())
			borrarArbol();
			cout << "Destructor Usado \n";
		}

		ArbolBinarioOrdenadoEnlazado &operator=(const ArbolBinarioOrdenadoEnlazado& a)
		{
			#ifndef NDEBUG
			assert(this->_raiz!=a._raiz);
			#endif
			//this->borrarArbol();
			ArbolBinarioOrdenadoEnlazado* nuevo=new ArbolBinarioOrdenadoEnlazado();
			AlmacenarNodo<G> operador;
			a.recorridoPreOrden(operador);
			std::vector<G> v=operador.vectorNodos();
		//	std::vector<G>::iterator it;
			for(int i=0;i<v.size();i++){
				nuevo->insertar(v[i]);
			}
			return *nuevo;
			}// recorrido pre orden y guardando en vector
			// crear nuevo arbol y copiar elementos del vector al arbol
		// hacer aqui la copia entera del arbol  y usar esto en constructor copia
		//pasar todo a vector y luego insertar los elementos del vector en el nuevo arbol

		bool insertar(const G &x)
		{
			NodoArbolBinario* nuevo=new NodoArbolBinario(x);//nuevo nodo que sera insertado
			if(_raiz==NULL){
				_raiz=nuevo;
				return true;
			}
			else{
				_actual=_raiz;
				_padre=_raiz;
				while(existeActual()){
					if(_actual->getInfo()>x){
						if(_actual->getIzquierdo()==NULL){
							_actual->setIzquierdo(nuevo);
							_padre=_actual;
							_actual=_actual->getIzquierdo();
							return true;
						}
						_padre=_actual;
						_actual=_actual->getIzquierdo();
					}
					else if(_actual->getInfo()<x){
						if(_actual->getDerecho()==NULL){
							_actual->setDerecho(nuevo);
							_padre=_actual;
							_actual=_actual->getDerecho();
							return true;
						}
						_padre=_actual;
						_actual=_actual->getDerecho();
					}
				}
			}
			return false;
		}

		void borrarArbol()
		{
			this->_raiz=NULL;
			this->_actual=NULL;
			this->_padre=NULL;
		}

		bool borrar()
		{
			NodoArbolBinario* aux=new NodoArbolBinario(_actual->getInfo());//aux para recorrer y no perder el actual
			NodoArbolBinario* padre_aux=new NodoArbolBinario(_padre->getInfo());
			aux=_actual;
			padre_aux=_padre;
			if(_actual->esHoja()==true){
				if(_padre->getIzquierdo()==_actual){
					_padre->setIzquierdo(NULL);
				}
				if(_padre->getDerecho()==_actual){
					_padre->setDerecho(NULL);
				}
				return true;
			}
			else{
				if(_actual->getDerecho()==NULL){ //comprueba si puede ir a la derecha
					if(_padre->getIzquierdo()==_actual){
						_padre->setIzquierdo(_actual->getIzquierdo());
					}
					if(_padre->getDerecho()==_actual){
						_padre->setDerecho(_actual->getIzquierdo());
					}
					return true;
				}
				else{
					padre_aux=_actual;
					aux=_actual->getDerecho();
					while(aux->getIzquierdo()!=NULL){//recorre hasta cuando no pueda mas a la izq
						padre_aux=aux;
						aux=aux->getIzquierdo();
					}
					_actual->setInfo(aux->getInfo());//cambia el valor del nodo que se "borra"
					padre_aux->setIzquierdo(NULL);//borra el nodo, ya que se cambia de lugar
					if(aux->getDerecho()!=NULL){//si al llegar al final de la izq hay nodo a la derecha este sera el izq del padre
						padre_aux->setIzquierdo(aux->getDerecho());
					}
					return true;
				}
			}
			return false;
			// comprobar si esHoja
			// nodo con hijos
			//  dercho y todo a izq hasta llegar al ultimo
		}

		void recorridoPreOrden (OperadorNodo<G> &operador) const
		{
			_raiz->recorridoPreOrden(operador);
		}

		void recorridoPostOrden (OperadorNodo<G> &operador) const
		{
			_raiz->recorridoPostOrden(operador);
		}

		void recorridoInOrden (OperadorNodo<G> &operador) const
		{
			_raiz->recorridoInOrden(operador);
		}

		bool buscar(const G& x) //const
		{
			if(estaVacio()){
				return false;
			}
			else{
				_actual=_raiz;
				while(existeActual()){
					if(_actual->getInfo()==x){
						return true;
					}
					else if(_actual->getInfo()>x){
						_padre=_actual;
						_actual=_actual->getIzquierdo();
					}
					else if(_actual->getInfo()<x){
						_padre=_actual;
						_actual=_actual->getDerecho();
					}
				}
			}
			return false;
		}//mirar si es mayor o menor

		bool estaVacio() const
		{
			if(_raiz==NULL){
				return true;
			}
			else{
				return false;
			}
		}

		G raiz() const
		{
			#ifndef NDEBUG
			assert(!estaVacio());
			#endif
			return _raiz->getInfo();
		}

		bool existeActual() const
		{
			#ifndef NDEBUG
			assert(!estaVacio());
			#endif
			if(_actual==NULL){
				return false;
			}
			else{
				return true;
			}
		}

		G actual() const
		{
			#ifndef NDEBUG
			assert(existeActual());
			#endif
			return _actual->getInfo();
		}

		/*!@}*/
	};

} //namespace ed

#endif //__ARBOLORDENADO_HPP__
