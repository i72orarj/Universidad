/**********************************
Productor-consumidor utilizando
semáforos generales o con contador
**********************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <semaphore.h>
#include <pthread.h>
#define TAMBUF 5     // Tamaño del búfer circular
#define NUMDATOS 20  // Número de datos a enviar

//Prototipos
void * productor(void *);
void * consumidor(void *);

/* Semaforos generales para controlar los extremos,
es decir, si el productor puede producir porque tenga huecos
y que el consumidor pueda consumir porque haya items*/
sem_t hay_datos;
sem_t hay_sitio;

//Seccion crítica
int buffer[TAMBUF];

// Semaforo binario para proteger la sección crítica
pthread_mutex_t buffer_lock = PTHREAD_MUTEX_INITIALIZER;

main()
{
  pthread_t tidprod, tidcons;
  
	//Inicializacion de semaforos
  sem_init(&hay_datos, 0, 0);
  sem_init(&hay_sitio, 0, TAMBUF);
  //Completar control de errores
  //...

	//Se crean los hilos
  pthread_create(&tidprod, NULL, productor, NULL);
  pthread_create(&tidcons, NULL, consumidor, NULL);
  //Completar control de errores
  //...

  //Se espera a que los hilos terminen
  pthread_join(tidprod, NULL);
  pthread_join(tidcons, NULL);
  //Completar control de errores
  //...

	
  exit(EXIT_SUCCESS);
}

// Funciones productor-consumidor
void *productor(void *arg1)
{
  int i, bufin = 0;
  for (i = 0; i<NUMDATOS; i++) 
  {
		//¿Hay buffer libre para producir?
		sem_wait(&hay_sitio);
		//Seccion critica. Acceso al semáforo
		pthread_mutex_lock(&buffer_lock);
		//Produczco dato. Como ejemplo multiplos de 5
		buffer[bufin] = i*5;
		printf("Produciendo un %d en posicion %d\n",buffer[bufin],bufin);
		bufin = (bufin + 1) % TAMBUF;
		//Fin de secció crítica. Desbloqueo del semáforo
		pthread_mutex_unlock(&buffer_lock);
		//Indicación de que hay un item como mínimo a consumir
		sem_post(&hay_datos);
		//sleep(1);
  }

  pthread_exit( NULL );
}

void *consumidor(void *arg2)
{
	int i, midato;
   int bufout = 0;

	for (i = 0; i<NUMDATOS; i++) 
	{
		//¿Hay algo que consumir??
		sem_wait(&hay_datos);
		//Acceso a seccion crítica. Bloqueo del semaforo
		pthread_mutex_lock(&buffer_lock);
      midato = buffer[bufout];
		printf("Consumiendo un %d de la posicion %d\n",midato,bufout);
      bufout = (bufout + 1) % TAMBUF;
      //Finaliza seccion crítica. Desbloqueo del semaforo
      pthread_mutex_unlock(&buffer_lock);
		//Indicación de que al menos hay un hueco libre para producir.
		sem_post(&hay_sitio);
	   //sleep(1);
	}
	pthread_exit( NULL );
}
