#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>

// 1 Lector, N copiadores que pueden escribir concurrentemente.

#define TAM_BUFFER 1024

char buffer[TAM_BUFFER];	      //Buffer intermedio de comunicación.
int n_copias_terminadas;        //Numero de copiadores que ya han terminado de leer del buffer.
int bytes_leidos;	              //Bytes leidos. Si no es 0, entonces el lector ha terminado el fichero.
int n_copias;			            	//Número de copias que se van a realizar.

pthread_mutex_t escritor;	      //Mutex.
pthread_cond_t seguirleyendo;	  //Para despertar a la hebra que lee el fichero.
pthread_cond_t seguircopiando;	//Para despertar a las hebras que hacen las copias del fichero.

void check_init_mutex(int error);
void check_destroy_mutex(int error);
void check_lock_mutex(int error);
void check_unlock_mutex(int error);
void check_pthread_create(int error);
void check_pthread_join(int error);

void* lector(void * parametro)
{
	char nombrefichero[FILENAME_MAX];
	strcpy(nombrefichero, (char *)parametro);

	FILE* fichero = fopen(nombrefichero,"r");

	if(fichero==NULL) {
		printf("Error: no se pudo abrir el fichero de lectura %s\n", nombrefichero);
		exit(-1);
	}

	do{
    check_lock_mutex(pthread_mutex_lock(&escritor));
		
		bytes_leidos = fread(buffer,sizeof(char),TAM_BUFFER,fichero);
		
		if(bytes_leidos > 0)
		{
   		//Despierta a los hilos que copian del buffer a cada fichero copia.
			pthread_cond_broadcast(&seguircopiando);
			
			//Espera no activa para que todos los hilos copiadores terminen de leer y copiar el contenido del buffer.
			pthread_cond_wait(&seguirleyendo, &escritor);
			
			n_copias_terminadas = 0; // Reiniciamos el contador de copias
		}
		else
		{
			//Se ha terminado de leer el fichero.
			//Despierta a los hilos copiadores para que cierren sus ficheros y finalicen.
			pthread_cond_broadcast(&seguircopiando);
		}			

		check_unlock_mutex(pthread_mutex_unlock(&escritor));
		
	}while(bytes_leidos > 0);

	fclose(fichero);

	//Finalización correcta y no devuelve nada.
	pthread_exit(NULL);
}

void* copiador(void * parametro)
{
	char nombrefichero[FILENAME_MAX];
	strcpy(nombrefichero, (char *)parametro);
	
	FILE* fichero = fopen(nombrefichero,"w");

	if(fichero==NULL) {
		printf("Error: no se pudo abrir el fichero de escritura %s\n", nombrefichero);
		exit(-1);
	}

	do{
		check_lock_mutex(pthread_mutex_lock(&escritor));

    while(!bytes_leidos > 0)
  	  pthread_cond_wait(&seguircopiando, &escritor); //Espera no activa para que el lector termine de rellenar el buffer.

    check_unlock_mutex(pthread_mutex_unlock(&escritor)); // Libera el mutex para que todos los copiadores puedan escribir en paralelo

    if(bytes_leidos > 0)
    {
		  //Volcamos el contenido del buffer en el fichero. Esta copia es concurrente a los múltiples hilos copiadores.
		  fwrite(buffer, sizeof(char), bytes_leidos,fichero);
		  fflush(fichero);

      check_lock_mutex(pthread_mutex_lock(&escritor)); // Bloqueamos de nuevo el mutex para incrementar el número de copias terminadas
      
		  n_copias_terminadas++;

		  if (n_copias_terminadas == n_copias)
			  pthread_cond_signal(&seguirleyendo);	//Despierta al lector para informarle de que todos los copiadores han terminado.
			  
		  pthread_cond_wait(&seguircopiando, &escritor); // Espero a que el lector me de paso para seguir.
		  
  		check_unlock_mutex(pthread_mutex_unlock(&escritor));
		}

	}while(bytes_leidos > 0);

	fclose(fichero);

	//Finalización correcta y no devuelve nada.
	pthread_exit(NULL);
}

int main(int argc, char **argv)
{
	pthread_t* hebras;
	char** fichero_hebras;
	
	char nombrefichero[FILENAME_MAX];
	char auxnombrefichero[FILENAME_MAX];
	FILE *fichero;

	int i;

	//Controlamos los parámetros
	if(argc != 3){
		printf("Parámetros incorrectos\n");
		printf("Sintaxis correcta: %s <nombrefichero> <numcopias>\n", argv[0]);
		exit(-1);
	}
	
	strcpy(nombrefichero, argv[1]);
	
	if(access(nombrefichero, F_OK ) == -1)
	{
		printf("Error: el fichero %s no existe\n",nombrefichero);
		exit(-1);
	}

	n_copias = atoi(argv[2]);

  hebras = (pthread_t*)malloc((n_copias+1)*sizeof(pthread_t));
  fichero_hebras = (char**)malloc(n_copias*sizeof(char*));
  
  for(i = 0; i < n_copias; i++)
    fichero_hebras[i] = (char*)malloc(FILENAME_MAX*sizeof(char));
  
	strncat(auxnombrefichero, nombrefichero, strlen(nombrefichero)-strlen((rindex(nombrefichero,'.'))));

	//Inicializamos los mutex
	check_init_mutex(pthread_mutex_init(&escritor,NULL));

	//Inicializamos las variables de condición
	pthread_cond_init(&seguirleyendo,NULL);
	pthread_cond_init(&seguircopiando,NULL);

	//Creamos las hebras: 1 Lector / n Escritores.
  check_pthread_create(pthread_create(&(hebras[0]), NULL, (void *) lector, (void *) nombrefichero));
	
	for(i = 0; i < n_copias; i++)
	{
		sprintf(fichero_hebras[i],"%s%d%s", auxnombrefichero, i, rindex(nombrefichero,'.'));
		check_pthread_create(pthread_create(&(hebras[i+1]), NULL, (void *) copiador, (void *) fichero_hebras[i]));
	}

	//Esperamos a la finalización de las hebras (1 lector y n_copias escritores).
	for(i = 0; i <= n_copias; i++)
		check_pthread_join(pthread_join(hebras[i], NULL));

	//Liberamos el mutex.
	check_destroy_mutex(pthread_mutex_destroy(&escritor));

	//Liberamos las variables de condición.
	pthread_cond_destroy(&seguirleyendo);
	pthread_cond_destroy(&seguircopiando);

  //Liberamos memoria dinámica.	
	for(i = 0; i < n_copias; i++)
    free(fichero_hebras[i]);
    
	free(fichero_hebras);
	free(hebras);
	
	exit(1);
}

void check_lock_mutex(int error)
{
	switch (error)
	{
    case 0:      // Ningún error
      break;
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
		default:      //Otro error no controlado.
			printf("    Se produjo el error %d\n", error);
			break;
	}
}

void check_unlock_mutex(int error)
{
	switch (error)
	{
    case 0:      // Ningún error
      break;
		case EPERM:  //El tipo de semáforo requiere que la hebra sea su propietario, y no lo es.
			printf("    Se produjo el error EPERM (El tipo de semáforo requiere que la hebra sea su propietario, y no lo es).\n");
			break;
		default:     //Otro error no controlado.
			printf("    Se produjo el error %d\n", error);
			break;
	}
}

void check_init_mutex(int error)
{
	switch (error)
	{
		case 0:      // Ningún error
      break;
    case EAGAIN: //El sistema no tiene recursos para inicializar el semáforo.
			printf("    (Hilo ppal.) Se produjo el error EAGAIN (Sin recursos para inicializar el semáforo).\n");
			break;
		case ENOMEM: //Memoria insuficiente para inicializar el semáforo
			printf("    (Hilo ppal.) Se produjo el error ENOMEM (Memoria insuficiente para inicialiar el semáforo).\n");
			break;
		case EPERM:  //El proceso no tiene privilegios para inicializar el semáforo.
			printf("    (Hilo ppal.) Se produjo el error EPERM (Sin privilegios para inicializar el semáforo).\n");
			break;
		case EINVAL: //Los atributos enviados indican que se trata de un ' robust mutex ' pero no se ha configurado el atributo process-shared
			printf("    (Hilo ppal.) Se produjo el error EINVAL (Error en los atributos al indicar que se trata de un ' robust mutex ').\n");
			break;
	}
}

void check_destroy_mutex(int error)
{
	switch (error)
	{
    case 0:      // Ningún error
      break;
		case EBUSY:  //El semáforo está cerrado.
			printf("    (Hilo ppal.) Se produjo el error EBUSY (El semáforo está cerrado).\n");
			break;
		case EINVAL: //Semáforo no válido.
			printf("    (Hilo ppal.) Se produjo el error EINVAL (Semáforo no válido).\n");
			break;
	}
}

void check_pthread_create(int error) 
{
  switch (error)
  {
			case 0:      // Ningún error
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

void check_pthread_join(int error) 
{
  switch (error)
  {
			case 0:      // Ningún error
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
