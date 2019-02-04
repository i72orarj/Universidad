/*Implemente un programa que genere N hilos que comparten un vector de tamaño M. El programa principal inicializa el vector a 0 en todos sus valores antes de crear los hilos.

Cada hilo debe seleccionar aleatoriamente una posición del vector y sumarle 1. Esta operación la debe repetir 100 veces.
Dado que el vector es compartido estamos ante un problema de sección crítica que debemos resolver usando semáforos POSIX.

Una vez finalizados todos los hilos el programa principal deberá sumar todos los elementos del vector para verificar que el resultado es correcto.*/

#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define TAMANO 20
#define NHilos 3

int vector[TAMANO];
void * funcion(void * valor);
sem_t semaforo;

int main(){
	extern int vector[TAMANO];
	pthread_t IDHilos[NHilos];
	int Hilos[NHilos];
	sem_init(&semaforo, 0, 1);

	for(int i=0;i<TAMANO;i++)
		vector[i]=0;

	for(int i=0;i<NHilos;i++){
		Hilos[i]=i;
		pthread_create(&IDHilos[i],NULL,&funcion,(void *) &Hilos[i]);
	}

	for(int i=0;i<NHilos;i++)
		pthread_join(IDHilos[i], NULL);


	int sumatotal=0;
	for(int i=0;i<TAMANO;i++){
		sumatotal+=vector[i];
	}
	printf("El valor de suma total es %d y deberia ser: %d\n", sumatotal, NHilos*100);
}

void * funcion(void * valor){
	int * id;
	id=(int *) valor;

	srand(time(NULL));

	int azar;
	for(int i=0;i<100;i++){
		azar=rand()%20;
		sem_wait(&semaforo);
		int local=vector[azar];
		local++;
		vector[azar]=local;
		sem_post(&semaforo);
		printf("El hilo %d ha aumentado la posicion %d del vector \n", *id, azar);
	}

	return(0);
}