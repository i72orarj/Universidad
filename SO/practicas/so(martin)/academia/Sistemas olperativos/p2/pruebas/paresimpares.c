#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

void * pares(void * parametro){

	int *n;

	n = (int *)parametro;

	int i;

	int *suma;

	suma = (int *)malloc(int);
	*suma=0;

	for(i=0 ; i<10 ; i++){

		if(n[i]%2==0){

			*suma = n[i] + *suma;
		}
	}
pthread_exit((void *) suma);
}


void * impares(void * parametro){




}


int main(){

	pthread_t hebras[2];

	
	int v[10];
	int i;

	int *puntero_pares, *puntero_impares;

	for(i=0, i<10 ; i++){
		
		v[i]=i+1;
	}

	
	pthread_create(&hebras[0], NULL, (void *)pares, (void *) v);

	pthread_join(hebras[0], (void **) &puntero_pares);

	pthread_create(&hebras[1], NULL, (void *)impares, (void *) v);
	
	pthread_join(hebras[1], (void **) &puntero_impares);


return 0;
}
