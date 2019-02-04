#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

#define N 5
void *productor(int *indice);
void *consumidor(int *indice);
void sum_prod(int i);
void sum_cons(int i);

sem_t e, n, s;


main()
{
	srand(time(NULL));
	pthread_t prod[N], cons[N];
	int v[N], i;
	int *num1, *num2;
	sem_init(&e,0,N);
	sem_init(&s,0,1);
	sem_init(&n,0,0);

	for(i=0;i<N;i++)
	{
		v[i]=i;
		pthread_create(&prod[i], NULL, (void *) productor, (void *) &v[i]);
		pthread_create(&cons[i], NULL, (void *) consumidor, (void *) &v[i]);
	}

	for(i=0;i<N;i++)
	{
		pthread_join(prod[i],NULL);
		pthread_join(cons[i],NULL);

	}




}

void *productor(int *indice)
{
	int i;

	for(i=0;i<10;i++)
	{
		
		sem_wait(&e);
		sem_wait(&s);
		sum_prod(*indice);
		sem_post(&s);
		sem_post(&n);

	}
			
	pthread_exit(NULL);
}

void *consumidor(int *indice)
{
	int i;


	for(i=0;i<10;i++)
	{
		
		sem_wait(&n);
		sem_wait(&s);
		sum_cons(*indice);
		sem_post(&s);
		sem_post(&e);
	
	}
	pthread_exit(NULL);
}

void sum_prod(int i)
{
	int suma1=0;
	int num1;
	num1=rand()%10;
	suma1+=num1;
	printf("Soy el consumidor %d y quito panes y mi suma es %d\n", i, suma1);
	sleep(1);
}
void sum_cons(int i)
{
	int suma2=0;
	int num2;
	num2=rand()%10;
	suma2+=num2;
	printf("Soy el productor %d y añado panes y mi suma es %d\n", i, suma2);
	sleep(1);
}