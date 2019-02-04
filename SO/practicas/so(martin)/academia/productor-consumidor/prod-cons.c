#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#define N 5
#define nhilos 5

void * productor(void *arg);

void * consumidor(void *arg);
void anyadir(int indice);
void extraer(int indice);

sem_t s;
sem_t n;
sem_t c;

main()
{
	srand(time(NULL));
	pthread_t pro[nhilos];
	pthread_t con[nhilos];
	int i, v[N];
	sem_init(&s, 0, 1);
	sem_init(&n, 0 , 0);
	sem_init(&c, 0, N);

	for(i=0;i<nhilos;i++)
	{
		v[i]=i;
		
		pthread_create(&pro[i], NULL, (void *) productor, (void *) &v[i]);
		pthread_create(&con[i], NULL, (void *) consumidor, (void *) &v[i]);
	}

	for(i=0;i<nhilos;i++)
	{
		pthread_join(pro[i],NULL);
		pthread_join(con[i],NULL);
	}
}

void * productor(void * arg)
{
	int *indice= (int *) arg;
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

void * consumidor(void *arg)
{
	int *indice= (int *) arg;
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

void anyadir(int indice)
{
	int num=((rand()%4)+1);
	printf("Soy el productor %d y estoy colocando panes.\n", indice);
	sleep(num);
}
void extraer(int indice)
{
	int num=((rand()%4)+1);
	printf("Soy el consumidor %d y estoy cogiendo panes.\n", indice);
	sleep(num);

}