#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

char nombreF[256];
int fin_fichero=0;
int contador=0;

pthread_mutex_t mutex=PTHREAD_MUTEX_INITILIZER;
pthread_cond_t cond=PTHREAD_COND_INITIALIZER;
pthread_cond_t terminen=PTHREAD_COND_INITIALIZER;

int main(int argc, char **argv)
{
	int num, i, v[10];
	strcpy(nombreF, argv[2]);

	pthread_t thd[num+1];

	for(i=1;i<num+1;i++)
	{
		v[i]=i;
		pthread_create(&thd[i], NULL, (void*) escritores, (void *) &v[i])
	}
	usleep(10000);
	pthread_create(&thd[0], NULL, (void *) principal, NULL );

	for(i=0;i<num;i++)
	{
		pthread_join(thd[i], NULL);
	}

}

void *principal(void *arg)
{
	FILE *fich=NULL;
	char cadena[1024];
	fich=fopen(nombreF, "r");
	if(fich)
	{
		while(1)
		{
			pthread_mutex_lock(&mutex);

			if(fgets(cadena,1024,fich)!=NULL)
			{
				pthread_cond_broadcast(&cond);
				pthread_cond_wait(&terminen, &mutex);
			}
			else{
				fin_fichero=1;
				pthread_cond_broadcast(&cond);
			}
			pthread_mutex_unlock(&mutex);
		}

		
	}
	fclose(fich);
	pthread_exit(0);
}

void *escritores(int *indice)
{
	FILE *fich=NULL;
	fich=fopen(nombreF, "w");
	char numero[5];
	sprintf(numero,"%d", *indice);

	while(1)
	{
		if(fich)
		{
			pthread_mutex_lock(&mutex);


			pthread_cond_wait(&cond, &mutex);
			if(fin_fichero==1) break;
			fputs(cadena,fich);

			if(contador<=5)
			{
				cont++;
			}
			else{
				cont=0;
				pthread_cond_signal(&terminen);
			}
			pthread_mutex_unlock(&mutex);
		}	

	}
	pthread_mutex_unlock(&mutex);
	fclose(fich);
}