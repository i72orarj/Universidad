#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include "funciones.h"

void* Productor(void* arg)
{
  int wasBlocked = 0;
  int pos = *(int*)arg;
  
  pthread_mutex_lock(&lock[pos]); //Entrada en la sección crítica.

  while(V[pos] == maxLimit)
  {
    wasBlocked = 1; // for cool printf purposes
    printf("Productor \t \e[1;31mbloqueado\033[0m \t posición [%d]\n", pos);
    pthread_cond_wait(&lleno[pos], &lock[pos]); //Si está lleno nos bloqueamos esperando a que algún consumidor actúe y liberamos el lock de dicha posición.
  }
  
  if(wasBlocked)
    printf("Productor \t \e[1;32mdesbloqueado\033[0m \t posición [%d]\n", pos);
    
  printf("Productor \t incrementa \t posición [%d]\n", pos);
  
  V[pos]++;
  
  pthread_cond_signal(&vacio[pos]); //Al haber incrementado la posicion del vector, desbloqueamos a un hipotético consumidor en espera de dicha posición.
  
  pthread_mutex_unlock(&lock[pos]); //Salida de la sección crítica.

  pthread_exit(NULL);  
}

void* Consumidor(void* arg)
{
  int wasBlocked = 0;
  int pos = *(int*)arg;
  
  pthread_mutex_lock(&lock[pos]); //Entrada en la sección crítica.  

  while(V[pos] == minLimit)
  {
    wasBlocked = 1; // for cool printf purposes
    printf("Consumidor \t \e[1;31mbloqueado\033[0m \t posición [%d]\n", pos);
    pthread_cond_wait(&vacio[pos], &lock[pos]); //Si está vacío nos bloqueamos esperando a que algún productor actúe y liberamos el lock de dicha posición.
  }
  
  if(wasBlocked)
    printf("Consumidor \t \e[1;32mdesbloqueado\033[0m \t posición [%d]\n", pos);
    
  printf("Consumidor \t decrementa \t posición [%d]\n", pos);
  
  V[pos]--;
  
  pthread_cond_signal(&lleno[pos]); //Al haber decrementado la posicion del vector, desbloqueamos a un hipotético productor en espera de dicha posición.
  
  pthread_mutex_unlock(&lock[pos]); //Salida de la sección crítica.
  
  pthread_exit(NULL);
}

void muestraVector(int* V, int length)
{
  int i;
  
  for(i = 0; i < length; i++)
    printf("%d\t", V[i]);
  printf("\n");
}
