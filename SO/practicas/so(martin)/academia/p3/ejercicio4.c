/******************************************* 
 Hilos para copiar varias veces un fichero 
 ********************************************/
#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h>
#include <string.h>

char nombre_fichero[100];

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
//Variable que envia el lector para que se vayan desbloqueando las copias
pthread_cond_t cond = PTHREAD_COND_INITIALIZER; 
// Variable que envía el último lector para reactivar al lector
pthread_cond_t terminen = PTHREAD_COND_INITIALIZER;

int copias=0;
char cadena[1024];
int contador=0;
int fin_fichero=0;

void *principal(void *arg){

	int s,i;
	int c;
	FILE *f;

	f = fopen(nombre_fichero,"r");

		while(1)
		{
				//Bloqueo el mutex
				pthread_mutex_lock(&mtx);
				
				// Sección crítica
				if(fgets(cadena, 1024, f) != NULL)				
				{   				
					printf("Soy el lector y leí del fichero: %s\n", cadena);
					// saco a los copiadores de la espera
					pthread_cond_broadcast(&cond);
					// me espero a que terminen
					pthread_cond_wait(&terminen, &mtx);
					
				} 
				else {   // si llego al final del fichero
					fin_fichero = 1;
					// Una vez que termino saco a los copiadores de la espera y termino
					pthread_cond_broadcast(&cond);
					s = pthread_mutex_unlock(&mtx); 
					break;
				}
				
				// Desbloqueo el mutex
				pthread_mutex_unlock(&mtx); 
		}		

	fclose(f);
	pthread_exit(NULL);
}

void *copiador(int *indice)
{
	char copia[100], numero[5];
	int s,i;
	FILE *f1;

	strcpy(copia,nombre_fichero);
    sprintf(numero,"%d",*indice);  
    strcat(copia, numero);

	f1 = fopen(copia,"w");	

	while(1) 
	{
		pthread_mutex_lock(&mtx);

		// me espero a que el lector me diga que puedo acceder
		pthread_cond_wait(&cond, &mtx);

		// si se ha llegado al fin del fichero me salgo
		if(fin_fichero) break;

		// escribo la cadena en mi fichero
		fputs(cadena,f1);
			
		if(contador<copias-1) // Si no soy el último 
		{
			 printf("Soy el %lu y he leido: %s\n",pthread_self(), cadena);
			 contador = contador + 1;
		}
		else   // soy el último en leer
		{   
			 printf("Soy el último- %lu y he leido: %s el ultimo\n",pthread_self(), cadena);
			 contador = 0;
			 // envío la señal al lector para que despierte
			 pthread_cond_signal(&terminen);
		}

		pthread_mutex_unlock(&mtx);
		
	}
	pthread_mutex_unlock(&mtx);
	fclose(f1);

}

int main(int argc,char **argv){

	int num,i, indices[50];

	// argumento 1, el nombre del fichero a copiar
	// argumento 2, la cantidad de copias o hilos
	strcpy(nombre_fichero, argv[1]);
	num = atoi(argv[2]);
	pthread_t hebra[num+1];
	copias = atoi(argv[2]);

	for(i=1;i<num+1;i++){
		indices[i] = i;
		pthread_create(&hebra[i],NULL,(void*)copiador,&indices[i]);
	}
	
	usleep(100000);
	pthread_create(&hebra[0],NULL,(void*)principal,NULL); //hebra principal
	
	for(i=0;i<num+1;i++){

		pthread_join(hebra[i],NULL);
	}

}

	
