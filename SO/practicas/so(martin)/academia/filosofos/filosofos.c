#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#define N 5
#define IZQ(x) (((x)-1)%N)
#define DER(x) (((x)+1)%N)
// Pensando 0    Hambriento 1      Comiendo 2

void * filosofos(void * arg);
void comer(int indice);
void pensar(int indice);
void coger_tenedores(int indice);
void dejar_tenedores(int indice);
void prueba(int indice);

sem_t s[N];
sem_t mutex;
int vector_estados[N];


main()
{
	srand(time(NULL));
	int i, v[N];
	pthread_t thd[N];
	for(i=0;i<N;i++)
	{
	sem_init(&s[i], 0, 0);
	vector_estados[i]=0;
	}
	sem_init(&mutex, 0 , 1);

	
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

void * filosofos(void * arg)
{
	int *indice=(int *) arg;
	while(1)
	{
	pensar(*indice);
	coger_tenedores(*indice);
	comer(*indice);	
	dejar_tenedores(*indice);

	}


	pthread_exit(NULL);
}

void comer(int indice)
{
	int num=((rand()%3)+1);
	printf("Soy el filosofo %d y estoy comiendo.\n", indice);
	sleep(num);
}

void pensar(int indice)
{
	int num=((rand()%3)+1);
	printf("Soy el filosofo %d y estoy pensando.\n", indice);
	sleep(num);
}

void coger_tenedores(int indice)
{
	
	sem_wait(&mutex);
	vector_estados[indice]=1;
	prueba(indice);
	sem_post(&mutex);
	sem_wait(&s[indice]);
}

void dejar_tenedores(int indice)
{
	sem_wait(&mutex);
	vector_estados[indice]=0;
	prueba(IZQ(indice));
	prueba(DER(indice));
	sem_post(&mutex);
}

void prueba(int indice)
{
	if(vector_estados[indice]== 1 && vector_estados[IZQ(indice)]!= 2 && vector_estados[DER(indice)]!= 2)
	{
		vector_estados[indice]=2;
		sem_post(&s[indice]);
	}
}