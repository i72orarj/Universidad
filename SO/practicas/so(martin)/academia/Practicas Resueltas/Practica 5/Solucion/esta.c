/* Obtención de los estadísticos descriptivos. */
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <stdio.h>
#include "sim.h"

void *
Estadisticas (void *p)
{
  extern sem_t empty_info, full_info;
  extern pthread_mutex_t mut_info;
  extern tINFO *resul;
  tINFO info;
  int out, n;
  double tmedioSJF = 0., tmedioFCFS = 0.;
  
  out = 0;
  
  for (n=1;;n++)
    {
      /* Obtiene el siguiente proceso planificado. */
      sem_wait (&full_info);
      pthread_mutex_lock (&mut_info),      
      info = resul[out];
      pthread_mutex_unlock (&mut_info);
      sem_post (&empty_info);
      
      out++;
      
      /* Presenta estadística actual. */
      if (info.tipo == algSJF)
        {
          tmedioSJF = ((tmedioSJF*(n-1))+info.tespera)/n;
	  printf ("SJF: Planificados %3d procesos. Tiempo medio de espera: %f\n", 
	          n, tmedioSJF);
	}
      else
        {
          tmedioFCFS = ((tmedioFCFS*(n-1))+info.tespera)/n;
	  printf ("FCFS: Planificados %3d procesos. Tiempo medio de espera: %f\n",
	          n, tmedioFCFS);
	}
    }
  

}
