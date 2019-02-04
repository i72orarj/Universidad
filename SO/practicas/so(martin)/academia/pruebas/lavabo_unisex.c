#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 5
void *hombres(int *i);
void *mujeres(int *i);
int h=0, m=0;
sem_t s_mutex_vacio, s_mutex_h, s_mutex_m, s_hombres, s_mujeres;

int main()
{
	int i, v[N];
	pthread_t hom[N], muj[N];

	sem_init(&s_mutex_vacio, 0,1);
	sem_init(&s_mutex_h, 0,1);
	sem_init(&s_mutex_m, 0,1);
	sem_init(&s_hombres, 0,3);
	sem_init(&s_mujeres, 0,3);

	for(i=0;i<N;i++)
	{
		v[i]=i;
		pthread_create(&hom[i],NULL, (void *) hombres, (void *) &v[i]);
		pthread_create(&muj[i],NULL, (void *) mujeres, (void *) &v[i]);
	}

	for(i=0;i<N;i++)
	{
		pthread_join(hom[i], NULL);
		pthread_join(muj[i], NULL);
	}
}

void *hombres(int *i)
{
	while(1)
	{
		sleep(2);
		sem_wait(&s_hombres);
		sem_wait(&s_mutex_h);
		h++;
		if(h==1)
			sem_wait(&s_mutex_vacio);
		sem_post(&s_mutex_h);
		printf("Soy el hombre %d y estoy meando\n", *i);
		sleep(1);
		sem_wait(&s_mutex_h);
		h--;
		if(h==0)
		{
			puts("Ya no quedan hombres en el aseo.");
			sem_post(&s_mutex_vacio);
		}
		sleep(1);
		sem_post(&s_mutex_h);
		sem_post(&s_hombres);
	}
	pthread_exit(NULL);

}

void *mujeres(int *i)
{
	while(1)
	{
		sleep(2);
		sem_wait(&s_mujeres);
		sem_wait(&s_mutex_m);
		m++;
		if(m==1)
			sem_wait(&s_mutex_vacio);
		sem_post(&s_mutex_m);
		printf("Soy la mujer %d y estoy meando\n", *i);
		sleep(1);
		sem_wait(&s_mutex_m);
		m--;
		if(m==0)
		{
			puts("Ya no quedan mujeres en el aseo.");
			sem_post(&s_mutex_vacio);
		}
		sleep(1);
		sem_post(&s_mutex_m);
		sem_post(&s_mujeres);
	}
	pthread_exit(NULL);
	
}