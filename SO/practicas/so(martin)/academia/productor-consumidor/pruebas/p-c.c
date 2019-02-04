#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#define N 5

void *productor(void *arg);

void *consumidor(void *arg);
void extraer(int i);
void anyadir(int i);
sem_t s;
sem_t c;
sem_t n;


main()
{
	srand(time(NULL));
	pthread_t pro[N];
	pthread_t con[N];
	int i, v[N];

	sem_init(&s,0,1);
	sem_init(&c,0,N);
	sem_init(&n,0,0);

	for(i=0;i<N;i++)
	{
		v[i]=i;
		phtread_create(&pro[i], NULL, (void *) productor, (void *) &v[i]);
		phtread_create(&con[i], NULL, (void *) consumidor, (void *) &v[i]);
	}

	for(i=0;i<N;i++)
	{
		pthread_join(pro[i], NULL);
		pthread_join(con[i], NULL);

	}


}

void *productor(void *arg)
{
	while(1)
	{
		int *indice=(int *)arg;
	sem_wait(&c);
	sem_wait(&s);
	anyadir(*indice);
	sem_post(&s);
	sem_post(&n);
	pthread_exit(NULL);
}	
	}

void anyadir(int i)
{
	int num=(rand()%4)+1;
	printf("Soy el hilo %d y estoy colocando panes.\n", i);
	sleep(num);
}

void *consumidor(void *arg)
{
	while(1)
	{
		int *indice=(int *) arg;
	sem_wait(&n);
	sem_wait(&s);
	extraer(*indice);
	sem_post(&s);
	sem_post(&c);
	pthread_exit(NULL);
	}
	
}

void extraer(int i)
{
	int num=(rand()%4)+1;
	printf("Soy el hilo %d y estoy cogiendo panes.\n", i);
	sleep(num);
}