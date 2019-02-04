
//Sistemas Operativos
//Práctica 3. Ejercicio 5
//Programa que crea N hebras, 1 para leer el fichero y N-1 para hacer las copias concurrentes del fichero.
//Versión c: Cada hebra que hace una copia del fichero despierta al escritor, y éste continúa escribiendo sólo cuando todas las hebras han terminado de leer del buffer.
//	     Con indicador de progreso de cada copia.


#include <stdio.h>
#include <pthread.h>
#include <errno.h>	//Códigos de error
#include <string.h>	//Cadenas
#include <stdlib.h>

#include <curses.h>

#define TAM_BUFFER 1024		//Tamaño del buffer.


pthread_mutex_t pantalla;	//Semáforo binario.

pthread_mutex_t escritor;	//Semáforo binario.

pthread_cond_t seguirleyendo;	//Para despertar a la hebra que lee el fichero.
pthread_cond_t seguircopiando;	//Para despertar a las hebras que hacen las copias del fichero.


//Estructura de datos que se le manda a cada hebra.
struct Datos{

	char nombreFichero[FILENAME_MAX];
	int proceso;
	long totalBytes;

};


int n_hebras;				//Número de copias que se van a realizar.


//Variables sección crítica
	char buffer[TAM_BUFFER];	//Buffer intermedio de comunicación.
	int leidos;			//Bytes que se han leído en la última operación de lectura.
	int terminaleer;		//Para controlar si el el proceso que lee el fichero original ha terminado de leer.
	int estado;			//0 -> el lector no está produciendo.  1 -> el lector está produciendo.
	int procesosterminados;		//Procesos que ya han terminado de leer del buffer.
//



void dibuja_marco(int desdefil, int hastafil, int desdecol, int hastacol);
int dibujaProgreso(int progreso, long bProcesados, long bTotal, int fila, int columna);


void * f_lector(void * parametro){

	//Función lector: lee del fichero original y lo almacena en el buffer.

	//Declaración de variables.

	FILE *fichero;

	struct Datos datos;

	int progreso;			//Para el progreso en pantalla
	long bytesProcesados;
	int fila;
	int columna;

	datos=*(struct Datos *)parametro;

	progreso=0;
	bytesProcesados=0;
	fila=1;
	columna=45;

	fichero=fopen(datos.nombreFichero,"rb");

	if(fichero==NULL){

		printf("\n      Error!! No se pudo abrir el fichero %s .\n", datos.nombreFichero);
		exit(-1);

	}

	pthread_mutex_lock(&pantalla);
		mvprintw(fila+1,columna-37,"Leyendo fichero ..: %s", datos.nombreFichero);
	pthread_mutex_unlock(&pantalla);


	do{

		pthread_mutex_lock(&escritor);

		//En cada lectura se leen TAM_BUFFER bytes
		leidos=fread(buffer,sizeof(char),TAM_BUFFER,fichero);

		if(leidos>0){

			estado=0;	//No produciendo.

			bytesProcesados=bytesProcesados+leidos;
			progreso=dibujaProgreso(progreso,bytesProcesados,datos.totalBytes,fila,columna);

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

		pthread_mutex_unlock(&escritor);

	}while(leidos>0);

	fclose(fichero);

	//Informamos a los procesos de que se ha terminado de leer.
	pthread_mutex_lock(&escritor);

		estado=0;	//No produciendo.
		terminaleer=1;
		pthread_cond_broadcast(&seguircopiando);	//Despierta a los procesos que copian del buffer a cada fichero copia.

	pthread_mutex_unlock(&escritor);

	//Finalización correcta y no devuelve nada.
	pthread_exit(NULL);

}

void * f_copiador(void * parametro){

	//Función copiador: lee el contenido del buffer que el lector ha rellenado.

	//Declaración de variables.

	FILE *fichero;

	struct Datos datos;

	int finlectura;

	int progreso;			//Para el progreso en pantalla
	long bytesProcesados;
	int fila;
	int columna;

	datos=*(struct Datos *)parametro;

	finlectura=0;

	progreso=0;
	bytesProcesados=0;
	columna=15;
	fila=3+(datos.proceso*3);
	
	fichero=fopen(datos.nombreFichero, "wb");

	if(fichero==NULL){

		printf("\n      Error!! No se pudo abrir el fichero %s .\n", datos.nombreFichero);
		exit(-1);

	}

	pthread_mutex_lock(&pantalla);
		mvprintw(fila+1,columna-10,"Copia %d", datos.proceso);
		mvprintw(fila+1,columna+24,"Creando fichero ..: %s", datos.nombreFichero);
	pthread_mutex_unlock(&pantalla);


	do{

		pthread_mutex_lock(&escritor);

		while(estado==1){

			pthread_cond_wait(&seguircopiando, &escritor); //Espera no activa para que el lector termine de rellenar el buffer.

		}

		//Volcamos el contenido del buffer en el fichero.
		fwrite(buffer, sizeof(char), leidos,fichero);
		fflush(fichero);

		bytesProcesados=bytesProcesados+leidos;

		progreso=dibujaProgreso(progreso,bytesProcesados,datos.totalBytes,fila,columna);

		procesosterminados++;

		pthread_cond_broadcast(&seguirleyendo);	//Despierta al escritor para informarle de que un proceso ha terminado.

		pthread_cond_wait(&seguircopiando, &escritor);	//Espera no activa para que el lector cargue el buffer con los nuevos datos.

		if(terminaleer==1){

			//El lector ha terminado de leer. No hay más datos para procesar.
			finlectura=1;

		}

		pthread_mutex_unlock(&escritor);

		}while(finlectura==0);

		//Cerramos el fichero.
		fclose(fichero);
	
	//Finalización correcta y no devuelve nada.
	pthread_exit(NULL);

}


int main(int argc, char **argv){

	//Declaración de variables.

	pthread_t hebras[10];			//Para almacenar las hebras.
	struct Datos datos_hebras[10];		//Para almacenar los datos que le corresponden a cada hebra.

	char nombrefichero[FILENAME_MAX];
	char auxnombrefichero[FILENAME_MAX];
	long totalBytes;

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

		//Obtenemos el tamaño del fichero.
		fseek(fichero, 0L, SEEK_END);
		totalBytes=ftell(fichero);
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
	pthread_mutex_init(&escritor,NULL);
	pthread_mutex_init(&pantalla,NULL);


	//Inicializamos las variables de condición.
	pthread_cond_init(&seguirleyendo,NULL);
	pthread_cond_init(&seguircopiando,NULL);


	initscr();		//Inicia lcurses

	curs_set(0);		//Oculta el cursor

	noecho();		//Desactiva echo de la tecla pulsada


	dibuja_marco(0,4,0,79);
	dibuja_marco(5,23,0,79);


	//Creamos las hebras: 1 Lector / n Escritores.
	for(i=0;i<=n_hebras;i++){

		datos_hebras[i].proceso=i;
		datos_hebras[i].totalBytes=totalBytes;

		if(i==0){

			//Escritor
			strcpy(datos_hebras[i].nombreFichero,nombrefichero);
			error = pthread_create( &(hebras[i]), NULL, (void *) f_lector, (void *)&datos_hebras[i]);

		}else{

			//Lectores
			sprintf(datos_hebras[i].nombreFichero,"%s%d%s",auxnombrefichero,i-1,rindex(nombrefichero,'.'));
			error = pthread_create( &(hebras[i]), NULL, (void *) f_copiador, (void *)&datos_hebras[i]);

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
	for(i=0;i<=n_hebras;i++){

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

	sleep(4);


	//Restaura el cursor
	curs_set(1);

	//Activa echo de la tecla pulsada
	echo();

	//Finaliza lcurses
	endwin();


	//Liberamos los semáforos.
	pthread_mutex_destroy(&escritor);
	pthread_mutex_destroy(&pantalla);


	//Liberamos las variables de condición.
	pthread_cond_destroy(&seguirleyendo);
	pthread_cond_destroy(&seguircopiando);

	//Finalización correcta y no devuelve nada.
	pthread_exit(NULL);
}



void dibuja_marco(int desdefil, int hastafil, int desdecol, int hastacol){

	//Declaración de variables

	int i;
	int j;


	//Dibuja un recuadro con las coordenadas recibidas.

	mvwaddch(stdscr,desdefil,desdecol,ACS_ULCORNER);
	mvwaddch(stdscr,desdefil,hastacol,ACS_URCORNER);

	for(j=desdecol+1;j<hastacol;j++){

		mvwaddch(stdscr,desdefil,j,ACS_HLINE);
		mvwaddch(stdscr,hastafil,j,ACS_HLINE);

	}

	for(i=desdefil+1;i<hastafil;i++){

		mvwaddch(stdscr,i,desdecol,ACS_VLINE);
		mvwaddch(stdscr,i,hastacol,ACS_VLINE);

	}

	mvwaddch(stdscr,hastafil,desdecol,ACS_LLCORNER);
	mvwaddch(stdscr,hastafil,hastacol,ACS_LRCORNER);

	return;

}


int dibujaProgreso(int progreso, long bProcesados, long bTotal, int fila, int columna){

	//Declaración de variables.

	int nuevoProgreso;	//Progreso realizado sobre el total
	int i;

	pthread_mutex_lock(&pantalla);

	if(progreso==0){

		//Inicialmente dibujamos el marco

		dibuja_marco(fila,fila+2,columna,columna+21);
		mvprintw(fila,columna+1," % Realizado ");
	
	}

	wattrset(stdscr,A_REVERSE);


	//Calculamos el nuevo progreso realizado
	nuevoProgreso=(int)(((bProcesados*100)/bTotal)/5);


	//Continuamos el progreso por donde estaba
	for(i=progreso;i<nuevoProgreso;i++){

		mvprintw(fila+1,(columna+1)+i," ");

	}

	mvprintw(fila+1,columna+9,"%d",(int)((bProcesados*100)/bTotal));

	wattrset(stdscr,A_NORMAL);
	wrefresh(stdscr);


	//Retornamos el nuevo progreso ya alcanzado

	pthread_mutex_unlock(&pantalla);

	return (nuevoProgreso);

}

