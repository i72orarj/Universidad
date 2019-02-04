#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>

/* Soluci?n al problema de los fumadores. */

typedef enum
{
  TABACO, CERILLAS, PAPEL, FIN
}
producto_T;


#define CICLOS	100

producto_T producto;

pthread_mutex_t fumadores[3] = PTHREAD_MUTEX_INITIALIZER, productor =
  PTHREAD_MUTEX_INITIALIZER;



main ()
{

  pthread_t prod, fum[3];
  void *Productor (void *), *Fumador (void *);
  int i, v[3];
  extern pthread_mutex_t fumadores[3], productor;

  srand (-time (NULL));

  /* Bloquea a los fumadores. */
  for (i = 0; i < 3; i++)
    pthread_mutex_lock (&fumadores[i]);

  if (pthread_create (&prod, NULL, Productor, NULL))
    exit (1);
  for (i = 0; i < 3; i++)
    {
      v[i] = i;
      if (pthread_create (&fum[i], NULL, Fumador, &v[i]))
	exit (1);
    }

  pthread_join (prod, NULL);
  for (i = 0; i < 3; i++)
    pthread_join (fum[i], NULL);
}


void *
Productor (void *p)
{
  extern producto_T producto;
  int i;
  extern pthread_mutex_t fumadores[3], productor;


  for (i = 0; i < CICLOS; i++)
    {

      /* Espera para producir. */
      pthread_mutex_lock (&productor);

      /* Produce producto. */
      producto = rand () % 3;

      /* Despierta al fumador que puede fumar. */
      pthread_mutex_unlock (&fumadores[producto]);

    }

  /* Espera para producir el fin. */
  pthread_mutex_lock (&productor);

  /* Finaliza a los fumadores. */
  producto = FIN;
  for (i = 0; i < 3; i++)
    pthread_mutex_unlock (&fumadores[i]);

  fprintf (stdout, "Fin productor\n");

}

void *
Fumador (void *p)
{
  extern pthread_mutex_t fumadores[3], productor;
  extern producto_T producto;
  int *index, cigarros = 0;

  index = (int *) p;

  for (;;)
    {
      /* Espera a ser despertado. */
      pthread_mutex_lock (&fumadores[*index]);

      /* Comprueba si final. */
      if (producto == FIN)
	break;
      else
	{
	  /* Fuma. */
	  fprintf (stdout, "Fumador %d\n", *index);
	  cigarros++;
	}

      /* Despierta al productor. */
      pthread_mutex_unlock (&productor);
    }

  fprintf (stdout, "Fin fumador %d (%d cigarros)\n", *index, cigarros);
}
