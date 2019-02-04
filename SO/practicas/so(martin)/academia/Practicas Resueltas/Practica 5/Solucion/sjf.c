/* Simulación del algoritmo sjf. */
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <stdio.h>
#include "sim.h"

void *
sjf (void *p)
{
  extern tPROC *bufer;
  extern tINFO *resul;
  tPROC actual;
  tINFO info;
  extern sem_t empty, full[N_PLAN], empty_info, full_info;
  extern pthread_mutex_t mutex, mut_info;
  extern int sclock, contador[N_PLAN];
  int out;
  extern int info_in;
  
  out = info_in = 0;

  for (;;)
    {
      /* Obtiene el próximo proceso. */
      sem_wait (&full[FCFS]);
      pthread_mutex_lock (&mutex),      
      actual = bufer[out];
           
      if (++contador[out] == N_PLAN)
	{
	  contador[out] = 0;
	  sem_post (&empty);
	}
      pthread_mutex_unlock (&mutex);      
      
      out++;
      
      /* Planifica. */
      printf ("T: %4d - SJF: Planificado proceso %5d. Servicio: %4d Fin: %4d\n",
              sclock, actual.id, actual.tservicio, sclock +actual.tservicio);
      sclock += actual.tservicio;
      
      /* Informa al proceso de estadística. */
      info.tipo = algSJF;
      info.tespera = sclock - actual.stllegada - actual.tservicio;
      sem_wait (&empty_info);
      pthread_mutex_lock (&mut_info),      
      resul[info_in] = info;
      pthread_mutex_unlock (&mut_info);
      sem_post (&full_info);
      
      info_in++;
    } 
}
