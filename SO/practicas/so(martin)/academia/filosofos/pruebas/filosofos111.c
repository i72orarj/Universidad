#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

// Pensando 0  Hambriento 1  Comiendo 2
#define N 5
#define IZQ(x) (((x)-1)%N)
#define DER(x) (((x)+1)%N)
void *filosofos(int *i);
void pensar(int i);
void comer(int i);
void coger_tenedores(int i);
void dejar_tenedores(int i);
void prueba(int i);
sem_t s[N], mutex;
int estados[N];

main()
{
	pthread_t thd[N];
	int v[N], i;
	
	sem_init(&mutex,0,1);
	for(i=0;i<N;i++)
	{
		sem_init(&s[i], 0, 0);
		estados[i]=0;
	}

	for(i=0;i<N;i++)
	{
		v[i]=i;
		pthread_create(&thd[i], NULL, (void *) filosofos, (void *) &v[i]);
	}

	for(i=0;i<N;i++)
	{
		pthread_join(thd[i], NULL);
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
	printf("Soy el filosofo %d y estoy pensando\n", i);
	sleep(1);
}


void comer(int i)
{
	printf("Soy el filosofo %d y estoy comiendo\n", i);
	sleep(2);
}

void coger_tenedores(int i)
{
	
	
	sem_wait(&mutex);
	estados[i]=1;
	prueba(i);
	sem_post(&mutex);
	sem_wait(&s[i]);
	

}

void dejar_tenedores(int i)
{
	
	
		sem_wait(&mutex);
		estados[i]=0;
		prueba(IZQ(i));
		prueba(DER(i));
		sem_post(&mutex);
	
}

void prueba(int i)
{
	if(estados[i]==1 && estados[IZQ(i)]!=2 && estados[DER(i)]!=2)
	{
		estados[i]=2;
		sem_post(&s[i]);
	}
}