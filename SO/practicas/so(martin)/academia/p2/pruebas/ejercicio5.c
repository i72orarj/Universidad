#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>

void * funcion(void *arg);
#define TAM 10

int main(int argc, char **argv)
{
	system("clear");
	int error, i;
	int *valor_devuelto;
	pthread_t thd[TAM];
	int n_hilos= argc-1;
	int suma=0;


	for(i=0;i<n_hilos; i++)
	{
		pthread_create(&thd[i], NULL, (void *) funcion, (void *) argv[i+1]);

	}
		puts("Fichero 1:");
		system("cat fichero1.txt");
		puts("Fichero 2:");
		system("cat fichero2.txt");
	for(i=0;i<n_hilos;i++)
	{
		pthread_join(thd[i], (void **) &valor_devuelto);
		
		printf("El fichero %s tiene %d lineas\n", argv[i+1], *valor_devuelto);

		suma=suma+*valor_devuelto;
	}

	printf("La suma total de líneas es :%d\n", suma);


}

void * funcion(void *arg)

{
	char cadena[TAM];
	char copia[TAM];
	strcpy(copia, (char *) arg);
	int *cont= malloc(sizeof(int));
	*cont=0;
	FILE *fich=NULL;
	fich=fopen(copia, "r");

		if(fich)
		{
			while(fscanf(fich,"%s", cadena)==1)
			{
				*cont=*cont+1;
			}
			
		}
		fclose(fich);
		pthread_exit((void *) cont);
}