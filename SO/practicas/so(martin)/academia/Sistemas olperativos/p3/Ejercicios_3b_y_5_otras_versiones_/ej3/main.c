#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include "funciones.h"

// Múltiples hilos Productores y Consumidores que actúan sobre posiciones aleatorias de un array

void main(int argc, char* argv[])
{
  if(argc != 2)
  {
    printf("Usage: %s N_HILOS\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  
  srand(time(NULL));
  
  int i,j;
  int nhilos = atoi(argv[1]);
  
  pthread_t* tid = (pthread_t*)malloc(2*nhilos*sizeof(pthread_t)); // Reservo 2 * NHILOS, worstcase: todos los hilos de son del mismo tipo en la misma posición.
  int* positions = (int*)malloc(nhilos*sizeof(int));
  int initialValue[DIM];
  int producers[DIM];
  int consumers[DIM];

  for(i = 0; i < DIM; i++)
  {
    pthread_mutex_init(&lock[i], NULL); // Iniciamos el mutex de cada posicion
    pthread_cond_init(&lleno[i], NULL); // Iniciamos la variable de condicion de cada posicion
    pthread_cond_init(&vacio[i], NULL); // Iniciamos la variable de condicion de cada posicion
    
    V[i] = initialValue[i] = minLimit + rand()%(maxLimit - minLimit); // Iniciamos el vector aleatoriamente
    producers[i] = consumers[i] = 0;    // Numero de productores y consumidores de cada posición
  }
  
  muestraVector(V, DIM);
  
  for(i = 0; i < nhilos; i++)
  {
    positions[i] = rand()%DIM;  // Random position
    
    if(rand()%2) // Random producer/consumer
    {
      producers[positions[i]]++;
      pthread_create(&tid[i], NULL, (void*)Productor, (void*)&positions[i]);  //Creamos un PRODUCTOR
    }
    else
    {
      consumers[positions[i]]++;
      pthread_create(&tid[i], NULL, (void*)Consumidor, (void*)&positions[i]); //Creamos un CONSUMIDOR
    }
  }

  sleep(1); // Wait threads to print messages
  printf("Revisando si es necesario crear más hilos para desbloquear otros hilos\n");
  fflush(stdout); 
  
  int nAuxThreads = 0; // Count auxiliary threads to unlock main threads
  int posIndex=0; // Position index
  
  for(i = 0; i < DIM; i++)
  {
    if(producers[i] > consumers[i]) // Higher number of producers than consumers for the position "i"
    {
      if(initialValue[i] + (producers[i] - consumers[i]) > maxLimit)
      {
         int nConsumers = initialValue[i] + (producers[i] - consumers[i]) - maxLimit; // Count how many to create based on array limits
         printf("Es necesario crear %d consumidores en la posición [%d]\n", nConsumers, i);
         positions[posIndex] = i;
         
         for(j = 0; j < nConsumers; j++)
           pthread_create(&tid[nhilos+nAuxThreads+j], NULL, (void*)Consumidor, (void*)&positions[posIndex]);
         
         nAuxThreads += nConsumers;
         posIndex++;
      }
    }
    else if(consumers[i] > producers[i]) // Higher number of consumers than producers for the position "i"
    {
      if(initialValue[i] - (consumers[i] - producers[i]) < minLimit)
      {
        int nProducers = minLimit - (initialValue[i] - (consumers[i] - producers[i])); // Count how many to create based on array limits
        printf("Es necesario crear %d productores en la posición [%d]\n", nProducers, i);
        positions[posIndex] = i;

        for(j = 0; j < nProducers; j++)
         pthread_create(&tid[nhilos+nAuxThreads+j], NULL, (void*)Productor, (void*)&positions[posIndex]);

        nAuxThreads += nProducers;
        posIndex++;
      }
    }
  }
  
  if(nAuxThreads == 0)
    printf("No ha sido necesario crear más hilos para garantizar la finalización del programa\n");

  for(i = 0; i < nhilos + nAuxThreads; i++) // Wait main and auxiliary threads to exit
    pthread_join(tid[i], NULL);
  
  printf("Final vector\n");
  muestraVector(V, DIM);
   
  for(i = 0; i < DIM; i++)
  {
    pthread_mutex_destroy(&lock[i]);
    pthread_cond_destroy(&lleno[i]);
    pthread_cond_destroy(&vacio[i]);
  }
  
  free(tid);
  free(positions);
}

