#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

#define N 5
void *fprod(int *i);
void *fcons(int *i);
sem_t s,n,c;

main()
{
	int i, v[N];
	pthread_t prod[N], cons[N];

	sem_init(&s, 0, 1);
	sem_init(&c,0,N);
	sem_init(&n,0,0);

	for(i=0;i<N; i++)
	{
		v[i]=i;
		pthread_create(&prod[i], NULL, (void *) fprod, (void *) &v[i]);
		pthread_create(&cons[i], NULL, (void *) fcons, (void *) &v[i]);
	}

	for(i=0;i<N;i++)
	{
		pthread_join(prod[i], NULL);
		pthread_join(cons[i], NULL);
	}
}

void *fprod(int *i)
{
	sleep(2);
	while(1)
	{
		sem_wait(&c);
		sem_wait(&s);
		printf("Soy el productor %d y estoy anyadiendo\n", *i);
		sleep(1);
		sem_post(&s);
		sem_post(&n);
	}
}


void *fcons(int *i)
{
	sleep(2);
	while(1)
	{
		sem_wait(&n);
		sem_wait(&s);
		printf("Soy el consumidor %d y estoy cogiendo\n", *i);
		sleep(1);
		sem_post(&s);
		sem_post(&c);
	}
}