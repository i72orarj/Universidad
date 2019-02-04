/*2.los procesos a diferencia de los hilos, no comparten el mismo
espacio de memoria, por lo que si queremos que accedan a las mismas variables en memoria, estos
deben compartirla.
 Realice un programa que expanda N procesos hijos. 
 Cada hijo debe compartir una variable denominada contador, que debe estar inicializada a cero.  
 Esta variable debe ser incrementada por cada hilo 100 veces. 
 Imprima la variable una vez finalicen los hilos y analice el resultado obtenido. 
 Un resultado previsible para 3 procesos sería 300, ¿ha sido así?

Implemente el ejercicio usando semáforos POSIX para proteger la exclusión mutua de la variable contador.*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <semaphore.h>


#define NProcesos 3

void incrementa(int i, sem_t * semaforo);

int main(){

	key_t clave;
	clave=ftok("adicional4_2.c", 1);

	int shmid;
	shmid=shmget(clave, sizeof(int), IPC_CREAT | 0777);
	if(shmid==-1){
		printf("error con la obtencion de memoria del padre\n");
		exit(-1);}

	int * contador;
	contador=(int *) shmat(shmid, NULL, 0);
	*contador=0;

	//semaforo comun

	key_t claveS;
	claveS=ftok("adicional4_2", 2);
	int shmidS=shmget(claveS, sizeof(sem_t), IPC_CREAT | 0777);
	if(shmid==-1){
		printf("error con la obtencion de memoria del padre\n");
		exit(-1);
	}

	sem_t * semaforo;
	semaforo=(sem_t *)shmat(shmidS, NULL, 0);

	sem_init(semaforo, 1, 1);

	//fin semaforo comun

	for(int i=0; i<NProcesos;i++){			
		if(!fork()){
			incrementa(i, semaforo);
			exit(0);
		}
	}

	for(int i=0;i<NProcesos;i++){
		int status;
		int pid=wait(&status);					//pasa algo por int pid != pid_t ?
		printf("El proceso con pid: %d finaliza con status: %d\n\n", pid, status);
	}

	printf("El contador toma como valor final: %d\n", *contador);

	shmdt(contador);
	shmctl(shmid, IPC_RMID, NULL);
	return 0;
} 

void incrementa(int i, sem_t * semaforo){
//memoria compartida contador
	key_t clave;
	clave=ftok("adicional4_2.c", 1);

	int shmid;
	shmid=shmget(clave, sizeof(int), IPC_CREAT | 0777);
	if(shmid==-1){
		printf("error con la obtencion de memoria del hijo\n");
		exit(1);
	}

	int * contador;
	contador=(int *) shmat(shmid,NULL, 0);

//ACCION PROCESO
	sem_wait(semaforo);//abre critica
	int local=*contador;
		for(int x=0;x<100;x++)
			local++;
		*contador=local;
		printf("El proceso %d deja el contador como %d \n", i, *contador);	//lo dejo dentro para poder ver si funciona bien(deberia ir fuera)
	sem_post(semaforo);//cierra critica
	shmdt(contador);
	sem_close(semaforo);
		exit(0);
}