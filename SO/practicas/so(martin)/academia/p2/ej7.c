#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
int cont=0;
void *funcion(void *argu);
main()
{
	int n=2,  i;
	pthread_t thd[n];
	int *valor_devuelto;
	int v[n];
	for(i=0;i<n;i++)
	{
		v[i]=i;
		pthread_create(&thd[i], NULL, (void *) funcion, (void*) &v[i]);
	}
		for(i=0;i<n;i++)
	{
		pthread_join(thd[i],NULL);

	}
	printf("La variable global impresa es :%d\n", cont);
}

void *funcion(void *argu)
{

	int i;
	for(i=0;i<50;i++)
	{
		cont++;
	}
	
}