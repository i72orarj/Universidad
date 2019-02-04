#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void * sumapar(void * parametro){

	int *id, i, *suma;

	suma = (int *)malloc(sizeof(int));
	*suma = 0;

	id = (int *)parametro;

	for(i=0 ; i<10 ; i++){
	
		if(i%2!=0){
			
			*suma = *suma + id[i];
			
		}

	}
	
pthread_exit((void *) suma);
}

void * sumaimpar(void * parametro){

int *id, i, *suma;

	suma = (int *)malloc(sizeof(int));
	*suma = 0;

	id = (int *)parametro;

	for(i=0 ; i<10 ; i++){
	
		if(i%2==0){
			
			*suma = *suma + id[i];
			
		}

	}
	
pthread_exit((void *) suma);

}

int main(int argc, char *argv[]){

	pthread_t hilos[2];

	int v[10], i;
	int *puntero_suma;

	for(i=0 ; i<10 ; i++){

		v[i]=i+1;
	}

	for(i=0 ; i<2 ; i++){

		if(i==0){		
	
			pthread_create(&hilos[i], NULL, (void *) sumapar, (void *) v);
		}else if(i==1){

			pthread_create(&hilos[i], NULL, (void *) sumaimpar, (void *) v);
		}
	}

	for(i=0 ; i<2 ; i++){

		pthread_join(hilos[i], (void **) &puntero_suma);

		printf("La suma de los pares vale: %d\n", *puntero_suma);
	}
	//printf("La suma de los pares vale: %d\n", atoi(puntero_suma));


return 0;
}


