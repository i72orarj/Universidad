/**
 * 
 *   ojo: EJERCICIO SIN COMPROBACION DE ERRORES!!!!
 * 
 * 
 * PROBLEMA DE LOS LECTORES-ESCRITORES. PRIORIDAD LECTORES
 * 
 *   2 LECTORES Y 2 ESCRITORES
**/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define VECES 5  //Numero de veces que escriben y leen los escritores y los lectores

//Prototipos
void * escritor(void *);
void * lector(void *);
 
int dato = 5; /* recurso */ 
int n_lectores = 0; /* numero de lectores */ 
pthread_mutex_t mutex; /* controlar el acceso a dato */ 
pthread_mutex_t mutex_lectores; /* controla la variable n_lectores */

main(int argc, char *argv[]) 
{ 
pthread_t th1, th2, th3, th4; 

pthread_mutex_init(&mutex, NULL); 
//Mejorable con un for() y vector de hebras
pthread_create(&th1, NULL, (void *) lector, NULL); 
pthread_create(&th2, NULL, (void *) escritor, NULL); 
pthread_create(&th3, NULL, (void *) lector, NULL); 
pthread_create(&th4, NULL, (void *) escritor, NULL); 
//Mejorable con un for() y vector de hebras
pthread_join(th1, NULL); 
pthread_join(th2, NULL); 
pthread_join(th3, NULL); 
pthread_join(th4, NULL); 
pthread_mutex_destroy(&mutex); 
pthread_mutex_destroy(&mutex_lectores); 
exit(0); 
} 


void * escritor(void *argv) /* codigo del escritor */
{ 
int i;
for(i=0; i<VECES; i++)
{
   int aux;
	pthread_mutex_lock(&mutex); 
   aux = dato;
	dato = dato + 2; /* modificar el recurso */ 
	printf("Escritor %lu modificando dato %d->%d\n",(unsigned long int) pthread_self(),aux,dato);
	pthread_mutex_unlock(&mutex);
	usleep(random()%2000); 
}
pthread_exit(NULL); 
} 

void * lector(void *argv) /* codigo del lector */ 
{ 
int i;
for(i=0; i<VECES; i++)
{
	pthread_mutex_lock(&mutex_lectores); 
	n_lectores++; 
	if (n_lectores == 1) 
		pthread_mutex_lock(&mutex); 
	pthread_mutex_unlock(&mutex_lectores); 
	printf("Lector %lu leyedo dato: %d\n",(unsigned long int) pthread_self(), dato); /* leer dato */ 
	pthread_mutex_lock(&mutex_lectores); 
	n_lectores--; 
	if (n_lectores == 0) 
		pthread_mutex_unlock(&mutex); 
	pthread_mutex_unlock(&mutex_lectores); 
	usleep(random()%2000);
}
pthread_exit(NULL); 
}
