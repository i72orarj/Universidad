#include <iostream>
#include <string>
// #include <cstdlib> //Para usar system
// #include <fstream> //Para trabajar con ficheros

#include "grafo.hpp"
#include "algoritmosgrafos.hpp"
#include "funciones.hpp"

using namespace std;
using namespace ed;

int main()
{
	Grafo<string, int> g;
	std::string** caminos;
	std::string ciudad1, ciudad2;
	AlgoritmosGrafos<string, int> algoritmos;
	int opcion;
	bool grafoIntroducido = false;

	do {
		opcion = menu();
		switch (opcion) {
			case 1: // Cargar grafo desde fichero
			if ( grafoIntroducido )
			g.borrarGrafo(); // Si hay un grafo introducido se borra.

			grafoIntroducido = cargarGrafo(g);

			if (grafoIntroducido) {
				cout << "Grafo cargado correctamente \n";
				//Prueba de la asignación y del destructor
				// {
				// 	Grafo<string, int> g1 = g;
				// }
			}
			else
			cout << "Grafo no cargado \n";

			getchar();
			getchar();
			break;

			case 2: //Algoritmo de Floyd
			if ( grafoIntroducido )
				caminos=algoritmos.algoritmoFloyd(g);
			else
				cout << "Primero tiene que introducir un grafo\n";
			getchar();
			getchar();
			break;
			case 3: //distancia entre ciudades
			std::cout << "Intoduzca las dos ciudades" << '\n';
			std::cout << "Ciudad 1: ";
			std::cin >> ciudad1;
			std::cout << "Ciudad 2: ";
			std::cin >> ciudad2;
			algoritmos.recorridos(g,caminos,ciudad1,ciudad2);
			getchar();
			getchar();
			break;
		}
	} while (opcion!=0);

	return 0;
}
