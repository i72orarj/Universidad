#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>

void *randomNUM(void *ind);
int main(int argc, char **argv)
{
system("clear");
	int n=atoi(argv[1]);
	int error=0, i;
	pthread_t thd[n];
	int v[n];
	int* valor_devuelto;
	int suma=0;
	srand(time(NULL));
	
	if(argc!=2)
	{
		puts("Error en los argumentos.");
		exit(-1);
	}

	for(i=0;i<n;i++)
	{
		v[i]=i;
		error=pthread_create(&thd[i], NULL, (void *) randomNUM, (void *) &v[i]);
		sleep(1);
			if(error==-1)
			{
				puts("Error en la creacion de hilos.");
				printf("errno value:%d\n", errno);
			}
	}

	for(i=0;i<n;i++)
	{
		pthread_join(thd[i], (void **) &valor_devuelto);
		suma=suma+*valor_devuelto;
	}
	printf("La suma total es :%d\n", suma);
	exit(EXIT_SUCCESS);
}

void *randomNUM(void *ind)
{ 
	int *indice= (int *)ind;
	int num1, num2;
	int *suma=malloc(sizeof(int));
	num1=rand()%11;
	num2=rand()%11;

	*suma=num1+num2;

	printf("Hilo %d, con número 1: %d y número 2: %d\n", *indice, num1, num2);
	pthread_exit((void *)suma);
}