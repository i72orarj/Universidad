#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#define N 5

void *derecha(void *arg);
void *izquierda(void *arg);
int der=0;
int izq=0;

sem_t s_mutex_vacio, s_mutex_der, s_mutex_izq;

main()
{
	pthread_t thd1[N], thd2[N];
	int i, v[N];

	sem_init(&s_mutex_vacio, 0, 1);
	sem_init(&s_mutex_der, 0, 1);
	sem_init(&s_mutex_izq, 0, 1);

	for(i=0; i<N; i++)
	{
		v[i]=i;
		pthread_create(&thd1[i],NULL, (void *) derecha, (void *) &v[i]);
		pthread_create(&thd2[i],NULL, (void *) izquierda, (void *) &v[i]);
	}

	for(i=0; i<N;i++)
	{
		pthread_join(thd1[i], NULL);
		pthread_join(thd2[i], NULL);
	}
}

void *derecha(void *arg)
{
	int *i=(int *)arg;
	while(1)
	{
		sleep(2);
		sem_wait(&s_mutex_der);
		der++;
		if(der==1)
			sem_wait(&s_mutex_vacio);
		sem_post(&s_mutex_der);
		printf("El coche %d está pasando por la derecha\n", *i);
		sleep(1);
		sem_wait(&s_mutex_der);
		der--;
		if(der==0)
		{
			puts("Ya no quedan más coches");
			sem_post(&s_mutex_vacio);
		}
		sleep(1);
		sem_post(&s_mutex_der);
	}
	pthread_exit(NULL);
}

void *izquierda(void *arg)
{
	int *i=(int *)arg;
	while(1)
	{
		sleep(2);
		sem_wait(&s_mutex_izq);
		izq++;
		if(izq==1)
			sem_wait(&s_mutex_vacio);
		sem_post(&s_mutex_izq);
		printf("El coche %d está pasando por la izquierda\n", *i);
		sleep(1);
		sem_wait(&s_mutex_izq);
		izq--;
		if(izq==0)
		{
			puts("Ya no quedan más coches");
			sem_post(&s_mutex_vacio);
		}
		sleep(1);
		sem_post(&s_mutex_izq);
	}
	pthread_exit(NULL);
}