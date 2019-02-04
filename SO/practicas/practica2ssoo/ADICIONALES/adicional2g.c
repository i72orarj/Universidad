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
sem_t semaforo;

void * funcion (void * valor);

int main(){
	extern int contador;
	int IDHilos[NHilos];						//parametro que se le pasa a cada hilo
	pthread_t IDHilo[NHilos];					//vector que almacena id´s de hilos
	int * devuelto;//int * devuelto[NHilos];

	for(int i=0;i<NHilos;i++){
		IDHilos[i]=i;			//al hilo 0 un 0, al i un i
		pthread_create(&IDHilo[i], NULL, &funcion, (void *) &IDHilos[i]);	
		}

	for(int i=0;i<NHilos;i++){
		pthread_join(IDHilo[i], (void **) &devuelto); //pthread_join(IDHilo[i], (void **) &devuelto[i]);
		//printf("El hilo %d devuelve %d \n", IDHilos[i], *devuelto);//printf("El hilo %d devuelve %d \n", IDHilos[i], *devuelto[i]);
	}

/*	for(int i=0;i<NHilos;i++)
		printf("Devuelto[%i]: %i\n", i, *devuelto);//printf("Devuelto[%i]: %i\n", i, *(devuelto[i]));*/ 


}

void * funcion(void * valor){
	extern int contador;
	sem_t semaforo;
	sem_init(&semaforo, 0, 1);

	int * retorno;

	int * parametro = (int *) valor; 		//si quiero usar el parametro, debo hacer una conversion de void al tìpo de valor que yo se que le he pasado

	int local;
	for(int x=0;x<100;x++){
		sem_wait(&semaforo);
		local=contador;
		local++;
		contador=local;
		sem_post(&semaforo);}
	printf("El hilo %d deja el contador: %d \n",*parametro, contador);

	retorno=(int *)malloc(sizeof(int));
	*retorno=contador;

	sem_destroy(&semaforo);
	pthread_exit((void *) retorno);
}