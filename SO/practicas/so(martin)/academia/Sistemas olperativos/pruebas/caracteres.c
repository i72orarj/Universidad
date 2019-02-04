#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

#define N 4

sem_t mutex;

void * caracter(void * parametro){

	int *id, i;

	id = (int *)parametro;

	char car;

	if(*id==0){

		car='+';
		

	}else if(*id==1){

		car='-';
	
	}else if(*id==2){

		car='*';
		
	}else if(*id==3){

		car='/';
		
	}

	sem_wait(&mutex);
	

	for(i=0 ; i<5 ; i++){

		printf("%c", car);
		sleep(1);
	}
	
	sem_post(&mutex);
}

int main(){



	pthread_t hilos[N];
	int v[4];

	int i;

	sem_init(&mutex, 0, 1);

	for(i=0 ; i<N ; i++){
		
		v[i]=i;
		pthread_create(&hilos[i], NULL, caracter, (void *) &v[i]);
	}

	sem_wait(&mutex);
	for(i=0 ; i<5 ; i++){

		printf("%c", '#');
		sleep(1);
	}
	sem_post(&mutex);	

	for(i=0 ; i<N ; i++){

		pthread_join(hilos[i], NULL);

	}
	printf("\n");

	sem_destroy(&mutex);






return 0;
}
