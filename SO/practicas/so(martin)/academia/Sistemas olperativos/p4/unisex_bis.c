
//Sistemas Operativos
//Práctica 4. Ejercicio 2
//Programa: Aseo de la Universidad.
//          Sin espera activa.
//	    Cola única de llegada.
//          Aprovecha la capacidad máxima del baño.
//	    En caso de que haya una/un mujer/hombre en el baño da prioridad a las/los mujeres/hombres que estuvieran esperando.


#include <stdio.h>
#include <semaphore.h>
#include <errno.h>	//Códigos de error
#include <stdlib.h>


//Para controlar errores en los semáforos.
	void error_en_sem_init(int error);
	void error_en_sem_destroy(int error);
	void error_en_sem_wait(int error);
	void error_en_sem_post(int error);
//


char ocupado;		//Para saber si el baño está ocupado.

sem_t aseo;		//Para entrar al aseo.
sem_t critico;		//Para acceder a la sección crítica.

sem_t mujer;		//Para evitar la espera activa de las mujeres.
sem_t hombre;		//Para evitar la espera activa de los hombres.

int mujeres_espera;	//Mujeres que hay en espera de entrar al baño.
int hombres_espera;	//Hombres que hay en espera de entrar al baño.

int mujeres_dentro;	//Mujeres que hay en el baño.
int hombres_dentro;	//Hombres que hay en el baño.

int cierra_m;		//Para controlar que no pueden entrar las mujeres al baño.
int cierra_h;		//Para controlar que no pueden entrar los hombres al baño.

int libera_m;		//Para controlar que pueden entrar las mujeres al baño.
int libera_h;		//Para controlar que pueden entrar los hombres al baño.

int cierres_m;		//Para controlar las veces que no han podido entrar las mujeres al baño.
int cierres_h;		//Para controlar las veces que no han podido entrar los hombres al baño.


int que_libere_la_ultima;	//La última mujer permite el paso a los hombres.
int que_libere_el_ultimo;	//El último hombre permite el paso a las mujeres.


int turno;		//Para saber cuándo llega una mujer/hombre al baño



void * mujeres(void * parametro){

	//Mujeres que quieren entrar al aeso.

	//Declaración de variables.

	int cantidad;
	int numero;
	int mturno;
	int error;

	numero=*((int *)parametro);	//Número de la mujer.

	error=sem_wait(&critico);
	if(error!=0){
		error_en_sem_wait(error);
	}

		turno++;

		mturno=turno;	//Turno que ha cogido la mujer.

		mujeres_espera++;	//Hay una mujer más en espera de entrar al baño.

		printf("\nLlega la mujer %d", numero);

		if(ocupado=='N'){

			ocupado='S';			//El baño está ocupado.

			if(hombres_espera==0){

				libera_h=0;
				cierra_h=numero;	//Para controlar qué mujer cierra el baño a los hombres.
				cierres_h++;
				error=sem_wait(&hombre);	//Para que no entren los hombres.
				if(error!=0){
					error_en_sem_wait(error);
				}


			}else if(libera_h==1){

			  	libera_h=0;
				cierres_m++;
			  	error=sem_wait(&mujer);	//Para que no entren las mujeres.
				if(error!=0){
					error_en_sem_wait(error);
				}

			}

		}

	error=sem_post(&critico);
	if(error!=0){
		error_en_sem_post(error);
	}




		error=sem_wait(&mujer);
		if(error!=0){
			error_en_sem_wait(error);
		}


	error=sem_wait(&aseo);
	if(error!=0){
		error_en_sem_wait(error);
	}


		error=sem_post(&mujer);
		if(error!=0){
			error_en_sem_post(error);
		}



		printf(" \n--> M   Ha entrado al baño la mujer %d que cogió el turno %d",numero,mturno);
		
		error=sem_wait(&critico);
		if(error!=0){
			error_en_sem_wait(error);
		}


			mujeres_dentro=mujeres_dentro+1;	//Hay una mujer más dentro del baño

			mujeres_espera--;	//Hay una mujer menos esperando

			if(hombres_dentro!=0){		//Controlamos que no puede haber hombres en el baño.

				printf("\nHay hombres ***************************************\n");
				sleep(4);

			}


		error=sem_post(&critico);
		if(error!=0){
			error_en_sem_post(error);
		}


		printf(" \n--> M       Sale del baño la mujer %d", numero);

	error=sem_post(&aseo);
	if(error!=0){
		error_en_sem_post(error);
	}



	error=sem_wait(&critico);
	if(error!=0){
		error_en_sem_wait(error);
	}


		mujeres_dentro=mujeres_dentro-1;	//Hay una mujer menos en el baño

		if(mujeres_dentro==0 && mujeres_espera==0){
			
			if( (hombres_espera!=0 && cierres_h>0) ||

			    ((numero==cierra_h || que_libere_la_ultima) && cierres_h>0)

                          ){

				cierres_h--;

				ocupado='N';		//El baño está libre
				libera_h=1;

				if((numero==cierra_h || que_libere_la_ultima) && cierres_h>0){
					que_libere_la_ultima=0;
				}

				error=sem_post(&hombre);	//Para que entren los hombres si están a la espera.
				if(error!=0){
					error_en_sem_post(error);
				}


			}

		}else{

			if(numero==cierra_h){

				que_libere_la_ultima=1;

			}

		}

	error=sem_post(&critico);
	if(error!=0){
		error_en_sem_post(error);
	}


	//Finalización correcta y no devuelve nada.
	pthread_exit(NULL);

}

void * hombres(void * parametro){

	//Hombres que quieren entrar al aeso.

	//Declaración de variables.

	int cantidad;
	int numero;
	int hturno;

	int error;


	numero=*((int *)parametro);

	error=sem_wait(&critico);
	if(error!=0){
		error_en_sem_wait(error);
	}


		turno++;

		hturno=turno;

		hombres_espera++;

		printf("\nLlega el hombre %d", numero);

		if(ocupado=='N'){

			ocupado='S';			//El baño está ocupado.

			if(mujeres_espera==0){

				libera_m=0;
				cierra_m=numero;	//Para controlar qué hombre cierra el baño a las mujeres.
				cierres_m++;
				error=sem_wait(&mujer);	//Para que no entren las mujeres.
				if(error!=0){
					error_en_sem_wait(error);
				}

			}else if(libera_m==1){

			 	libera_m=0;
				cierres_h++;
			 	error=sem_wait(&hombre);	//Para que no entren los hombres.
				if(error!=0){
					error_en_sem_wait(error);
				}

			}

		}

	error=sem_post(&critico);
	if(error!=0){
		error_en_sem_post(error);
	}




		error=sem_wait(&hombre);
		if(error!=0){
			error_en_sem_wait(error);
		}


	error=sem_wait(&aseo);
	if(error!=0){
		error_en_sem_wait(error);
	}


		error=sem_post(&hombre);
		if(error!=0){
			error_en_sem_post(error);
		}


		printf(" \n-->   H   Ha entrado al baño el hombre %d que cogió el turno %d",numero,hturno);

		error=sem_wait(&critico);
		if(error!=0){
			error_en_sem_wait(error);
		}


			hombres_espera--;

			hombres_dentro=hombres_dentro+1;

			if(mujeres_dentro!=0){

				printf("\nHay mujeres ***************************************\n");
				sleep(4);

			}

		error=sem_post(&critico);
		if(error!=0){
			error_en_sem_post(error);
		}


		printf(" \n-->   H       Sale del baño el hombre %d", numero);

	error=sem_post(&aseo);
	if(error!=0){
		error_en_sem_post(error);
	}



	error=sem_wait(&critico);
	if(error!=0){
		error_en_sem_wait(error);
	}

		hombres_dentro=hombres_dentro-1;

		if(hombres_dentro==0 && hombres_espera==0){

			if( (mujeres_espera!=0 && cierres_m>0 ) ||

			    ((numero==cierra_m || que_libere_el_ultimo) && cierres_m>0)

			  ){

				cierres_m--;

				ocupado='N';
				libera_m=1;

				if((numero==cierra_m || que_libere_el_ultimo) && cierres_m>0){
					que_libere_el_ultimo=0;
				}

				error=sem_post(&mujer);	//Para que entren las mujeres si están a la espera.
				if(error!=0){
					error_en_sem_post(error);
				}

			}

		}else{

			if(numero==cierra_m){

				que_libere_el_ultimo=1;

			}

		}

	error=sem_post(&critico);
	if(error!=0){
		error_en_sem_post(error);
	}


	//Finalización correcta y no devuelve nada.
	pthread_exit(NULL);

}


int main(){

	//Declaración de variables.

	pthread_t hebras[500];
	int datos_hebras[500];

	int i;
	int error;

	int num_hombres;
	int num_mujeres;


	error=sem_init(&critico, 0, 1);
	if(error!=0){
		error_en_sem_init(error);
	}

	error=sem_init(&hombre, 0, 1);
	if(error!=0){
		error_en_sem_init(error);
	}

	error=sem_init(&mujer, 0, 1);
	if(error!=0){
		error_en_sem_init(error);
	}

	error=sem_init(&aseo, 0, 3);
	if(error!=0){
		error_en_sem_init(error);
	}


	ocupado='N';

	num_hombres=0;
	num_mujeres=0;

	libera_h=0;
	libera_m=0;

	hombres_espera=0;
	mujeres_espera=0;

	hombres_dentro=0;
	mujeres_dentro=0;

	cierra_h=0;
	cierra_m=0;

	cierres_h=0;
	cierres_m=0;

	que_libere_el_ultimo=0;
	que_libere_la_ultima=0;

	turno=0;

	printf("\n\n");

	//Creamos las hebras: Mujeres / Hombres.
	for(i=0;i<380;i++){

		if(i%2==0){	//ok

			datos_hebras[i]=++num_mujeres;

			//Mujeres
			error = pthread_create( &(hebras[i]), NULL, (void *) mujeres, &datos_hebras[i]);

		}else{

			datos_hebras[i]=++num_hombres;

			//Hombres
			error = pthread_create( &(hebras[i]), NULL, (void *) hombres, &datos_hebras[i]);

		}
		
		//Capturamos los errores que se pueden producir al crear una hebra.
		switch (error){

			case 0: //Correcto.

				//printf("    (Hilo ppal.) Se ha creado la hebra ..: %lu\n", (unsigned long int)hebras[i]);

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
	for(i=0;i<380;i++){

		error = pthread_join(hebras[i], NULL);

		//Capturamos los errores que se pueden producir al recoger (join) una hebra.
		switch (error){

			case 0: //Correcto.

				//printf("    (Hilo ppal.) Terminó correctamente la hebra ..: %lu\n", (unsigned long int)hebras[i]);

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

	printf("\n Mujeres en espera ..: %d    Hombres en espera ..: %d", mujeres_espera, hombres_espera);

	printf("    (Hilo ppal.) Finalización correcta.\n");

	printf("\n\n");

	error=sem_destroy(&critico);
	if(error!=0){
		error_en_sem_destroy(error);
	}

	error=sem_destroy(&hombre);
	if(error!=0){
		error_en_sem_destroy(error);
	}

	error=sem_destroy(&mujer);
	if(error!=0){
		error_en_sem_destroy(error);
	}

	error=sem_destroy(&aseo);
	if(error!=0){
		error_en_sem_destroy(error);
	}


	//Finalización correcta y no devuelve nada.
	pthread_exit(NULL);
}



void error_en_sem_wait(int error){

	//Función para controlar los errores que se pueden producir al bloquear un semáforo.

	//Capturamos el error.
	switch (error){

		case EAGAIN: //El semáforo estaba bloqueado.

			printf("    Se produjo el error EAGAIN (El semáforo estaba bloqueado).\n");

			break;

		case EDEADLOCK:  //Interbloqueo.

			printf("    Se produjo el error EDEADLOCK (Interbloqueo).\n");

			break;

		case EINTR:  //Se recibió una señal que interrumpió la solicitud.

			printf("    Se produjo el error EINTR (Se recibió una señal que interrumpió la solicitud).\n");

			break;

		case EINVAL: //Semáforo no válido.

			printf("    Se produjo el error EINVAL (Semáforo no válido).\n");

			break;

		default:  //Otro error no controlado.

			printf("    Se produjo el error %d\n", error);

			break;

	}

	sleep(10);

	return;

}



void error_en_sem_post(int error){

	//Función para controlar los errores que se pueden producir al desbloquear un semáforo.

	//Capturamos el error.
	switch (error){

		case EINVAL: //Semáforo no válido.

			printf("    Se produjo el error EINVAL (Semáforo no válido).\n");

			break;

		default:  //Otro error no controlado.

			printf("    Se produjo el error %d\n", error);

			break;

	}

	sleep(10);

	return;

}



void error_en_sem_init(int error){

	//Función para controlar los errores que se pueden producir al inicializar un semáforo.

	//Capturamos el error.
	switch (error){

		case EINVAL:  //El parámetro indicado excede el valor máximo del tamaño del semáforo.

			printf("    (Hilo ppal.) Se produjo el error EINVAL (Se ha excedido el tamaño máximo del semáforo).\n");

			break;

		case ENOSPC:  //Falta de recursos o se ha alcanzado el máximo de semáforos.

			printf("    (Hilo ppal.) Se produjo el error ENOSPC (Falta de recursos o se ha alcanzado el máximo de semáforos).\n");

			break;

		case EPERM:  //El proceso no tiene los recursos necesarios para inicializar el semáforo.

			printf("    (Hilo ppal.) Se produjo el error EPERM (Falta de recursos para inicializar el semáforo).\n");

			break;

		default:  //Otro error no controlado.

			printf("    Se produjo el error %d\n", error);

			break;

	}

	sleep(10);

	return;

}



void error_en_sem_destroy(int error){

	//Función para controlar los errores que se pueden producir al destruir un semáforo.

	//Capturamos el error.
	switch (error){

		case EBUSY: //El semáforo está cerrado y hay procesos bloqueados en él.

			printf("    (Hilo ppal.) Se produjo el error EBUSY (El semáforo está cerrado y hay procesos bloqueados en él).\n");

			break;

		case EINVAL:  //Semáforo no válido.

			printf("    (Hilo ppal.) Se produjo el error EINVAL (Semáforo no válido).\n");

			break;

		default:  //Otro error no controlado.

			printf("    Se produjo el error %d\n", error);

			break;

	}

	sleep(10);

	return;

}


