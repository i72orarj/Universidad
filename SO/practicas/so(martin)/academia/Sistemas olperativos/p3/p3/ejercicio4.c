
//Sistemas Operativos
//Práctica 3. Ejercicio 4
//Programa: lectores-escritores sin espera activa.
//1 escritor y N lectores


#include <stdio.h>
#include <pthread.h>
#include <errno.h>	//Códigos de error
#include <string.h>	//Cadenas
#include <stdlib.h>


//Para controlar errores en los semáforos.
	void error_en_destroy_mutex(int error);
	void error_en_init_mutex(int error);
	void error_en_unlock_mutex(int error);
	void error_en_lock_mutex(int error);
//



pthread_mutex_t escritor;	//Semáforo binario.
pthread_mutex_t lectores;	//Semáforo binario.

int cuentalectores;	//Lectores simultáneos leyendo del fichero.
int terminaescribir;


void * fescritor(void * parametro){

	//Función escritor: escribe en el fichero 1 .. 100

	//Declaración de variables.

	FILE *fichero;

	int lineas;
	int suma;
	int error;

	lineas=0;

	while(lineas!=100){

		//Escribimos una línea
		error=pthread_mutex_lock(&escritor);
			if(error!=0){

				//Se produjo un error.
				error_en_lock_mutex(error);

			}

			fichero=fopen("fichero.txt", "a");

			if(fichero==NULL){

				printf("\n      Error!! No se pudo abrir el fichero para escribir: fichero.txt\n");
				exit(-1);

			}

			fprintf(fichero, "%d\n", lineas+1);

			fclose(fichero);

		error=pthread_mutex_unlock(&escritor);
		if(error!=0){

			//Se produjo un error.
			error_en_unlock_mutex(error);

		}

		lineas=lineas+1;

	}

	error=pthread_mutex_lock(&escritor);
		if(error!=0){
	
			//Se produjo un error.
			error_en_lock_mutex(error);

		}

	terminaescribir=1;

	error=pthread_mutex_unlock(&escritor);
	if(error!=0){

		//Se produjo un error.
		error_en_unlock_mutex(error);

	}


	printf("\n   --> Escritor valor total de las líneas producidas ..: %d", lineas);

	//Finalización correcta y no devuelve nada.
	pthread_exit(NULL);

}

void * lector(void * parametro){

	//Función lector: lee el fichero que el escritor va escribiendo.

	//Declaración de variables.

	FILE *fichero;

	int lineas;
	char cadena[80];

	int finaliza;
	int error;

	finaliza=0;

	lineas=0;

	//Hacemos el recuento del número de lineas del fichero, mientras el escritor no haya terminado de escribir en él.
	while(finaliza==0){

		error=pthread_mutex_lock(&lectores);
		if(error!=0){

			//Se produjo un error.
			error_en_lock_mutex(error);

		}

		//Incrementamos en uno los lectores simultáneos.
		cuentalectores=cuentalectores+1;

		if(cuentalectores==1){

			//Es el primer lector que empieza a leer.
			//Cerramos para que el escritor no pueda escribir mientras se lee.

			error=pthread_mutex_lock(&escritor);

			if(error!=0){

				//Se produjo un error.
				error_en_lock_mutex(error);

			}

		}

		finaliza=terminaescribir;

		error=pthread_mutex_unlock(&lectores);
		if(error!=0){

			//Se produjo un error.
			error_en_unlock_mutex(error);

		}

		//Leemos el fichero.

		lineas=0;

		fichero=fopen("fichero.txt", "r");

		if(fichero==NULL){

			printf("\n      Error!! No se pudo abrir el fichero para leer: fichero.txt\n");

		}else{

			fscanf(fichero,"%s",cadena);

			while(!feof(fichero)){

				lineas=lineas+1;
				fscanf(fichero,"%s",cadena);

			}

			//Cerramos el fichero.
			fclose(fichero);

			//Decrementamos en uno los lectores simultáneos.
			error=pthread_mutex_lock(&lectores);
			if(error!=0){

				//Se produjo un error.
				error_en_lock_mutex(error);

			}

			cuentalectores=cuentalectores-1;

			if(cuentalectores==0){

				//Ya no hay lectores leyendo.
				//Abrimos el semáforo para que el escritor pueda escribir.

				error=pthread_mutex_unlock(&escritor);
				if(error!=0){

					//Se produjo un error.
					error_en_unlock_mutex(error);

				}

			}

			error=pthread_mutex_unlock(&lectores);
			if(error!=0){

				//Se produjo un error.
				error_en_unlock_mutex(error);

			}

			printf("\n   --> Lector valor total de las líneas leídas ..: %d", lineas);

		}

	}

	//Finalización correcta y no devuelve nada.
	pthread_exit(NULL);

}


int main(){

	//Declaración de variables.

	pthread_t hebras[4];

	int i;
	int error;

	printf("\n\n");

	//Lectores simultáneos leyendo del fichero.
	cuentalectores=0;

	terminaescribir=0;

	//Inicializamos los semáforos.
	error=pthread_mutex_init(&escritor,NULL);
	if(error!=0){

		//Se produjo un error.
		error_en_init_mutex(error);

	}

	error=pthread_mutex_init(&lectores,NULL);
	if(error!=0){

		//Se produjo un error.
		error_en_init_mutex(error);

	}


	//Creamos las hebras: 1 Escritor / n Lectores.
	for(i=0;i<4;i++){

		if(i==0){

			//Escritor
			error = pthread_create( &(hebras[i]), NULL, (void *) fescritor, NULL);

		}else{

			//Lectores
			error = pthread_create( &(hebras[i]), NULL, (void *) lector, NULL);

		}
		
		//Capturamos los errores que se pueden producir al crear una hebra.
		switch (error){

			case 0: //Correcto.

				printf("    (Hilo ppal.) Se ha creado la hebra ..: %lu\n", (unsigned long int)hebras[i]);

				break;

			case EAGAIN: //El sistema no puede crear más hebras bien porque se ha llegado al máximo PTHREAD_THREADS_MAX
				     //o bien porque se ha quedado sin recursos para ello.

				printf("    (Hilo ppal.) Se produjo el error EAGAIN (sin recursos o máximo de hebras alcanzado).\n");

				break;

			case EINVAL: //La configuración especificada en el parámetro attr no es correcta.

				printf("    (Hilo ppal.) Se produjo el error EINVAL (valores de attr incorrectos).\n");

				break;

			case EPERM:  //El proceso no tiene los permisos apropiados para configurar la política de planificacion
				     //o la configuración indicada en el parámetro attr.

				printf("    (Hilo ppal.) Se produjo el error EPERM (sin privilegios para configurar la planificación o attr).\n");

				break;

		}

		
	}


	//Esperamos a la finalización de las hebras.
	for(i=0;i<4;i++){

		error = pthread_join(hebras[i], NULL);

		//Capturamos los errores que se pueden producir al recoger (join) una hebra.
		switch (error){

			case 0: //Correcto.

				printf("    (Hilo ppal.) Terminó correctamente la hebra ..: %lu\n", (unsigned long int)hebras[i]);

				break;


			case EDEADLK: //Se quiso hacer un join a sí misma.

				printf("    (Hilo ppal.) Se quiso hacer un join a sí mismo.\n");

				break;

			case EINVAL: //La hebra ha sido detached u otra hebra está esperando a que termine.

				printf("    (Hilo ppal.) Se produjo el error EINVAL (la hebra ha sido detached u otra hebra está esperando a que termine.).\n");

				break;

			case ESRCH:  //Se ha hecho un pthread_join sobre una hebra que no existe.

				printf("    (Hilo ppal.) Se produjo el error ESRCH (la hebra no existe).\n");

				break;

		}

	}

	printf("    (Hilo ppal.) Finalización correcta.\n");

	printf("\n\n");

	//Liberamos los semáforos.
	error=pthread_mutex_destroy(&escritor);
	if(error!=0){

		//Se produjo un error.
		error_en_destroy_mutex(error);

	}

	error=pthread_mutex_destroy(&lectores);
	if(error!=0){

		//Se produjo un error.
		error_en_destroy_mutex(error);

	}


	//Finalización correcta y no devuelve nada.
	pthread_exit(NULL);
}



void error_en_lock_mutex(int error){

	//Función para controlar los errores que se pueden producir al bloquear un semáforo.

	//Capturamos el error.
	switch (error){

		case EAGAIN: //Se ha excedido el máximo número de cierres recursivos.

			printf("    Se produjo el error EAGAIN (Se ha excedido el máximo número de cierres recursivos).\n");

			break;

		case EINVAL: //La hebra actual tiene mayor prioridad que el semáforo.

			printf("    Se produjo el error EINVAL (La hebra actual tiene mayor prioridad que el semáforo).\n");

			break;

		case ENOTRECOVERABLE: //No se puede recuperar el estado del semáforo.

			printf("    Se produjo el error ENOTRECOVERABLE (No se puede recuperar el estado del semáforo).\n");

			break;

		case EBUSY:  //Semáforo cerrado.

			printf("    Se produjo el error EBUSY (Semáforo cerrado).\n");

			break;

		case EDEADLOCK:  //Interbloqueo.

			printf("    Se produjo el error EDEADLOCK (Interbloqueo).\n");

			break;

		default:  //Otro error no controlado.

			printf("    Se produjo el error %d\n", error);

			break;

	}

	return;

}



void error_en_unlock_mutex(int error){

	//Función para controlar los errores que se pueden producir al desbloquear un semáforo.

	//Capturamos el error.
	switch (error){

		case EPERM: //El tipo de semáforo requiere que la hebra sea su propietario, y no lo es.

			printf("    Se produjo el error EPERM (El tipo de semáforo requiere que la hebra sea su propietario, y no lo es).\n");

			break;

		default:  //Otro error no controlado.

			printf("    Se produjo el error %d\n", error);

			break;

	}

	return;

}



void error_en_init_mutex(int error){

	//Función para controlar los errores que se pueden producir al inicializar un semáforo.

	//Capturamos el error.
	switch (error){

		case EAGAIN: //El sistema no tiene recursos para inicializar el semáforo.

			printf("    (Hilo ppal.) Se produjo el error EAGAIN (Sin recursos para inicializar el semáforo).\n");

			break;

		case ENOMEM: //Memoria insuficiente para inicializar el semáforo

			printf("    (Hilo ppal.) Se produjo el error ENOMEM (Memoria insuficiente para inicialiar el semáforo).\n");

			break;

		case EPERM:  //El proceso no tiene privilegios para inicializar el semáforo.

			printf("    (Hilo ppal.) Se produjo el error EPERM (Sin privilegios para inicializar el semáforo).\n");

			break;

		case EINVAL:  //Los atributos enviados indican que se trata de un ' robust mutex ' pero no se ha configurado el atributo process-shared

			printf("    (Hilo ppal.) Se produjo el error EINVAL (Error en los atributos al indicar que se trata de un ' robust mutex ').\n");

			break;

	}

}



void error_en_destroy_mutex(int error){

	//Función para controlar los errores que se pueden producir al destruir un semáforo.

	//Capturamos el error.
	switch (error){

		case EBUSY: //El semáforo está cerrado.

			printf("    (Hilo ppal.) Se produjo el error EBUSY (El semáforo está cerrado).\n");

			break;

		case EINVAL:  //Semáforo no válido.

			printf("    (Hilo ppal.) Se produjo el error EINVAL (Semáforo no válido).\n");

			break;

	}

}

