#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#define TAM 10

void *funcion(void * arg);
struct reparto_info
{
	int *vector;
	int desde;
	int hasta;
};


int main(int argc, char **argv)
{
	int desde, hasta, n=atoi(argv[1]);
	struct reparto_info parametros[TAM];
	struct reparto_info reparto;
	int *valor_devuelto;
	int error=0, i, vector[TAM], suma=0;
	pthread_t thd[TAM];
	srand(time(NULL));

	if(argc!=2)
		puts("Error en la linea de ordenes.");

	for(i=0;i<TAM;i++)
	{
		vector[i]=rand()%11;
		printf("%d\n", vector[i]);
		suma+=vector[i];

	}
	printf("La suma hecha sin threads :%d\n", suma);
	suma=0;
	desde=0;
	hasta=n/10;




	for(i=0;i<n;i++)
	{
		reparto.vector=vector;
		reparto.desde=desde;
		if(i==n-1)
		{
			reparto.hasta=10;
		}
		else{
			reparto.hasta=desde+hasta;
		}
		parametros[i]=reparto;
		desde=reparto.hasta;

		pthread_create(&thd[i], NULL, (void *) funcion, (void *) &parametros[i]);
	}


	for(i=0;i<n;i++)
	{
		pthread_join(thd[i], (void **) &valor_devuelto);
		suma=suma+*valor_devuelto;
	}
	printf("La suma total es %d\n", suma);
}

void *funcion(void * arg)
{
	struct reparto_info *par=(struct reparto_info *) arg;

	int i;
	int *suma=malloc(sizeof(int));
	*suma=0;

	for(i=par->desde; i<par->hasta; i++)
	{
		*suma=*suma+par->vector[i];
	}
	pthread_exit((void *) suma);
}