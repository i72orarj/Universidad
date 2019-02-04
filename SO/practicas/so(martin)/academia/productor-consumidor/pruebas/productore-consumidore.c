#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#define N 5
void *productor(int *indice);
void *consumidor(int *indice);
void anyadir(int i);
void extraer(int i);
sem_t s;
sem_t n;
sem_t c;

main()
{
	pthread_t prod[N], cons[N];
	int v[N], i;

	sem_init(&s, 0 ,1);
	sem_init(&n, 0, 0);
	sem_init(&c, 0, N);

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

void *productor(int *indice)
{
	while(1)
	{
		sem_wait(&c);
		sem_wait(&s);
		anyadir(*indice);
		sem_post(&s);
		sem_post(&n);
	}
	pthread_exit(NULL);
}

void *consumidor(int *indice)
{
	while(1)
	{
	sem_wait(&n);
	sem_wait(&s);
	extraer(*indice);
	sem_post(&s);
	sem_post(&c);
	}
	pthread_exit(NULL);
}

void anyadir(int i)
{
	int num=(rand()%3)+1;
	printf("Soy el %d y estoy añadiendo panes\n", i);
	sleep(num);
}
void extraer(int i)
{
	int num=(rand()%3)+1;
	printf("Soy el %d y estoy extrayendo panes\n", i);
	sleep(num);
}