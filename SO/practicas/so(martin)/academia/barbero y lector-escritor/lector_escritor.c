#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <errno.h>
#include <string.h>



void escribir();
void leer();
void *escritor();
void *lector();

sem_t x;
sem_t sescr;
int cuentalect=0;

void main()
{
	sem_init(&x, 0,1);
	sem_init(&sescr, 0, 1);
	pthread_t h_lector, h_escritor;

	pthread_create(&h_lector, NULL, (void *) lector);
	pthread_create(&h_escritor, NULL, (void *) escritor);

	pthread_join(h_lector, NULL);
	pthread_join(h_escritor, NULL);

}

void *lector()
{

	while(1)
	{
		sem_wait(&x);
		cuentalect++;
		if(cuentalect==1)
		{
			sem_wait(&sescr);
			
		}
		sem_post(&x);
		leer();
		sem_wait(&x);
		cuentalect--;
		if(cuentalect==0)
			sem_post(&sescr);
		sem_post(&x);
	}
}

void *escritor()
{

	while(1)
	{
		sem_wait(&sescr);
		sem_wait(&x);
		escribir();
		sem_post(&x);
		sem_post(&sescr);
	}
}

void leer()
{
	printf("Soy el lector y estoy leyendo\n");
	sleep(2);
}	

void escribir()
{
	printf("Soy el escritor y estoy escribiendo\n");
	sleep(2);
}	



















