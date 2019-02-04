#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

sem_t shombre, turno, smujer, mutexh, mutexm, empty;

int m=0, h=0;

void * hombre(void * parametro){


	int *id;

	id = (int *)parametro;


	sem_wait(&turno);
	sem_wait(&shombre); printf("\nSoy el hombre %d y me pongo en cola", *id);
	h++;
	if(h==1)
		sem_wait(&empty);
	sem_post(&shombre);
	sem_post(&turno);

	sem_wait(&mutexh);

	printf("\nSoy el hombre %d y entro al baño.", *id);
	sleep(5);

	sem_post(&mutexh);
	
	sem_wait(&shombre);
	h--;
	printf("\nEl hombre %d ha salido del baño", *id);
	if(h==0)
		sem_post(&empty);
	sem_post(&shombre);

pthread_exit(NULL);
}

void * mujer(void * parametro){

	int *id;

	id = (int *)parametro;

	sem_wait(&turno);
	sem_wait(&smujer); 
	printf("\nSoy la mujer %d y me pongo en cola", *id);
	m++;
	if(m==1)
		sem_wait(&empty);
	sem_post(&smujer);
	sem_post(&turno);
	
	sem_wait(&mutexm);

	printf("\nSoy la mujer %d y entro al baño.", *id);
	sleep(5);
	sem_post(&mutexm);
	
	sem_wait(&smujer);
	m--;
	printf("\nLa mujer %d ha salido del baño", *id);
	if(m==0)
		sem_post(&empty);
	sem_post(&smujer);

	
pthread_exit(NULL);
}

int main(){

	pthread_t hilos[10];

	int v[10], i;


	sem_init(&shombre, 0, 1);
	sem_init(&smujer, 0, 1);
	sem_init(&turno, 0, 1);
	sem_init(&empty, 0, 1);
	sem_init(&mutexh, 0, 3);
	sem_init(&mutexm, 0, 3);
	
	for(i=0 ; i<10 ; i++){

		v[i]=i+1;
		if(i%2==0){

			pthread_create(&hilos[i], NULL, hombre, (void *) &v[i]);

		}else{

			pthread_create(&hilos[i], NULL, mujer, (void *) &v[i]);

		}

	}

	for(i=0 ; i<10 ; i++){

		pthread_join(hilos[i], NULL);

	}

	sem_destroy(&shombre);
	sem_destroy(&smujer);
	sem_destroy(&empty);
	sem_destroy(&mutexh);
	sem_destroy(&mutexm);
	sem_destroy(&turno);

return 0;
}
