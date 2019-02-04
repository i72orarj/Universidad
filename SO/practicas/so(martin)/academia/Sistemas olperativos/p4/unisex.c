/*
Práctica 4 - Ejercicio 2
Julio Domingo Jiménez Ledesma

Problema del baño unisex dando preferencia al sexo que ya se encuentre dentro.
En caso de, por ejemplo, haber dos mujeres dentro y estar primero en cola un hombre, no entrará otra mujer hasta que no
haya pasado el hombre antes.

Esto se consigue de manera similar a un problema de escritores y lectores donde el servicio es el buffer compartido con
un límite de lectores en él y dos grupos de lectores diferentes (hombres y mujeres) que no pueden coincidir en el 
acceso al buffer. No habría ningún escritor.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h> //include para semaforos
#include <unistd.h> 

#define CAPACIDAD 3 /*Máximo de personas que pueden entrar en el servicio*/
#define HILOS 10 //Tamaño de la cola. Tendrá el mismo número de hombres y de mujeres.

void* hombre(void* id); //Función para los hilos de hombres
void* mujer(void* id); //Función para los hilos de mujeres

void checkError(int f, char msg[200]); //Comprueba si hay fallos en las funciones POSIX
void checkNULL(int* f, char msg[200]); //Comprueba si hay fallos en las reservas de memoria


//se declaran globales tipo es sem_t
sem_t empty; //Semáforo para indicar que el servicio está vacío. Inicializado a 1
sem_t male; //Sección crítica para los hilos de hombres. Inicializado a 1 para bloquear un solo hombre que pase al baño, dos hombres o mujeres no pueden entrar al baño
sem_t female; //Sección crítica para los hilos de mujeres. Inicializado a 1 
sem_t male_count; //Cantidad de hombres que podrían entrar al servicio. Inicializado a CAPACIDAD para cuando incremente o decremente las variables esten bloqueados
sem_t female_count; //Cantidad de mujeres que podrían entrar servicio. Inicializado a CAPACIDAD sirve para que solo un hombre o una mujer entre al baño
sem_t turnstile; //Indica si es el turno de hombres o mujeres para entrar en el baño. Inicializado a 1

int mcount = 0; //Número de hombres dentro del servicio
int fcount = 0; //Número de mujeres dentro del servicio

////////////////
//FUNCIÓN MAIN//
////////////////

int main()
{
  pthread_t *thr_cola = NULL;
  int *vectorID = NULL;
  int i, cola = 2*HILOS;
 
  srand(time(0));
  
  //Reservando memoria para vectores
  checkNULL(vectorID = (int*)calloc(cola, sizeof(int)), "Error al reservar memoria de vectorID. Saliendo");
  checkNULL((int*)(thr_cola = (pthread_t*)calloc(cola, sizeof(pthread_t))), "Error al reservar memoria para thr_cola. Saliendo");
  
  //Inicializando semáforos.
  checkError(sem_init(&empty, 0, 1), "Error al inicializar empty. Saliendo."); //quitando lo de los errores seria: sem_init(&empty, 0, 1);
  checkError(sem_init(&male, 0, 1), "Error al inicializar male. Saliendo."); //para iniciarlizar semaforos sem_init, el nombre, siempre 0 y despues hasta donde llega
  checkError(sem_init(&female, 0, 1), "Error al inicializar female. Saliendo.");
  checkError(sem_init(&male_count, 0, CAPACIDAD), "Error al inicializar male_count. Saliendo.");
  checkError(sem_init(&female_count, 0, CAPACIDAD), "Error al inicializar female_count. Saliendo.");
  checkError(sem_init(&turnstile, 0, 1), "Error al inicializar turnstile. Saliendo.");

  //Lanzando hilos
  for(i = 0; i < cola; i++)
  {
    vectorID[i] = i;
    if(i%2 == 0)
      checkError(pthread_create(&thr_cola[i], NULL, hombre, (void*)&vectorID[i]), "Error al crear hilo de hombres");
    else
      checkError(pthread_create(&thr_cola[i], NULL, mujer, (void*)&vectorID[i]), "Error al crear hilo de mujeres");
  }
  
  //Esperando hilos
  for(i = 0; i < cola; i++)
  {
    checkError(pthread_join(thr_cola[i], NULL), "Error de join. Saliendo.");
  }
  
  //Destruyendo semáforos
  checkError(sem_destroy(&empty), "Error al destruir empty. Saliendo.");
  checkError(sem_destroy(&male), "Error al destruir male. Saliendo.");
  checkError(sem_destroy(&female), "Error al destruir female. Saliendo.");
  checkError(sem_destroy(&male_count), "Error al destruir male_count. Saliendo.");
  checkError(sem_destroy(&female_count), "Error al destruir female_count. Saliendo.");
  checkError(sem_destroy(&turnstile), "Error al destruir turnstile. Saliendo.");
  
  //Liberando memoria
  free(vectorID);
  free(thr_cola);
  
  printf("Final del programa.\n");
  exit(EXIT_SUCCESS);
}


////////////////////////
//FUNCIONES PARA HILOS//
////////////////////////

void* hombre(void* id)
{
  int myID = *(int*)id;
 
  /* Este semáforo permite que las personas vayan entrando en el baño por orden de llegada. Es común 
  a los hilos hombre y mujer */
  sem_wait(&turnstile); 
  /*Este printf() antes de sem_wait(&turnstile) puede dar lugar a que las salidas refrejen que se "cuelan" individuos.*/
  printf("HOMBRE %d en cola.\n", myID); 
  sem_wait(&male); //Protege la actualización del contador de hombre
  mcount++;
  if(mcount == 1)
    //Si hay una mujer dentro del baño, éste hilo se quedará bloqueado aquí. Esto impedirá que este hilo ejecute 
    //el siguiente sem_post(&turnstile) impidiendo que este hilo no pueda entrar en el baño hasta que se vacie, 
    //además de impedir que nadie se le "cuele", ya que el paso al siguiente hilo en cola lo dará el sem_post(&turnstile)
    //que este hilo invocará en un futuro. ¿Cuándo? Cuando la última mujer salga del baño y haga un sem_post(&empty).
    sem_wait(&empty);
  sem_post(&male);
  /*Permite que otro hilo trate de entrar en el baño en orden de llegada. El que pueda entrar o no depende de si hay gente
   del sexo opuesto dentro o si el baño tiene ya tres personas dentro del mismo sexo*/
  sem_post(&turnstile);

  sem_wait(&male_count); //Maximo de tres hilos de este tipo
  printf("HOMBRE %d dentro del baño.\n", myID);
  usleep(rand()%500000); //Aleatorio entre 0 y 0.5 segundos
  sem_post(&male_count);

  sem_wait(&male);
  mcount--;
  printf("HOMBRE %d ha salido del baño.\n", myID);
  if(mcount == 0)
    //Marca el baño como vacío y desbloquearía un hilo del otro sexo que hubiera quedado bloqueado en su sem_wait(&empty);
    sem_post(&empty);
  sem_post(&male);

  pthread_exit(NULL);
}

void* mujer(void* id)
{
  int myID = *(int*)id; //hacemos el casting

  sem_wait(&turnstile);
  printf("MUJER %d en cola.\n", myID);
  sem_wait(&female);
  fcount++;
  if(fcount == 1)
    sem_wait(&empty);
  sem_post(&female);
  sem_post(&turnstile);

  sem_wait(&female_count);
  printf("MUJER %d dentro del baño.\n", myID);
  usleep(rand()%500000); //Aleatorio entre 0 y 0.5 segundos
  sem_post(&female_count);

  sem_wait(&female);
  fcount--;
  printf("MUJER %d ha salido del baño.\n", myID);
  if(fcount == 0)
    sem_post(&empty);
  sem_post(&female);

  pthread_exit(NULL);
}


////////////////////////
//FUNCIONES AUXILIARES//
////////////////////////
void checkError(int f, char msg[200])
{
  if(f != 0)
  {
    puts(msg);
    exit(EXIT_FAILURE);
  }
}

void checkNULL(int* f, char msg[200])
{
  if(f == NULL)
  {
    puts(msg);
    exit(EXIT_FAILURE);
  }
}
