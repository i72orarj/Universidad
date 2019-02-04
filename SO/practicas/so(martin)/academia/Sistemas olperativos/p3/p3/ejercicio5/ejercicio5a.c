
//Sistemas Operativos
//Práctica 3. Ejercicio 5
//Programa que crea N hebras, 1 para leer el fichero y N-1 para hacer las copias concurrentes de dicho fichero.
//Versión a: Cada hebra que hace una copia del fichero despierta al escritor, y éste continúa escribiendo sólo cuando todas las hebras han terminado de leer del buffer.


#include <stdio.h>
#include <pthread.h>
#include <errno.h>	//Códigos de error
#include <string.h>	//Cadenas
#include <stdlib.h>

#define TAM_BUFFER 1024		//Tamaño del buffer.


//Para controlar errores en los semáforos.
	void error_en_destroy_mutex(int error);
	void error_en_init_mutex(int error);
	void error_en_unlock_mutex(int error);
	void error_en_lock_mutex(int error);
//



pthread_mutex_t escritor;	//Semáforo binario.

pthread_cond_t seguirleyendo;	//Para despertar a la hebra que lee el fichero.
pthread_cond_t seguircopiando;	//Para despertar a las hebras que hacen las copias del fichero.


int n_hebras;				//Número de copias que se van a realizar.


//Variables sección crítica
	char buffer[TAM_BUFFER];	//Buffer intermedio de comunicación.
	int leidos;			//Bytes que se han leído en la última operación de lectura.
	int terminaleer;		//Para controlar si el el proceso que lee el fichero original ha terminado de leer.
	int estado;			//0 -> el lector no está produciendo.  1 -> el lector está produciendo.
	int procesosterminados;		//Procesos que ya han terminado de leer del buffer.
//


void * f_lector(void * parametro){

	//Función lector: lee del fichero original y lo almacena en el buffer.

	//Declaración de variables.

	FILE *fichero;

	char nombrefichero[FILENAME_MAX];

	int error;

	strcpy(nombrefichero, (char *)parametro);

	fichero=fopen(nombrefichero,"rb");

	if(fichero==NULL){

		printf("\n      Error!! No se pudo abrir el fichero %s .\n", nombrefichero);
		exit(-1);

	}

	do{

		error=pthread_mutex_lock(&escritor);
		if(error!=0){

			//Se produjo un error.
			error_en_lock_mutex(error);

		}


		//En cada lectura se leen TAM_BUFFER bytes
		leidos=fread(buffer,sizeof(char),TAM_BUFFER,fichero);

		if(leidos>0){

			estado=0;	//No produciendo.

			pthread_cond_broadcast(&seguircopiando);	//Despierta a los procesos que copian del buffer a cada fichero copia.

			while(procesosterminados!=(n_hebras)){

				//Espera no activa para que todos los procesos terminen de leer el contenido del buffer.
				pthread_cond_wait(&seguirleyendo, &escritor);

			}

			procesosterminados=0;

			estado=1;	//Produciendo.

		}else{

			//Se ha terminado de leer el fichero.
			terminaleer=1;

		}			

		error=pthread_mutex_unlock(&escritor);
		if(error!=0){

			//Se produjo un error.
			error_en_unlock_mutex(error);

		}


	}while(leidos>0);

	fclose(fichero);

	//Informamos a los procesos de que se ha terminado de leer.
	error=pthread_mutex_lock(&escritor);

		if(error!=0){

			//Se produjo un error.
			error_en_lock_mutex(error);

		}

		estado=0;	//No produciendo.
		terminaleer=1;
		pthread_cond_broadcast(&seguircopiando);	//Despierta a los procesos que copian del buffer a cada fichero copia.

	error=pthread_mutex_unlock(&escritor);
	if(error!=0){

		//Se produjo un error.
		error_en_unlock_mutex(error);

	}


	//Finalización correcta y no devuelve nada.
	pthread_exit(NULL);

}

void * f_copiador(void * parametro){

	//Función copiador: lee el contenido del buffer que el lector ha rellenado.

	//Declaración de variables.

	FILE *fichero;

	char nombrefichero[FILENAME_MAX];

	int error;

	int finlectura;

	finlectura=0;

	strcpy(nombrefichero, (char *)parametro);
	
	fichero=fopen(nombrefichero, "wb");

	if(fichero==NULL){

		printf("\n      Error!! No se pudo abrir el fichero %s .\n", nombrefichero);
		exit(-1);

	}

	printf("\nCreando el fichero %s\n", nombrefichero);
	
	do{

		error=pthread_mutex_lock(&escritor);
		if(error!=0){

			//Se produjo un error.
			error_en_lock_mutex(error);

		}


		while(estado==1){

			pthread_cond_wait(&seguircopiando, &escritor); //Espera no activa para que el lector termine de rellenar el buffer.

		}

		//Volcamos el contenido del buffer en el fichero.
		fwrite(buffer, sizeof(char), leidos,fichero);
		fflush(fichero);

		procesosterminados++;

		pthread_cond_broadcast(&seguirleyendo);	//Despierta al escritor para informarle de que un proceso ha terminado.

		pthread_cond_wait(&seguircopiando, &escritor);	//Espera no activa para que el lector cargue el buffer con los nuevos datos.

		if(terminaleer==1){

			//El lector ha terminado de leer. No hay más datos para procesar.
			finlectura=1;

		}

		error=pthread_mutex_unlock(&escritor);
		if(error!=0){

			//Se produjo un error.
			error_en_unlock_mutex(error);

		}


		}while(finlectura==0);

		//Cerramos el fichero.
		fclose(fichero);

	printf("\nEl fichero %s ya ha sido creado.\n", nombrefichero);

	//Finalización correcta y no devuelve nada.
	pthread_exit(NULL);

}


int main(int argc, char **argv){

	//Declaración de variables.

	pthread_t hebras[10];			//Para almacenar las hebras.
	char fichero_hebra[10][FILENAME_MAX];	//Para almacenar el fichero de copia que le corresponde a cada hebra.

	char nombrefichero[FILENAME_MAX];
	char auxnombrefichero[FILENAME_MAX];

	FILE *fichero;

	int i;
	int error;

	printf("\n\n");

	//Controlamos los parámetros
	if(argc!=3){

		printf("Parámetros incorrectos.\n");
		printf("Sintaxis correcta: %s <nombrefichero> <numcopias>\n", argv[0]);
		printf("Se para la ejecución del programa.\n");
		exit(-1);

	}

	strcpy(nombrefichero, argv[1]);

	//Comprobamos que el fichero existe.
	fichero=fopen(nombrefichero,"rb");
	if(fichero!=NULL){

		fclose(fichero);

	}else{

		printf("\nError!! El fichero %s no existe.\n",nombrefichero);
		printf("\n\n");
		exit(-1);

	}

	n_hebras=atoi(argv[2]);

	strncat(auxnombrefichero, nombrefichero,strlen(nombrefichero)-strlen((rindex(nombrefichero,'.'))));

	//Valores inciales
	terminaleer=0;		//No se ha terminado de leer.
	procesosterminados=0;	//Ningún proceso ha terminado de leer.
	estado=1;		//El proceso que lee el fichero original está leyendo.
	

	//Inicializamos los semáforos.
	error=pthread_mutex_init(&escritor,NULL);
	if(error!=0){

		//Se produjo un error.
		error_en_init_mutex(error);

	}


	//Inicializamos las variables de condición.
	pthread_cond_init(&seguirleyendo,NULL);
	pthread_cond_init(&seguircopiando,NULL);


	//Creamos las hebras: 1 Lector / n Escritores.
	for(i=0;i<=n_hebras;i++){

		if(i==0){

			//Escritor
			error = pthread_create( &(hebras[i]), NULL, (void *) f_lector, (void *)nombrefichero);

		}else{

			//Lectores
			sprintf(fichero_hebra[i],"%s%d%s",auxnombrefichero,i-1,rindex(nombrefichero,'.'));
			error = pthread_create( &(hebras[i]), NULL, (void *) f_copiador, (void *)fichero_hebra[i]);

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
	for(i=0;i<=n_hebras;i++){

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


	//Liberamos las variables de condición.
	pthread_cond_destroy(&seguirleyendo);
	pthread_cond_destroy(&seguircopiando);

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


