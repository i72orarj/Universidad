#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <string.h>

#define PENSANDO 0
#define HAMBRIENTO 1
#define COMIENDO 2
#define IZQ(x) ((x-1)%N)
#define DER(x) ((x+1)%N)
#define N 5

void comer(int i);
void coger_tenedores(int i);
void dejar_tenedores(int i);
void prueba(int i);
void pensar(int i);
void *filosofos(int *i);

int estado[N];
sem_t mutex, s[N];

int main()
{
	int i, v[N], error;
	pthread_t thd[N];

	for(i=0;i<N;i++)
	{
		estado[i]=PENSANDO;
		sem_init(&s[i],0,PENSANDO);
	}
	sem_init(&mutex,0,1);

	for(i=0;i<N;i++)
	{
		v[i]=i;
		error =pthread_create(&thd[i], NULL, (void *) filosofos, (void *) &v[i]);
	}
	if(error==-1)
	{
		printf("message error pthread_create %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	for(i=0;i<N;i++)
	{
		pthread_join(thd[i],NULL);
	}
}

void *filosofos(int *i)
{
	while(1)
	{
		pensar(*i);
		coger_tenedores(*i);
		comer(*i);
		dejar_tenedores(*i);

	}
	pthread_exit(NULL);
}

void pensar(int i)
{
	printf("Soy el filosofo %d y estoy PENSANDO\n", i);
	sleep((rand()%3)+1);
}

void comer(int i)
{
	printf("Soy el filosofo %d y estoy COMIENDO\n", i);
	sleep((rand()%3)+1);
}

void coger_tenedores(int i)
{
	sem_wait(&mutex);
	estado[i]=HAMBRIENTO;
	prueba(i);
	sem_post(&mutex);
	sem_wait(&s[i]);
}

void dejar_tenedores(int i)
{
	sem_wait(&mutex);
	estado[i]=PENSANDO;
	prueba(IZQ(i));
	prueba(DER(i));
	sem_post(&mutex);
}

void prueba(int i)
{
	if(estado[i]==HAMBRIENTO && estado[IZQ(i)]!= COMIENDO && estado[DER(i)]!=COMIENDO)
	{
		estado[i]=COMIENDO;
		sem_post(&s[i]);
	}
}