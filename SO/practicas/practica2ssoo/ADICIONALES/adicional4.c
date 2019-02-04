 /*Realice la multiplicación en paralelo de una matriz de 3x3 por un vector de 3x1.
  Para ello cree tres procesos que se repartan las filas de la matriz y del vector. 
  Cada hijo debe imprimir la fila que le ha tocado y el resultado final de la multiplicación la cual además envía al padre. 
  El padre debe esperar por la terminación de cada hijo y mostrar el vector resultante. */




#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>	
#include <sys/wait.h>

void multiplica(int i);

int matriz[3][3]={1,2,3,1,3,2,2,1,3};
int vector[3]={1,3,2};			//debe resultar 6, 18, 12

int main(){


	key_t clave;
	clave=ftok("adicional4.c", 1);

	int shmid;
	shmid=shmget(clave, 3*sizeof(int), IPC_CREAT | 0777);
	if(shmid==-1){
		printf("error con la obtencion de memoria del padre\n");
		exit(1);
	}

	for(int i=0; i<3;i++){
		if(!fork()){
			multiplica(i);
			exit(0);
		}
	}

	for(int i=0;i<3;i++){
		int status;
		int pid=wait(&status);					//pasa algo por int pid != pid_t ?
		printf("El proceso con pid: %d finaliza con status: %d\n\n", pid, status);
	}

	int * resultado;
	resultado=(int *) shmat(shmid, NULL, 0);
	printf("El resultado, calculado por los hijos es: [%i] [%i] [%i] \n", resultado[0], resultado[1], resultado[2]);


	shmdt(resultado);
	shmctl(shmid, IPC_RMID, NULL);
	return 0;
}

void multiplica(int i){

	key_t clave;
	clave=ftok("adicional4.c", 1);

	int shmid;
	shmid=shmget(clave, 3*sizeof(int), IPC_CREAT | 0777);
	if(shmid==-1){
		printf("error con la obtencion de memoria del hijo\n");
		exit(1);
	}

	int * resultado;
	resultado=(int *) shmat(shmid, NULL, 0);


	int local=0;
	for(int x=0;x<3;x++){
		local+=matriz[i][x]*vector[i];
	}

	printf("El resultado que obtiene el proceso que ejecuta la fila %d es: %d\n\n", i, local);
	
	//critica
	resultado[i]=local;
	//salir critica

	exit(0);
}
