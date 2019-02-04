#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h>
#include <string.h>

typedef struct parametros{
	int indice;
	int *vectorfila;
	int *vectorcolumna;
}params;

void *multi(params *par);

int main()
{
system("clear");

	int i, m[3][3]={{3,-1,8},{3,0,2},{4,-1,0}};
	int vectorcol[]={1,-1,2};
	int nh=3;
	int *valor_devuelto;

	params parametros[nh];	
	pthread_t thd[nh];
	

	for(i=0;i<nh;i++)
	{
	parametros[i].indice=i;
	parametros[i].vectorfila=m[i];
	parametros[i].vectorcolumna=vectorcol;
	
	pthread_create(&thd[i], NULL, (void*)multi, &parametros[i]);
	usleep(100000);

	}
	 for(i = 0; i < nh; i++) {
        pthread_join(thd[i], (void **) &valor_devuelto);
        printf("El hilo %d ha devuelto el valor %d\n",i+1, *valor_devuelto);
		
							}
}
void *multi(params *par)
{
	int *suma=(int*)malloc(sizeof(int));
	int i;
	*suma=0;
	for(i=0;i<3;i++){
	*suma+=par->vectorfila[i]*par->vectorcolumna[i];
					}
	pthread_exit((void*)suma);
}












