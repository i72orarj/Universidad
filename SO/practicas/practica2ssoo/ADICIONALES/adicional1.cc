//ej3.cc

/*. Realice la multiplicación en paralelo de una matriz de 3x3 por un vector de 3x1. 
Para ello cree tres hebras que se repartan las filas de la matriz y del vector.
 Cada hijo debe imprimir la fila que le ha tocado y el resultado final de la multiplicación la cual además envía al padre.
  El padre debe esperar por la terminación de cada hijo y mostrar el vector resultante. */

#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
 #include <stdio.h> //exit

int matriz[3][3];
int vector[3];
int resultado[3];

int main(){
	extern int matriz[3][3]={1,2,3,1,3,2,2,1,3};
	extern int vector[3]={1,3,2};
	extern int resultado[3]; //debe ser 6, 18, 12
	pthread_t IDHilos[3];
	void * funcion(void * id);

	int status;

	for(int i=0;i<3;i++){
		IDHilos[i]=i;
		int v[i]={i};
		if((status=pthread_create(IDHilos+i, NULL, &funcion ,(void *) &v[i])))
			printf("error en la creacion del hilo\n");
			exit(status);
	}

	for(int x=0;x<3;x++)
		pthread_join(IDHilos[x], &(resultado+x));		//resultado[x]

	for(int i=0;i<3;i++){
		printf("[%i] [%i] [%i] \n", resultado[0], resultado[1], resultado[2]);
	}
	
}


void * funcion(void * id){
	extern int matriz[3][3];
	extern int vector[3];
	extern int resultado[3];

	int * fila = (int *) id;

	printf("Para el hilo %i, la fila %i:\n",*fila, *fila);
	for(int i=0;i<3;i++)
		printf("v[%i]: %i\n",*fila, matriz[*fila][i]);

	int total=0;
	for(int x=0;x<3;x++)
		total+=(matriz[*fila][x]*vector[*fila]);

	printf("Para el hilo %i, resultado %i:\n",*fila, total);

	int * aportacion=(int *)malloc(sizeof(int));
	aportacion=&total;

    pthread_exit((void *) aportacion);	

}


