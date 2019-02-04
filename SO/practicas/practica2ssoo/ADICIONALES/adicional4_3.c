/*Implemente un programa que genere N procesos hijos que comparten un vector de tamaño M. 
El programa principal inicializa el vector a 0 en todos sus valores antes de crear los hilos.

Cada hijo debe seleccionar aleatoriamente una posición del vector y sumarle 1. 
Esta operación la debe repetir 100 veces. 
Dado que el vector es compartido estamos ante un problema de sección crítica que debemos resolver usando semáforos POSIX.

Una vez finalizados todos los hilos el programa principal deberá sumar todos los elementos del vector para verificar que el resultado es correcto.*/

#include <semaphore.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define TAMANO 20
#define NHijos 3

void funcion(int i, sem_t * semaforo);

int main(){
									//obtencion de memoria para vector
	key_t clave;
	clave=ftok("adicional4_3.c", 1);

	int shmid;
	shmid=shmget(clave, TAMANO*sizeof(int), IPC_CREAT | 0777);
	if(shmid==-1){
		printf("error con la obtencion de memoria del padre (vector)\n");
		exit(-1);}

	int * vector;
	vector=(int *) shmat(shmid, NULL, 0);
	for(int i=0;i<TAMANO;i++)
		vector[i]=0;	
										//obtencion de memoria para semaforo comun

	key_t claveS;
	claveS=ftok("adicional4_2", 2);
	int shmidS=shmget(claveS, sizeof(sem_t), IPC_CREAT | 0777);
	if(shmid==-1){
		printf("error con la obtencion de memoria del padre(semaforo)\n");
		exit(-1);
	}

	sem_t * semaforo;
	semaforo=(sem_t *)shmat(shmidS, NULL, 0);

	sem_init(semaforo, 1, 1);
										//fin semaforo comun

										//llamada a hijos
	for(int i=0; i<NHijos;i++){			
		if(!fork()){
			funcion(i, semaforo);
			exit(0);
		}
	}
										//espera a hijos
	for(int i=0;i<NHijos;i++){
		int status;
		int pid=wait(&status);									//pasa algo por int pid != pid_t ?
		printf("El proceso con pid: %d finaliza con status: %d\n\n", pid, status);
	}	
										//comprobacion mantenimiento
	int sumatotal=0;
	for(int i=0;i<TAMANO;i++){
		sumatotal+=vector[i];
	}
	printf("El valor de suma total es %d y deberia ser: %d\n", sumatotal, NHijos*100);
}

void funcion(int valor, sem_t * semaforo){
									//reserva de memoria
	key_t clave;
	clave=ftok("adicional4_3.c", 1);

	int shmid;
	shmid=shmget(clave, TAMANO*sizeof(int), IPC_CREAT | 0777);
	if(shmid==-1){
		printf("error con la obtencion de memoria del padre (vector)\n");
		exit(-1);}

	int * vector;
	vector=(int *) shmat(shmid, NULL, 0);


	srand(time(NULL));
	int azar;
	for(int i=0;i<100;i++){
		azar=rand()%20;
		sem_wait(semaforo);
		int local=vector[azar];
		local++;
		vector[azar]=local;
		sem_post(semaforo);
		printf("El hilo %d ha aumentado la posicion %d del vector \n", valor, azar);
	}

	sem_close(semaforo);
	exit(0);
}