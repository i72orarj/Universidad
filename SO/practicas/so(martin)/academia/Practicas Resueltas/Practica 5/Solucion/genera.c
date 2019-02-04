#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>

#include "sim.h"



void *
GenerarProcesos (void *p)
{
  int j;
  extern int sclock, fclock, in;
  extern tPROC *bufer;
  tPROC nuevo;
  extern sem_t empty, full[N_PLAN];
  extern pthread_mutex_t mutex;
  
  in = 0;
  
  for (;;)
    {
      /* Generar proceso. */
      sleep (rand() % 3);
      
      nuevo.tservicio = rand() % M;
      nuevo.id = rand() & LAST_ID;
      nuevo.ftllegada = fclock;
      nuevo.stllegada = sclock;
      
      /* Añadir al búfer. */
      sem_wait (&empty);
      pthread_mutex_lock (&mutex);
      bufer[in] = nuevo;
      pthread_mutex_unlock (&mutex);
      for (j = 0; j < N_PLAN; j++)
        sem_post (&full[j]);
      
      in++;
    }
  
  
}
