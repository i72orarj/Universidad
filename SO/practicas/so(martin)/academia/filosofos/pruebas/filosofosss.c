#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#define N 4
#define IZQ(x) (((x)-1)%N)
#define DER(x) (((x)+1)%N)
// Pensando 0  Hambriento 1  Comiendo 2
void *filosofos(void *arg);

void pensar(int i);
void comer(int i);

void coger_tenedores(int i);
void prueba(int i);

void dejar_tenedores(int i);
int vector_estados[N];
sem_t exmut;
sem_t s[N];

main()
{
	srand(time(NULL));
	pthread_t thd[N];
	int i, v[N];
	sem_init(&exmut, 0, 1);
	for(i=0;i<N;i++)
	{
		sem_init(&s[i], 0, 0);
		vector_estados[i]=0;
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

void *filosofos(void *arg)
{
	int *indice=(int *)arg;
	while(1)
	{
		pensar(*indice);
		coger_tenedores(*indice);
		comer(*indice);
		dejar_tenedores(*indice);
	}
		pthread_exit(NULL);
}

void pensar(int i)
{
	int num=(rand()%3)+1;
	printf("Soy el filosofo %d y estoy pensando.\n", i);
	sleep(num);
}

void comer(int i)
{
	int num=(rand()%3)+1;
	printf("Soy el filosofo %d y estoy comiendo.\n", i);
	sleep(num);
}

void coger_tenedores(int i)
{
	sem_wait(&exmut);
	vector_estados[i]=1;
	prueba(i);
	sem_post(&exmut);
	sem_wait(&s[i]);
}

void prueba(int i)
{
	if(vector_estados[i]== 1 && vector_estados[IZQ(i)]!=2 && vector_estados[DER(i)]!=2)
	{
		vector_estados[i]=2;
		sem_post(&s[i]);
	}
}

void dejar_tenedores(int i)
{
	sem_wait(&exmut);
	vector_estados[i]=0;
	prueba(IZQ(i));
	prueba(DER(i));
	sem_post(&exmut);
}