/*2. Como se comentó en la práctica 1, los procesos a diferencia de los hilos, no comparten el mismo
espacio de memoria, por lo que si queremos que accedan a las mismas variables en memoria, estos
deben compartirla.
Realice un programa que expanda N procesos hijos. Cada hijo debe compartir
una variable denominada contador, que debe estar inicializada a cero. Esta variable debe ser
incrementada por cada hilo 100 veces. Imprima la variable una vez finalicen los hilos y analice el resultado obtenido. Un resultado previsible para 3 procesos sería 300, ¿ha sido así?*/

//Implemente de nuevo el ejercicio usando semáforos POSIX para proteger la exclusión mutua de la variable contador.

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

#define NHilos 10


int contador=0;
pthread_mutex_t semaforo;


void * funcion (void * valor);

int main(){
	extern int contador;
	int IDHilos[NHilos];		//parametro que se le pasa a cada hilo
	pthread_t IDHilo[NHilos];	//vector que almacena id´s de hilos
	int * devuelto[NHilos];

	for(int i=0;i<NHilos;i++){
		IDHilos[i]=i;			//al hilo 0 un 0, al i un i
		pthread_create(&IDHilo[i], NULL, &funcion, (void *) &IDHilos[i]);	
		}

	for(int i=0;i<NHilos;i++){
		pthread_join(IDHilo[i], (void **) &devuelto[i]);
		//printf("El hilo %d devuelve %d \n", IDHilos[i], *devuelto[i]);
	}

}

void * funcion(void * valor){
	extern int contador;
	pthread_mutex_t semaforo;
	pthread_mutex_init(&semaforo, NULL);
	int * retorno;
	int * parametro = (int *) valor; 		//si quiero usar el parametro, debo hacer una conversion de void al tìpo de valor que yo se que le he pasado

	int local;

	for(int x=0;x<100;x++){
		pthread_mutex_lock(&semaforo);
		local=contador;
		local++;
		contador=local;
		pthread_mutex_unlock(&semaforo);
	}


	printf("El hilo %d deja el contador: %d \n", *parametro, contador);




	retorno=(int *)malloc(sizeof(int));
	*retorno=contador;
	pthread_exit((void *) retorno);
}