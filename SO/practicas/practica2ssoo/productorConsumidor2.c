#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define bufer 50
#define ITERACIONES 400
#define P 4
#define C 2


int indiceP=-1;
int indice=-1;
int v[bufer];
sem_t critica;
sem_t EspaciosOcupados;
sem_t EspaciosLibres;

void * produce(void * p);
void * consume(void * p);
int max(int a, int b);

int main(){

	printf("************%d PRODUCTORES CON %d PRODUCCIONES*************\n", P, ITERACIONES);
	printf("************%d CONSUMIDORES*************\n\n",C);

	pthread_t IDHiloProductor[P];
	pthread_t IDHiloConsumidor[C];

	sem_init(&critica, 0, 1);
	sem_init(&EspaciosOcupados, 0, 0);
	sem_init(&EspaciosLibres, 0, bufer);

	int ve[max(P,C)];
	for(int i=0;i<(P+C);i++){
			ve[i]=i;
	}
	for(int i=0;i<P;i++){
			int status=pthread_create(&IDHiloProductor[i], NULL, &produce, (void *) &ve[i]);
			if(status!=0){
				printf("Error al crear %dº hilo productor\n", ve[i]);
				exit(-1);}
	}

	for(int i=0;i<C;i++){
			int status=pthread_create(&IDHiloConsumidor[i], NULL, &consume, (void *) &ve[i]);
			if(status!=0){
				printf("Error al crear %dº hilo consumidor\n", ve[i]);
				exit(-1);}
	}

	int totalProducido=0;
	int totalConsumido=0;
	int * ResultadoProductor, * ResultadoConsumidor;

	for(int i=0;i<P;i++){
		pthread_join(IDHiloProductor[i], (void ** ) &ResultadoProductor);
		totalProducido+=*ResultadoProductor;
	}
	for(int i=0;i<C;i++){
		pthread_join(IDHiloConsumidor[i], (void ** ) &ResultadoConsumidor);
		totalConsumido+=*ResultadoConsumidor;
	}
	printf("Suma total calculada por los %d productores: %d\n", P, totalProducido);
	printf("Suma total calculada por los %d consumidores: %d\n", C, totalConsumido);

	sem_destroy(&critica);
	sem_destroy(&EspaciosOcupados);
	sem_destroy(&EspaciosLibres);

	return 0;
}

void * produce(void * p){
	int * entero;
	entero=(int *) p;
	int CantidadTotalGeneradaPorHilo=0;
	srand(time(NULL));
	int dato;
	printf("HILO PRODUCTOR %d INICIALIZADO\n\n", *entero);

	for(int i=0;i<ITERACIONES;i++){
		sem_wait(&EspaciosLibres);
			dato=rand()%1001;
			CantidadTotalGeneradaPorHilo+=dato;
		sem_wait(&critica);
			indiceP=(indiceP+1)%bufer;
			v[indiceP]=dato;
		sem_post(&critica);
		sem_post(&EspaciosOcupados);
	}
	printf("HILO PRODUCTOR %d HA CONCLUIDO SUS %d PRODUCCIONES: %d....\n\n", *entero, ITERACIONES, CantidadTotalGeneradaPorHilo);
	int * retorno;
	retorno=(int *) malloc(sizeof(int));
	*retorno=CantidadTotalGeneradaPorHilo;
	pthread_exit((void *) retorno);
}

void * consume(void * p){
	int itera=P*ITERACIONES;
	itera=itera/C;
	int * entero;
	entero=(int *) p;
	int suma=0;
	printf("HILO CONSUMIDOR %d INICIALIZADO\n\n", *entero);

	for(int i=0;i<itera;i++){
		sem_wait(&EspaciosOcupados);
		sem_wait(&critica);
			indice=(indice+1)%bufer;
			suma+=v[indice];
		sem_post(&critica);
		sem_post(&EspaciosLibres);
	}
	printf("HILO CONSUMIDOR %d SALIENDO TRAS SUS HACER %d CONSUMICIONES: %d....\n\n", *entero, itera, suma);
	int * retorno;
	retorno=(int *) malloc(sizeof(int));
	*retorno=suma;
	pthread_exit((void *) retorno);
}

int max(int a, int b){
	if(a>b)
		return a;
	else
		return b;
}
