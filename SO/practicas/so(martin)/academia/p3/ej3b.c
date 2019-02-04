#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N 5
#define MAX_ITEMS 20

int cont=0;
int buffer[N];

pthread_mutex_t mutex= PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t lleno= PTHREAD_COND_INITIALIZER;
pthread_cond_t vacio= PTHREAD_COND_INITIALIZER;

void *fprod(void *arg);
void *fcons(void *arg);

main()
{
	pthread_t thd1, thd2;
	
	pthread_create(&thd1, NULL, (void *) fprod,NULL);	
	pthread_create(&thd2, NULL, (void *) fcons,NULL);	

	pthread_join(thd1, NULL);
	pthread_join(thd2, NULL);	

}

void *fprod(void *arg)
{

	srand(time(NULL));
	int n_items=0, item, pos_buffer=0;

	while(n_items <= MAX_ITEMS)
	{
		usleep(rand()%100000);
		pthread_mutex_lock(&mutex);

		if(cont==N)
		{
			pthread_cond_wait(&lleno, &mutex);

		}
		buffer[pos_buffer]=rand()%20;
		printf("P:En la posición %d escribo %d\n", pos_buffer, buffer[pos_buffer]);
		sleep(1);
		pos_buffer=(pos_buffer+1)%N;
		cont++;
		n_items++;
		pthread_cond_signal(&vacio);
		pthread_mutex_unlock(&mutex);
	}
	pthread_exit(NULL);
}

void *fcons(void *arg)
{
	srand(time (NULL));
	int n_items=0, item, pos_buffer=0;

	while(n_items<=MAX_ITEMS)
	{
		usleep(rand()%100000);
		pthread_mutex_lock(&mutex);
		if(cont==0)
		{
			pthread_cond_wait(&vacio, &mutex);
		}
		item=buffer[pos_buffer];
		printf("C: Leo de %d el valor %d\n", pos_buffer, item);
		sleep(1);
		pos_buffer=(pos_buffer+1)%N;
		cont--;
		n_items++;
		pthread_cond_signal(&lleno);
		pthread_mutex_unlock(&mutex);
	}
	pthread_exit(NULL);
}