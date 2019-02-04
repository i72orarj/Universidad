#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void * imprime(void * parametro){


	int *id;

	id = (int *)parametro;

	int *suma;

	suma = (int *)malloc(sizeof(int));

	*suma = *id + 3;

	printf("Hilo: %d la suma es %d\n", *id, *suma);


	pthread_exit((void *) suma);

}

int main(int argc, char **argv){

	pthread_t *hebras;

	int *v;
	int tam, i;
	void * puntero;

	tam = atoi(argv[1]);

	hebras = (pthread_t *)malloc(sizeof(pthread_t)*tam); 
	v = (int *)malloc(sizeof(int)*tam);

	for(i=0 ; i<tam ; i++){

		v[i]=i+1; 
		pthread_create(&hebras[i], NULL, (void *) imprime ,(void *) &v[i] );

	}

	for(i=0 ; i<tam ; i++){

		pthread_join(hebras[i], (void**) &puntero);

	}


return 0;
}
