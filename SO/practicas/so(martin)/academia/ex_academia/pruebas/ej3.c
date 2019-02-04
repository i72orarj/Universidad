#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
void * derecha(int *i);
void * izquierda(int *i);
#define N 5
int der=0;
int izq=0;
sem_t s_mutex_der, s_mutex_izq, s_mutex_vacio;

main()
{
	pthread_t der[N], izq[N];
	int i, v[N];

	sem_init(&s_mutex_der,0,1);
	sem_init(&s_mutex_izq,0,1);
	sem_init(&s_mutex_vacio,0,1);
	

	for(i=0;i<N;i++)
	{
		v[i]=i;
		pthread_create(&der[i], NULL, (void *) derecha, (void *) &v[i]);
		pthread_create(&izq[i], NULL, (void *) izquierda, (void *) &v[i]);

	}
	for(i=0;i<N;i++)
	{
		pthread_join(der[i], NULL);
		pthread_join(izq[i], NULL);
	}
}

void * derecha(int *i)
{
	while(1)
	{
		sleep(2);
		sem_wait(&s_mutex_der);
		der++;
		if(der==1)sem_wait(&s_mutex_vacio);
		sem_post(&s_mutex_der);
		printf("Soy el camión %d y estoy pasando por la derecha\n", *i);
		sleep(1);
		sem_wait(&s_mutex_der);
		der--;
		if(der==0)
		{
			puts("Ya no quedan camiones de la derecha.");
			sem_post(&s_mutex_vacio);
		}
		sleep(1);
		sem_post(&s_mutex_der);

	}
}


void * izquierda(int *i)
{
	while(1)
	{
		sleep(2);
		sem_wait(&s_mutex_izq);
		izq++;
		if(izq==1)sem_wait(&s_mutex_vacio);
		sem_post(&s_mutex_izq);
		printf("Soy el camión %d y estoy pasando por la izquierda\n", *i);
		sleep(1);
		sem_wait(&s_mutex_izq);
		izq--;
		if(izq==0)
		{
			puts("Ya no quedan camiones de la izquierda.");
			sem_post(&s_mutex_vacio);
		}
		sleep(1);
		sem_post(&s_mutex_izq);

	}
}