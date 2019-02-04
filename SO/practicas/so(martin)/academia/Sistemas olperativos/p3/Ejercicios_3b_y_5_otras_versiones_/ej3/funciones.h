#ifndef FUNCIONES_H
#define FUNCIONES_H

#define DIM 5
#define maxLimit 10
#define minLimit 0

pthread_mutex_t lock[DIM];
pthread_cond_t  lleno[DIM];
pthread_cond_t  vacio[DIM];

int V[DIM]; // Vector global que van a ir modificando los productores y los consumidores.

void* Productor(void* arg);
void* Consumidor(void* arg);
void  muestraVector(int* V, int n);

#define max(x, y) (((x) > (y)) ? (x) : (y))
#define min(x, y) (((x) < (y)) ? (x) : (y))

#endif
