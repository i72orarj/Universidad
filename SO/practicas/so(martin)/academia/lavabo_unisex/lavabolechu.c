#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

#define CAPACIDAD 3
#define N 5

sem_t mutexm, mutexh, vacio, s_hombre, s_mujer;

void *Hombres(int *id)
{
int h=0;
	sem_wait(&s_hombre);
	sem_wait(&mutexh);
	h++;
	if(h==1)
		sem_wait(&vacio);
	sem_post(&mutexh);
	printf("Hombre %d en el lavabo\n", *id);
	sleep(3);
	sem_wait(&mutexh);
	printf("Hombre %d sale del lavabo\n", *id);
	h--;
	if(h==0)
		sem_post(&vacio);
	sem_post(&mutexh);
	sem_post(&s_hombre);
}

void *Mujeres(int *id)
{
int m=0;
	sem_wait(&s_mujer);
	sem_wait(&mutexm);
	m++;
	if(m==1)
		sem_wait(&vacio);
	sem_post(&mutexm);
	printf("Mujer %d en el lavabo\n", *id);
	sleep(3);
	sem_wait(&mutexm);
	printf("Mujer %d sale del lavabo\n", *id);
	m--;
	if(m==0)
		sem_post(&vacio);
	sem_post(&mutexm);
	sem_post(&s_mujer);
}


int main()
{
int i, vh[N], vm[N];
pthread_t hiloshombres[N], hilosmujeres[N];


	sem_init(&mutexm,0,1);
	sem_init(&mutexh,0,1);
	sem_init(&vacio,0,1);
	sem_init(&s_hombre,0,CAPACIDAD);
	sem_init(&s_mujer,0,CAPACIDAD);

	for(i=0; i<N; i++)
	{
		vh[i]=i+1;
		vm[i]=i+1;

		pthread_create(&hiloshombres[i],NULL,(void *)Hombres, (void *) &vh[i]);
		pthread_create(&hilosmujeres[i],NULL,(void *)Mujeres, (void *) &vm[i]);
	}

	for(i=0; i<N; i++)
	{
		pthread_join(hiloshombres[i],NULL);
		pthread_join(hilosmujeres[i],NULL);
	}

	exit(EXIT_SUCCESS);

return 0;
}
