#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
 
#define N 5
#define pensando 0
#define hambriento 1
#define comiendo 2
#define izq (id+4)%N  //(ph_num-1)%N
#define der (id+1)%N  //(ph_num+1)%N

sem_t mutex;
sem_t state[N];

int v[5];

void soltar_tenedores(int id);
void coger_tenedores(int id);
void test(int id);

void * filosofo(void * parametro){

	while(1){

	int *id;

	id = (int *)parametro;

	coger_tenedores(*id);
	sleep(2);

	soltar_tenedores(*id);
	sleep(2);
	}
}


void coger_tenedores(int id){

	sem_wait(&mutex);
	v[id]=hambriento;

	printf("\nEl filosofo %d esta hambriento.", id);

	test(id);
	sem_post(&mutex);
	sem_wait(&state[id]);


}


void soltar_tenedores(int id){

	sem_wait(&mutex);
	v[id]=pensando;

	test(izq);
	test(der);

	sem_post(&mutex);
}


void test(int id){

	if (v[id] == hambriento && v[izq] != comiendo && v[der] != comiendo){ //aqui se compararia en el caso de los tenedores en el medio de la mesa si la variable global es mayor que dos

		v[id] = comiendo;
		printf("\nEl filosofo %d esta comiendo", id);
		sem_post(&state[id]);
	}
}

int main(){

	int i;
	pthread_t hilos[N];

	sem_init(&mutex, 0, 1);

	for(i=0 ; i<N ; i++){

		sem_init(&state[i], 0, 0);

	}

	for(i=0 ; i<N ; i++){

		v[i]=i;
		pthread_create(&hilos[i], NULL, filosofo, (void *)&v[i]);

	}

	for(i=0 ; i<N ; i++){

		pthread_join(hilos[i], NULL);

	}





return 0;
}
