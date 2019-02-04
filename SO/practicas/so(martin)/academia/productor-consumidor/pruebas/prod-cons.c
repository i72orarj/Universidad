#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#define N 5
sem_t s, n, c;

void *productor(int *i);
void *consumidor(int *i);
void anyadir(int i);
void extraer(int i);

int main()
{
	int v[N], i;
	pthread_t prod[N], cons[N];

	sem_init(&s,0,1);
	sem_init(&n,0,0);
	sem_init(&c,0,N);

	for(i=0;i<N;i++)
	{
		v[i]=i;
		pthread_create(&prod[i], NULL, (void *) productor, (void *) &v[i]);
		pthread_create(&cons[i], NULL, (void *) consumidor, (void *) &v[i]);
	}

	for(i=0;i<N;i++)
	{
		pthread_join(prod[i], NULL);
		pthread_join(cons[i], NULL);
	}
}

void *productor(int *i)
{
	while(1)
	{
		sem_wait(&c);
		sem_wait(&s);
		anyadir(*i);
		sem_post(&s);
		sem_post(&n);
	}
}

void *consumidor(int *i)
{
	while(1)
	{
		sem_wait(&n);
		sem_wait(&s);
		extraer(*i);
		sem_post(&s);
		sem_post(&c);
	}
}

void anyadir(int i)
{
	printf("Soy el productor %d y estoy anyadiendo\n", i);
	sleep(1);
}

void extraer(int i)
{
	printf("Soy el consumidor %d ye estoy extraiendo\n", i);
	sleep(1);
}