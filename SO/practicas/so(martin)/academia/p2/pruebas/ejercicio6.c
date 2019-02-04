#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <stdio.h>
void *funcion(void *arg);
typedef struct parametros
{
int indice;
int *vector_col;
int *vector_fil;
}params;

main()
{
	int nh=3;
	int vectorcol[]={1,-1,2};
	int i, m[3][3]={{3,-1,8},{3,0,2},{4,-1,0}};
	params parametros[nh];
	int *suma;
	pthread_t thd[nh];

	for(i=0;i<nh;i++)
	{
		parametros[i].indice=i;
		parametros[i].vector_col=vectorcol;
		parametros[i].vector_fil=m[i];
		pthread_create(&thd[i], NULL, (void *) funcion, (void *) &parametros[i]);
	}

	for(i=0;i<nh;i++)
	{
		pthread_join(thd[i], (void **) &suma);
			printf("La suma es %d del hilo %d\n", *suma, i);
	}


}

void *funcion(void *arg)
{
	params *par= (params*) arg;
	int *suma=malloc(sizeof(int));
	int i;
	*suma=0;
		for(i=0;i<3;i++)
		{
			*suma+=par->vector_col[i]*par->vector_fil[i];
		}
		pthread_exit((void *) suma);
}