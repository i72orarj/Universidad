/* Simulación del algoritmo fcfs. */
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <stdio.h>
#include "sim.h"

void *
fcfs (void *p)
{
  extern tPROC *bufer;
  extern tINFO *resul;
  tPROC actual;
  tINFO info;
  extern sem_t empty, full[N_PLAN], empty_info, full_info;
  extern pthread_mutex_t mutex, mut_info;
  extern int fclock, contador[N_PLAN], info_in;
  int out;
  
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
      printf ("T: %4d - FCFS: Planificado proceso %5d. Servicio: %4d Fin: %4d\n",
              fclock, actual.id, actual.tservicio, fclock +actual.tservicio);
      fclock += actual.tservicio;
      
      /* Informa al proceso de estadística. */
      info.tipo = algFCFS;
      info.tespera = fclock - actual.ftllegada - actual.tservicio;
      sem_wait (&empty_info);
      pthread_mutex_lock (&mut_info),      
      resul[info_in] = info;
      pthread_mutex_unlock (&mut_info);
      sem_post (&full_info);
      
      info_in++;
    } 
}
