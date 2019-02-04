#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#define HOMBRES 4
#define MUJERES 6

sem_t s_mutex_vacio, s_mutex_h, s_mutex_m, s_hombres, s_mujeres;

int m=0;
int h=0;

void * hombre(void * arg);
void * mujer(void * arg);

main()
{
	srand(time(NULL));
	int v[10], i;
	pthread_t hom[HOMBRES], muj[MUJERES];

	sem_init(&s_mutex_vacio,0, 1);
	sem_init(&s_mutex_h, 0, 1);
	sem_init(&s_mutex_m, 0, 1);
	sem_init(&s_hombres, 0, 3);
	sem_init(&s_mujeres, 0, 3);

	for(i=0;i<HOMBRES;i++)
	{
		v[i]=i;
		pthread_create(&hom[i], NULL, (void *) hombre, (void *) &v[i]);
	}
		for(i=0;i<MUJERES;i++)
	{
		v[i]=i;
		pthread_create(&muj[i], NULL, (void *) mujer, (void *) &v[i]);
	}

	for(i=0;i<HOMBRES;i++)
		pthread_join(hom[i], NULL);


	for(i=0;i<MUJERES;i++)
		pthread_join(muj[i], NULL);
}

void * hombre(void * arg)
{
	int *indice=(int *)arg;
	int num=(rand()%3)+1;
	while(1)
	{
		sleep(2);
		sem_wait(&s_hombres);
		sem_wait(&s_mutex_h);
		h++;
		if(h==1)
			sem_wait(&s_mutex_vacio);
		sem_post(&s_mutex_h);
			printf("Soy el hombre %d y estoy meando\n", *indice);
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


void * mujer(void * arg)
{
	int *indice=(int *)arg;
	int num=(rand()%3)+1;
	while(1)
	{
		sleep(2);
		sem_wait(&s_mujeres);
		sem_wait(&s_mutex_m);
		m++;
		if(m==1)
			sem_wait(&s_mutex_vacio);
		sem_post(&s_mutex_m);
			printf("Soy la mujer %d y estoy meando\n", *indice);
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
