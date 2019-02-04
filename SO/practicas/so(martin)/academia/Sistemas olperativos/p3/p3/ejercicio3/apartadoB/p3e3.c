/*b)Modifique el apartado a) usando variables de condición junto con mutexs para evitar espera activa. Cuando el consumidor toma un producto notifica al productor que puede comenzar a trabajar nuevamente porque al menos hay un hueco donde poner una producción. En caso contrario si el buffer se vacía, el consumidor se pone a dormir y en el momento en que el productor agrega un producto crea una señal para despertarlo. Consulte la documentación de clases de teoría si lo considera oportuno. */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include "p3e3.h"

pthread_cond_t no_lleno = PTHREAD_COND_INITIALIZER; //Controla el llenado del buffer
pthread_cond_t no_vacio = PTHREAD_COND_INITIALIZER; //Controla el vaciado del buffer
pthread_mutex_t semaforo = PTHREAD_MUTEX_INITIALIZER; // Declaración de variable 
int buffer[MAX_BUFFER]={0,0,0,0,0};	//Buffer, sección crítica
int unidades_disponibles=0; //Total de unidades disponibles en buffer
int unidades_totales=0;	//Número total de unidades que todas los hilos producirán

int main (){

pthread_t productor;		//Creamos el hilo productor
pthread_t consumidor;	//Creamos el hilo consumidor

	printf("\n** Programa de simulación de Productor-Consumidor usando hebras, semáforos y variables de condición **\n\n");			

	//Preguntamos por el número total de unidades a producir

	printf("¿Cuántas unidades se van a producir en total?\n");
	scanf("%d", &unidades_totales);
	printf("\n");

	// Creamos los hilos.

	if(pthread_create(&productor,NULL, (void *) producir, NULL) !=0){
		perror ("Error al crear el productor...\n");
		printf("errno value= %d\n", errno); 
		exit(EXIT_FAILURE);
	}

	if(pthread_create(&consumidor, NULL, (void *) consumir, NULL) !=0){
		perror ("Error al crear el consumidor...\n");
		printf("errno value= %d\n", errno); 
		exit(EXIT_FAILURE);
	}
		

// Esperamos a recoger los hilos.
	
	if(pthread_join(productor, NULL) !=0){
		perror ("Error en el join()...\n");
		printf("errno value= %d\n", errno); 
		exit(EXIT_FAILURE);
	}
	
	if(pthread_join(consumidor, NULL) !=0){
		perror ("Error en el join()...\n");
		printf("errno value= %d\n", errno); 
		exit(EXIT_FAILURE);
	}
	
	printf("Se han recibido correctamente todas las hebras\n\n");	
	
// Se destruye Semaforo y Variables de condición

	if(pthread_mutex_destroy(&semaforo) !=0){
		perror ("Error al destruir el semaforo...\n");
		printf("errno value= %d\n", errno); 
		exit(EXIT_FAILURE);
	}

	if(pthread_cond_destroy(&no_lleno) !=0){
		perror ("Error al destruir la condición no_lleno...\n");
		printf("errno value= %d\n", errno); 
		exit(EXIT_FAILURE);
	}	
	
	if(pthread_cond_destroy(&no_vacio) !=0){
		perror ("Error al destruir la condición no_vacío...\n");
		printf("errno value= %d\n", errno); 
		exit(EXIT_FAILURE);
	}	
	
	printf("Se han destruido correctamente todos los semáforos y variables de condición.\n\n");
	
	printf("Fin del programa.\n\n");			

return 0;


}
