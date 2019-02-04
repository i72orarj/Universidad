#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#define TAM 10

struct reparto_info
{
	int desde;
	int hasta;
	int *vector;
};

void *fsuma(void *arg);

int main(int argc, char **argv)
{
	srand(time(NULL));
	int desde, hasta;
	struct reparto_info reparto;
	struct reparto_info reparto_hebras[TAM];
	int n_hilos=atoi(argv[1]);
	pthread_t thd[TAM];
	int vector[TAM];
	int *valor_devuelto;
	int suma=0, i, error=0;

	if(argc!=2)
	{
		puts("Error en línea de órdenes.");
		exit(EXIT_FAILURE);
	}
	
	for(i=0;i<10;i++)
	{
		vector[i]=rand()%11;
		printf("%d\n", vector[i]);
		suma+=vector[i];


	}
	printf("La suma 1º es :%d\n", suma);
	suma=0;

	desde=0;
	hasta=(n_hilos)/10;

	for(i=0;i<n_hilos;i++)
	{
		reparto.vector=vector;
		reparto.desde =desde;

			if(i==n_hilos-1)
			{
				reparto.hasta=10;
			}
			else
			{
				reparto.hasta=desde+hasta;
				
			}
				reparto_hebras[i]=reparto;
				desde=reparto.hasta;

			error= pthread_create(&(thd[i]), NULL, (void*) fsuma, (void *) &reparto_hebras[i]);
					if(error==-1)
					{
						perror(" thread error");
						printf("errno value:%d\n", errno);
					}

	}

		for(i=0;i<n_hilos;i++)
		{
			pthread_join(thd[i], (void **) &valor_devuelto);
			suma+=*valor_devuelto;


		}


		printf("la suma es : %d\n", suma);
	

}


void *fsuma(void * arg)
{
	int i;
	int *suma=malloc(sizeof(int));
	*suma=0;
	struct reparto_info *reparto=(struct reparto_info*) arg;

		for(i=reparto->desde; i<reparto->hasta;i++)
		{
			*suma=*suma+(reparto->vector[i]);
		}

		pthread_exit((void *) suma);
}