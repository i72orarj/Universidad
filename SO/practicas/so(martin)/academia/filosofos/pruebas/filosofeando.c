#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>

void *principal(void *arg);
void pensar(int i);
void comer(int i);
void coger_tenedores(int i);
void dejar_tenedores(int i);
void prueba(int i);

#define IZQ(x) ((x)-1)%N
#define DER(x) ((x)+1)%N
#define N 5
#define HAMBRIENTO 1
#define PENSANDO 0
#define COMIENDO 2



sem_t mutex, s[N];
int estado[N];

main()
{
	srand(time(NULL));
	int i, v[N];
	pthread_t thd[N];
	sem_init(&mutex,0,1);

	for(i=0;i <N; i++)
	{	
		sem_init(&s[i], 0, PENSANDO);
		estado[i]=PENSANDO;
		v[i]=i;
		pthread_create(&thd[i], NULL, (void *) principal, (void *) &v[i]);
	}

	for(i=0;i<N;i++)
	{
		pthread_join(thd[i], NULL);
	}
}

void *principal(void *arg)
{
	int *i=(int *)arg;
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
	sleep(rand()%N);
}

void comer(int i)
{
	printf("Soy el filosofo %d y estoy comiendo\n", i);
	sleep(rand()%N);	
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
	if(estado[i]== HAMBRIENTO && estado[IZQ(i)]!=COMIENDO && estado[DER(i)]!=COMIENDO)
	{
		estado[i]=COMIENDO;
		sem_post(&s[i]);
	}
}