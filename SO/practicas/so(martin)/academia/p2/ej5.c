#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>
#define TAM 1000
void *funcion(void * arg);

int main(int argc , char **argv)
{
	int i;
	int *dev;
	int suma=0;
	pthread_t thd[TAM];

	for(i=0;i<2;i++)
	{
		pthread_create(&thd[i], NULL, (void *) funcion, (void *) argv[i+1]);

	}

	for(i=0;i<2;i++)
	{
		pthread_join(thd[i],(void**) &dev);
		suma=suma+(*dev);
	}
	printf("El número de líneas es :%d\n", suma);
	exit(EXIT_SUCCESS);
}

void *funcion(void * arg)
{
	
	FILE *fich;
	char cadena[TAM];
	char copia[TAM];
	strcpy(copia, (char*)arg);
	int *cont=malloc(sizeof(int));
	*cont=0;
	fich=fopen(copia, "r");
	if(fich)
	{	
	while(fscanf(fich, "%s", cadena)==1)
	{
		*cont=*cont+1;
	}

	}
	fclose(fich);
	printf("El nº de lineas en el fichero %s aqui es :%d\n", copia, *cont);
	pthread_exit((void *) cont);
}	