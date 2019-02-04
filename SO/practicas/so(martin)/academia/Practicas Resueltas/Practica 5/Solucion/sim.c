/* Programa principal. */
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <time.h>
#include "sim.h"

/* Variables globales. */
int sclock, fclock, in, contador[N_PLAN], info_in;
tPROC *bufer;
tINFO *resul;
sem_t empty, full[N_PLAN], empty_info, full_info;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER,
                mut_info = PTHREAD_MUTEX_INITIALIZER;

int
main ()
{
  pthread_attr_t atributos;
  pthread_t generador, sjf_id, fcfs_id, esta;
  int status, i;
  
  /* Inicializa variables globales. */  
  pthread_attr_init (&atributos);
  sclock = fclock = 0;
  info_in = 0;
  for (i=0; i<N_PLAN; i++)
    {
      sem_init (&full[i], 0, 0);
      contador[i] = 0;
    }
  sem_init (&empty, 0, N);
  sem_init (&full_info, 0, 0);
  sem_init (&empty_info, 0, N);
  
  if ((bufer = malloc (sizeof(tPROC)*N))== NULL)
    exit (1);
  if ((resul = malloc (sizeof(tINFO)*N))== NULL)
    exit (1);
    
  /* Inicia simulador de procesos. */
  if ((status = pthread_create (&generador, &atributos, GenerarProcesos,
       NULL)))
    exit (status);
    
  /* Inicializa planificadores. */
  if ((status = pthread_create (&fcfs_id, &atributos, fcfs, NULL)))
    exit (status);
  if ((status = pthread_create (&sjf_id, &atributos, sjf, NULL)))
    exit (status);    

  /* Inicializa estadísticas. */
  if ((status = pthread_create (&esta, &atributos, Estadisticas, NULL)))
    exit (status);
  
  /* Espera el fin de los hilos. */
  pthread_join (generador, NULL);
  pthread_join (fcfs_id, NULL);
  pthread_join (sjf_id, NULL);
  
  return (1);
  
}
