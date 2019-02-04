#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include "p3e3.h"

extern pthread_cond_t no_lleno;
extern pthread_cond_t no_vacio;
extern pthread_mutex_t semaforo; 
extern int unidades_disponibles;
extern int unidades_totales;  //ESTO SE PODRIA HABER PUESTO COMO UN #define
extern int buffer[MAX_BUFFER];

//Producir

void * producir (void * arg){

int i;
int dato;
int pos=0;


	for (i=1;i<=unidades_totales;i++){

		dato = i; // producir dato

		//Cerramos semaforo y accedemos al buffer

		if(pthread_mutex_lock(&semaforo) != 0){
			perror ("Error al poner el rojo el semaforo... \n");
			printf("errno value= %d\n", errno); 
			exit(EXIT_FAILURE);
		}
	
		//Hacer si buffer lleno
		
		while (unidades_disponibles == MAX_BUFFER){ 

		//Bloquea al Productor

			if(pthread_cond_wait(&no_lleno,&semaforo) != 0){
				printf("Error de concidion de espera\n");
				printf("errno value= %d\n", errno); 	
				exit(EXIT_FAILURE);		
			}

		}
	
		//Producimos unidades
		
		printf("\nProductor:\n\n");
		buffer[pos]=i;
		pos=(pos+1) % MAX_BUFFER;
		unidades_disponibles++;
		printf("Hay %d unidades disponibles\n\n",unidades_disponibles);	

		//Mandamos señal y despertamos al consumidor
	
		if(pthread_cond_signal(&no_vacio) != 0){
			perror ("Error al mandar señal... \n");
			printf("errno value= %d\n", errno); 
			exit(EXIT_FAILURE);
		}	
		
		//abrimos semaforo
		if(pthread_mutex_unlock(&semaforo) != 0){
			perror ("Error al poner en verde el semaforo... \n");
			printf("errno value= %d\n", errno); 
			exit(EXIT_FAILURE);
		}
			
	}
		
	pthread_exit(NULL);		
	
}

//Consumir

void * consumir (void * arg){

int dato;
int i;
int pos=0;
int unidades_consumidas=0;

	//Bucle para consumir

	for (i=1;i<=unidades_totales;i++){
		
		//Cerramos semaforo y accedemos al buffer

		if(pthread_mutex_lock(&semaforo) != 0){
			perror ("Error al poner el rojo el semaforo... \n");
			printf("errno value= %d\n", errno); 
			exit(EXIT_FAILURE);
		}
	
		while(unidades_disponibles == 0) {
	
			//bloqueamos al consumidor

			if(pthread_cond_wait(&no_vacio, &semaforo) != 0){
				printf("Error de concidion de bloqueo.\n");
				printf("errno value= %d\n", errno); 	
				exit(EXIT_FAILURE);		
			}
		
		}
	
		//Consume unidades
	
		dato=buffer[pos];
		pos=(pos+1) % MAX_BUFFER;	
		unidades_disponibles--;
		unidades_consumidas++;
		printf("Consumidor:\n"
			   "Total unidades consumidas: %d\n", unidades_consumidas);
		
		if(unidades_consumidas == unidades_totales){
			printf("He consumido todas las unidades.\n\n");					
		}		
		

		//Mandamos señal y despertamos al productor
	
		if(pthread_cond_signal(&no_lleno) != 0){
			perror ("Error al mandar señal... \n");
			printf("errno value= %d\n", errno); 
			exit(EXIT_FAILURE);
		}		
		
		//abrimos semaforo

		if(pthread_mutex_unlock(&semaforo) != 0){
			perror ("Error al poner en verde el semaforo... \n");
			printf("errno value= %d\n", errno); 
			exit(EXIT_FAILURE);
		}			

	}

	pthread_exit(NULL);		
	
}

