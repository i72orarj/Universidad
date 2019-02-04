#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define bufer 100
#define ITERACIONES 1000

int v[bufer];
sem_t critica;
sem_t EspaciosOcupados;
sem_t EspaciosLibres;

void * produce(void * p);
void * consume(void * p);

int main(){
	pthread_t IDHilo[2];
	IDHilo[0]=0;
	IDHilo[1]=1;
	int * ResultadoProductor, * ResultadoConsumidor;

	sem_init(&critica, 0, 1);
	sem_init(&EspaciosOcupados, 0, 0);
	sem_init(&EspaciosLibres, 0, bufer);

	int status=pthread_create(&IDHilo[0], NULL, &produce, NULL);
		if(status!=0){
			printf("error al crear 1º hilo\n");
			exit(-1);}

	status=pthread_create(&IDHilo[1], NULL, &consume, NULL);
		if(status!=0){
			printf("error al crear 2º hilo\n");
			exit(-1);}

	pthread_join(IDHilo[0], (void ** ) &ResultadoProductor);
	pthread_join(IDHilo[1], (void ** ) &ResultadoConsumidor);

	printf("Suma total calculada por el productor: %d\n",*ResultadoProductor);
	printf("Suma total calculada por el consumidor: %d\n", *ResultadoConsumidor);

	sem_destroy(&critica);
	sem_destroy(&EspaciosOcupados);
	sem_destroy(&EspaciosLibres);

	return 0;
}

void * produce(void * p){
	srand(time(NULL));
	int auxiliar=0;
	int dato;
	int indice=-1;
	for(int i=0;i<ITERACIONES;i++){
		sem_wait(&EspaciosLibres);
			dato=rand()%1001;
			auxiliar+=dato;
			indice=(indice+1)%bufer;
			printf("El hilo productor ha generado un nuevo producto, %d, almacenado en %d\n", dato, indice);
		sem_wait(&critica);
			v[indice]=dato;
		sem_post(&critica);
		sem_post(&EspaciosOcupados);
	}

	int * retorno;
	retorno=(int *) malloc(sizeof(int));
	*retorno=auxiliar;
	pthread_exit((void *) retorno);
}

void * consume(void * p){
	int suma=0;
	int indice=-1;

	for(int i=0;i<ITERACIONES;i++){
		sem_wait(&EspaciosOcupados);
			indice=(indice+1)%bufer;
			printf("El hilo consumidor consume el elemento que se guardaba en %d\n", indice);
		sem_wait(&critica);
			suma=suma+v[indice];
		sem_post(&critica);
		sem_post(&EspaciosLibres);
	}

	int * retorno;
	retorno=(int *) malloc(sizeof(int));
	*retorno=suma;
	pthread_exit((void *) retorno);

}
