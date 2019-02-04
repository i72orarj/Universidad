
//Sistemas Operativos
//Práctica 2. Ejercicio 1
//Programa que crea dos hebras para imprimir dos cadenas, cada hebra imprime una cadena.
// --> cadena1 'Hola'
// --> cadena2 'mundo'
// --> O bien las dos cadenas que se reciban por parámetro.

// --> Adaptado para controlar:
//          - Que una hebra no puede hacer un join de sí misma.
//          - Que a una hebra que ha sido detached ya no se le puede hacer un join.
//          - Que a una hebra sólo se le puede hacer un join.

#include <stdio.h>
#include <pthread.h>
#include <errno.h>	//Códigos de error
#include <string.h>	//Cadenas
#include <stdlib.h>


void * imprime_cadena(void * parametro){

	//Función que imprime la cadena que recibe por parámetro.

	//Declaración de variables.

	char *cadena;
	int i;

	//Conversión de void * a char *
	cadena = (char *)parametro;

	for(i=0;i<strlen(cadena);i++){

		sleep(1);
		printf("%c\n", *(cadena+i));

	}

	//Finalización correcta y no devuelve nada.
	pthread_exit(NULL);

}



void * join_hebra(void * parametro){

	//Función que hace un join a la hebra que recibe por parámetro.

	//Declaración de variables.

	pthread_t *puntero_hebra;
	pthread_t hebra;

	int error;

	//Conversión
	puntero_hebra = (pthread_t *)parametro;

	hebra=*puntero_hebra;

	//Hacemos el join a la hebra.
	error=pthread_join(hebra, NULL);

	//Capturamos los errores que se pueden producir al recoger (join) una hebra.
	switch (error){

		case 0: //Correcto.

			printf("    (función join_hebra) Terminó correctamente la hebra ..: %lu\n", (unsigned long int)hebra);

			break;


		case EDEADLK: //Se quiso hacer un join a sí misma.

			printf("    (función join_hebra) Se quiso hacer un join a sí mismo.\n");

			break;

		case EINVAL: //La hebra ha sido detached u otra hebra está esperando a que termine.

			printf("    (función join_hebra) Se produjo el error EINVAL (la hebra ha sido detached u otra hebra está esperando a que termine.).\n");

			break;

		case ESRCH:  //Se ha hecho un pthread_join sobre una hebra que no existe.

			printf("    (función join_hebra) Se produjo el error ESRCH (la hebra no existe).\n");

			break;

	}

	//Si descomentamos la línea 98, en el join de la línea 202 dará el error:
	//EINVAL: porque hemos hecho el detach de esta hebra y ya no puede ser recogida.
	//pthread_detach(pthread_self());

	//Finalización correcta y no devuelve nada.
	pthread_exit(NULL);

}



int main(int argc, char **argv){

	//Declaración de variables.

	char cadenas[2][150]={"Hola\0","mundo\0"};

	pthread_t hebras[3];

	int i;
	int error;


	printf("\n\n");


	//Controlamos los parámetros.
	if(argc==2 || argc>3){

		printf("Parámetros incorrectos.\n");
		printf("Sintaxis correcta: %s <cadena1> <cadena2>\n", argv[0]);
		printf("Se para la ejecución del programa.\n");
		exit(-1);

	}

	if(argc==3){

		//Se reciben las dos cadenas por parámetro.
		strcpy(cadenas[0],argv[1]);
		strcpy(cadenas[1],argv[2]);

	}
	

	//Creamos las hebras.
	for(i=0;i<3;i++){

		if(i==2){

			error = pthread_create( &(hebras[i]), NULL, (void *) join_hebra, (void *) &hebras[0]);			

		}
		else{

			error = pthread_create( &(hebras[i]), NULL, (void *) imprime_cadena, (void *) cadenas[i]);

		}

		sleep(1);

		//Capturamos los errores que se pueden producir al crear una hebra.
		switch (error){

			case 0: //Correcto.

				printf("    (Hilo ppal. 1) Se ha creado la hebra ..: %lu\n", (unsigned long int)hebras[i]);

				break;

			case EAGAIN: //El sistema no puede crear más hebras bien porque se ha llegado al máximo PTHREAD_THREADS_MAX
				     //o bien porque se ha quedado sin recursos para ello.

				printf("    (Hilo ppal. 1) Se produjo el error EAGAIN (sin recursos o máximo de hebras alcanzado).\n");

				break;

			case EINVAL: //La configuración especificada en el parámetro attr no es correcta.

				printf("    (Hilo ppal. 1) Se produjo el error EINVAL (valores de attr incorrectos).\n");

				break;

			case EPERM:  //El proceso no tiene los permisos apropiados para configurar la política de planificacion
				     //o la configuración indicada en el parámetro attr.

				printf("    (Hilo ppal. 1) Se produjo el error EPERM (sin privilegios para configurar la planificación o attr).\n");

				break;

		}

	}

	//El sleep(4) es para dar tiempo a la función join_hebra para que recoja a la hebra que recibe por parámetro.
	//De este modo cuando se intente recoger de nuevo dicha hebra en el join de la línea 202 se producirá el error:
	//      ESRCH:  porque la función join_hebra ya habrá ejecutado la línea 66 y habrá recogido a la hebra.

	//Si se comenta el sleep(4) entonces se producirá el error:
	//      EINVAL: porque la función join_hebra estará esperando en la línea 66 a que termine la hebra para recogerla.

	sleep(4);

	//Esperamos a la finalización de las hebras.
	for(i=0;i<3;i++){

		error = pthread_join(hebras[i], NULL);

		//error = pthread_join(pthread_self(),NULL); //No se puede hacer un join de sí misma.

		//Capturamos los errores que se pueden producir al recoger (join) una hebra.
		switch (error){

			case 0: //Correcto.

				printf("    (Hilo ppal. 2) Terminó correctamente la hebra ..: %lu\n", (unsigned long int)hebras[i]);

				break;


			case EDEADLK: //Se quiso hacer un join a sí misma.

				printf("    (Hilo ppal. 2) Se quiso hacer un join a sí mismo.\n");

				break;

			case EINVAL: //La hebra ha sido detached u otra hebra está esperando a que termine.

				printf("    (Hilo ppal. 2) Se produjo el error EINVAL (la hebra ha sido detached u otra hebra está esperando a que termine.).\n");

				break;

			case ESRCH:  //Se ha hecho un pthread_join sobre una hebra que no existe.

				printf("    (Hilo ppal. 2) Se produjo el error ESRCH (la hebra no existe).\n");

				break;

		}

	}


	//En este pundo del programa todas las hebras han finalizado y han sido recogidas, por lo tanto el siguiente join dará error
	//porque ya no existe la hebra que se quiere recoger. (sólo un join por hebra).

	error = pthread_join(hebras[0], NULL);

	//Capturamos los errores que se pueden producir al recoger (join) una hebra.
	switch (error){

		case 0: //Correcto.

			printf("    (Hilo ppal. 3) Terminó correctamente la hebra ..: %lu\n", (unsigned long int)hebras[i]);

			break;


		case EDEADLK: //Se quiso hacer un join a sí misma.

			printf("    (Hilo ppal. 3) Se quiso hacer un join a sí mismo.\n");

			break;

		case EINVAL: //La hebra ha sido detached u otra hebra está esperando a que termine.

			printf("    (Hilo ppal. 3) Se produjo el error EINVAL (la hebra ha sido detached u otra hebra está esperando a que termine.).\n");

			break;

		case ESRCH:  //Se ha hecho un pthread_join sobre una hebra que no existe.

			printf("    (Hilo ppal. 3) Se produjo el error ESRCH (la hebra no existe).\n");

			break;

	}


	printf("    (Hilo ppal.) Finalización correcta.\n");

	printf("\n\n");

	//Finalización correcta y no devuelve nada.
	pthread_exit(NULL);
}
