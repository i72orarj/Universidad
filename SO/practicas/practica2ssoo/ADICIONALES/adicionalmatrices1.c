//ej3.cc

/*. Realice la multiplicación en paralelo de una matriz de 3x3 por un vector de 3x1. 
Para ello cree tres hebras que se repartan las filas de la matriz y del vector.
 Cada hijo debe imprimir la fila que le ha tocado y el resultado final de la multiplicación la cual además envía al padre.
  El padre debe esperar por la terminación de cada hijo y mostrar el vector resultante. */

#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
 #include <stdio.h> //exit

int matriz[3][3]={1, 2, 3, 1, 3, 2, 2, 1, 3};
int vector[3]={1, 3, 2};
int * resultado[3];
void * funcion(void * id);

int main(){
	extern int matriz[3][3];
	extern int vector[3];
	extern int * resultado[3];
	pthread_t IDHilos[3];


	int status;
	int v[3];
	for(int i=0;i<3;i++){
		
		v[i]=i;
		if((status=pthread_create(IDHilos+i, NULL, &funcion ,(void *) &v[i]))){
			printf("error en la creacion del hilo\n");
			exit(status);}
	}

	for(int x=0;x<3;x++)
		pthread_join(IDHilos[x], (void **) &(resultado[x]));		//resultado[x]

	printf("[%i] [%i] [%i] \n", *(resultado[0]), *(resultado[1]), *(resultado[2]));



	
	
}


void * funcion(void * id){
	extern int matriz[3][3];
	extern int vector[3];
	extern int * resultado[3];

	int * fila = (int *) id;

	printf("El hilo %i calcula la fila %i:\n",*fila, *fila);
	for(int i=0;i<3;i++)
		printf("v[%i]: %i\n",*fila, matriz[*fila][i]);

	int total=0;
	for(int x=0;x<3;x++)
		total+=(matriz[*fila][x]*vector[*fila]);

	printf("El hilo %i obtiene como resultado %i:\n",*fila, total);

	int * aportacion=(int *)malloc(sizeof(int));
	*aportacion=total; //aportacion=&total no funciona, va mal

    pthread_exit((void *) aportacion);	//return

}


