#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <semaphore.h>
void *derecha(int *indice);
void *izquierda(int *indice);
sem_t s_mutex_vacio, s_mutex_der, s_mutex_izq;

int izq=0;
int der=0;

int main()
{
	int i, v[5];
	pthread_t hilo1[5], hilo2[5];


	sem_init(&s_mutex_der, 0, 1);
	sem_init(&s_mutex_izq, 0, 1);
	sem_init(&s_mutex_vacio, 0, 1);
	for(i=0;i<5;i++)
	{
		v[i]=i;
		pthread_create(&hilo1[i], NULL, (void *) izquierda, (void *) &v[i]);
	}
		for(i=0;i<5;i++)
	{
		v[i]=i;
		pthread_create(&hilo2[i], NULL, (void *) derecha, (void *) &v[i]);
	}


	for(i=0;i<5;i++)
	{
		pthread_join(hilo1[i], NULL);
		pthread_join(hilo2[i], NULL);
	}
}

void *derecha(int *indice)
{
	while(1)
	{
		sleep(2);
		
		sem_wait(&s_mutex_der);
		der++;
		if(der==1) sem_wait(&s_mutex_vacio);
		sem_post(&s_mutex_der);
		printf("Soy el coche %d y estoy pasando por la derecha\n", *indice);
		sleep(1);
		sem_wait(&s_mutex_der);
		der--;
		if(der==0)
		{
			printf("Ya han pasado todos los coches\n");
			sem_post(&s_mutex_vacio);
		} 
		sleep(1);
		sem_post(&s_mutex_der);
	
	}
	pthread_exit(NULL);
}

void *izquierda(int *indice)
{
	while(1)
	{
		sleep(2);
	
		sem_wait(&s_mutex_izq);
		izq++;
		if(izq==1) sem_wait(&s_mutex_vacio);
		sem_post(&s_mutex_izq);
		printf("Soy el coche %d y estoy pasando por la izquierda\n", *indice);
		sleep(1);
		sem_wait(&s_mutex_izq);
		izq--;
		if(izq==0)
		{
			printf("Ya han pasado todos los coches\n");
			sem_post(&s_mutex_vacio);
		} 
		sleep(1);
		sem_post(&s_mutex_izq);
		
	}
	pthread_exit(NULL);
}
