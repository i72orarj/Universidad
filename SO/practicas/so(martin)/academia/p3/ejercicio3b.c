#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define  N  5
#define  MAX_ITEMS  20

int        buffer[N];
int        contador=0;

pthread_mutex_t mutex= PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  lleno= PTHREAD_COND_INITIALIZER;
pthread_cond_t  vacio= PTHREAD_COND_INITIALIZER;

void *func_prod(void *arg) {
    int item, pos_buffer=0;
    int num_items=0;
    
	srand(time(NULL));

    while (num_items<= MAX_ITEMS) 
    {
		usleep(rand()%100000);
		pthread_mutex_lock(&mutex);

		if (contador==N) {
        	pthread_cond_wait(&lleno, &mutex);//Como esta lleno, bloqueo a los consumidores.
    	}
		buffer[pos_buffer]= rand()%20;
		printf("P: Escribo en %d el valor = %d\n", pos_buffer, buffer[pos_buffer]);
		sleep(1);
		pos_buffer = (pos_buffer + 1) % N;
		contador= contador + 1;
		num_items++; 
     	pthread_cond_signal(&vacio);

		pthread_mutex_unlock(&mutex);
    }
    pthread_exit(0);
}


void *func_cons(void *arg) {
    int item, pos_buffer=0;
    int num_items=0;

	srand(time(NULL));
    
    while (num_items<= MAX_ITEMS) 
    {
		usleep(rand()%100000);
		pthread_mutex_lock(&mutex);

		if (contador==0) {
        	pthread_cond_wait(&vacio, &mutex);
    	}
		
		item= buffer[pos_buffer];
		printf("C: Leo de %d el valor %d\n", pos_buffer, item);
		sleep(1);
		pos_buffer = (pos_buffer + 1) % N;
		contador= contador - 1;
		num_items++;  
		pthread_cond_signal(&lleno);

		pthread_mutex_unlock(&mutex);
    }
    pthread_exit(0);
}


int main(void) {
    pthread_t hcons, hprod;
    
    pthread_create(&hprod, NULL,(void *) func_prod, NULL);
    pthread_create(&hcons, NULL,(void *) func_cons, NULL);
    pthread_join(hprod, NULL);
    pthread_join(hcons, NULL);
}
