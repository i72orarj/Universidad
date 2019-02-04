/*
   Soluci?n al problema del productor/consumidor en el cual cada ?tem es
   consumido por un consumidor en particular.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define N	10
#define ITER	100
#define C	3
#define FIN	-1

typedef struct
  {
    int c;
    int info;
  }
tBUFER;

tBUFER bufer[N];
int libre[N];

#define TRUE	1
#define FALSE	0

sem_t full[C], empty;
pthread_mutex_t ex_buf = PTHREAD_MUTEX_INITIALIZER;


int
main(void)
{
  int i;
  extern sem_t full[C], empty;
  extern int libre[N];
  pthread_t consumidor[C], productor;
  int v[C];
  void * Productor (void *), * Consumidor (void *);
  
  /* Inicializaci?n de sem?foros y variables globales. */
  sem_init (&empty, 0, N);
  for (i=0; i<N; i++)
    libre[i] = TRUE;
  for (i=0; i<C; i++)
    sem_init(&(full[i]), 0, 0);
    
  srandom (-time(NULL));
    
  /* Inicio de hilos. */
  pthread_create (&productor, 0, Productor, NULL);
  for (i=0; i<C; i++)
    {
      v[i] = i;
      pthread_create (&consumidor[i], 0, Consumidor, &v[i]);
    }
  
  /* Espera fin de hilos. */
  pthread_join (productor, NULL);
  for (i=0; i<C; i++)
    pthread_join (consumidor[i], NULL);
    
}

void *
Productor (void *p)
{
  int p_index = 0, item, i, suma[C], consumidor;
  extern sem_t full[C], empty;
  extern pthread_mutex_t ex_buf;
  extern tBUFER bufer[N];
  
  for (i=0; i<C; i++)
    suma[i] = 0;
  
  for (i=0; i<ITER; i++)
    {
      /* Produce item. */
      item = random()%100;
      consumidor = random() % C;
      suma[consumidor] += item;
      
      sem_wait (&empty);
      
      pthread_mutex_lock (&ex_buf);
      while (libre[p_index] == FALSE)
        p_index = (p_index + 1) % N;
      libre[p_index] = FALSE;
      bufer[p_index].info = item;
      bufer[p_index].c = consumidor;
      pthread_mutex_unlock (&ex_buf);
            
      sem_post (&full[consumidor]);      
            
      fprintf (stdout, "Pro: Item %d (%d)\n", item, consumidor);
    }
  
  
  /* Espera a vaciar el bufer por completo. */
  for (i=0; i<N; i++)
    sem_wait (&empty);
  
  /* Indica fin a los consumidores. */
  for (i=0; i<C; i++)
    {            
      pthread_mutex_lock (&ex_buf);
      while (libre[p_index] == FALSE)
        p_index = (p_index + 1) % N;
      libre[p_index] = FALSE;
      bufer[p_index].info = FIN;
      bufer[p_index].c = i;
      pthread_mutex_unlock (&ex_buf);
            
      sem_post (&full[i]); 
      
      if (N < C)
        sem_wait (&empty);
    } 
  
  fprintf (stdout, "Pro: Suma");
  for (i=0; i<C; i++)
    fprintf (stdout, "\t%d", suma[i]);
  fprintf (stdout, "\n");

}


void *
Consumidor (void *p)
{
  int c_index = 0, item, *index, suma = 0;
  extern sem_t full[C], empty;
  extern int libre[N];
  extern pthread_mutex_t ex_buf;
  extern tBUFER bufer[N];
  
  index = (int *) p;

  for (;;)
    {
      sem_wait (&full[*index]);
            
      pthread_mutex_lock (&ex_buf);
      while (bufer[c_index].c != *index ||
             libre[c_index] == TRUE)
        c_index = (c_index + 1) % N;  
         
      item = bufer[c_index].info;  
      
      libre[c_index] = TRUE;      
      pthread_mutex_unlock (&ex_buf);
                    	
      sem_post (&empty);     
      
      /* Comprueba si fin. */
      if (item == FIN)
        break;
      
      suma += item;    
            
      fprintf (stdout, "C%2d: Item %d\n", *index, item);
    }
    
  fprintf (stdout, "C%2d: Suma %d\n", *index, suma);
}
