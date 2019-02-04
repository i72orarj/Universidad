#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>



void * imprime(void * parametro){


	int *id;

	id=(int *)parametro;

	printf("Hilo: %d \n", *id);

	pthread_exit(NULL);


}

int main(int argc, char **argv){

	pthread_t *hebras; //declaracion de hilos

	int tam, i;

	int *v;

	tam = atoi(argv[1]); //pasamos el numero de hilos a entero que viene por linea de ordenes 

	hebras = (pthread_t *)malloc(sizeof(pthread_t)*tam); //reservamos memoria para los hilos
	v = (int *)malloc(sizeof(int)*tam); //reservamos memoria para el vector que indicara el numero del hilo

	for(i=0 ; i<tam ; i++){
		v[i]=i+1; //aumenta el numero del hilo por el que vamos
		pthread_create(&hebras[i], NULL, (void *) imprime ,(void *) &v[i] ); //el ultimo argumento, para pasarle quien es el que hilo que soy

	}


	for(i=0 ; i<tam ; i++){

		pthread_join(hebras[i], NULL); //el join no devuelve nada por lo tanto es null

	}



return 0;
}


