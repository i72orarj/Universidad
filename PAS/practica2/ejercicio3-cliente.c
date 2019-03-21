#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <mqueue.h>
#include <time.h>
#include <signal.h>
#include "common.h"

// Apuntador al fichero de log (se utilizará en el ejercicio resumen)
FILE *fLog = NULL;

// Cola del servidor
mqd_t mq_server = -1;

// Cola del cliente
mqd_t mq_client = -1;

// Nombre para las colas
char clientQueue[100];
char serverQueue[100];

char wlog[100];//cadena para escribir en el ficheo de log

// Función que procesará EL FINAL
void finPrograma(int value);

void funcionLog(char* mensaje);

void manejadorSenales(int signal);

int main(int argc, char **argv)
{

	// Buffer para intercambiar mensajes
	char buffer[MAX_SIZE];
	if (signal(SIGINT, manejadorSenales) == SIG_ERR){
    printf("No puedo asociar la señal SIGINT al manejador!\n");
	}
	if (signal(SIGTERM, manejadorSenales) == SIG_ERR){
		printf("No puedo asociar la señal SIGTERM al manejador!\n");
	}


	// Nombre para las colas. Al concatenar el login seran unicas en el sistema.
	sprintf(clientQueue, "%s-%s", CLIENT_QUEUE, getenv("USER"));
	sprintf(serverQueue, "%s-%s", SERVER_QUEUE, getenv("USER"));

	// Abrir la cola del servidor
	mq_server = mq_open(serverQueue, O_WRONLY);
	if( mq_server == (mqd_t)-1)
	{
     	perror("Error al abrir la cola del servidor");
			sprintf(wlog,"Error al abrir la cola del servidor");
			funcionLog(wlog);
      exit(EXIT_FAILURE);
	}

	// Abrir la cola del cliente
	mq_client = mq_open(clientQueue, O_RDONLY);
	if( mq_client == (mqd_t)-1)
	{
    	perror("Error al abrir la cola del cliente");
			sprintf(wlog,"Error al abrir la cola del cliente");
			funcionLog(wlog);
   	exit(EXIT_FAILURE);
	}

	// flag que indica cuando hay que parar
	int must_stop = 0;
	printf("Mandando mensajes al servidor (escribir \"%s\" para parar):\n", MSG_STOP);

	do
	{
		printf("> ");

		// Puede servirnos por si al hacer pruebas hemos cerrado nuestro cliente y servidor
		// y se han quedado caracteres en los bufferes de entrada/salida estandar
		fflush(stdout);                  // Limpiar buffer de salida
		memset(buffer, 0, MAX_SIZE);     // Poner a 0 el buffer

		/* Leer por teclado. Según la documentación, fgets lo hace de esta manera:
		It stops when either (n-1) characters are read, the newline character is read,
		or the end-of-file is reached, whichever comes first.
		Automáticamente fgets inserta el fin de cadena '\0'
		*/
		fgets(buffer, MAX_SIZE, stdin);

		/* //Descartar el \n del final
		if(buffer[strlen(buffer)-1] == '\n')
			buffer[strlen(buffer)-1] = '\0';
		*/
		funcionLog(buffer);
		// Enviar y comprobar si el mensaje se manda
		if(mq_send(mq_server, buffer, MAX_SIZE, 0) != 0)
		{
			perror("Error al enviar el mensaje");
			sprintf(wlog,"Error al enviar el mensaje");
			funcionLog(wlog);
			exit(EXIT_FAILURE);
		}

		if(strncmp(buffer, MSG_STOP, strlen(MSG_STOP))==0)
			must_stop=1;
		else
		{
			// Número de bytes leidos
			ssize_t bytes_read;
			// Recibir el mensaje
			bytes_read = mq_receive(mq_client, buffer, MAX_SIZE, NULL);
			// Comprar que la recepción es correcto (bytes leidos no son negativos)
			if(bytes_read < 0)
			{
				perror("Error al recibir el mensaje");
				sprintf(wlog,"Error al recibir el mensaje");
				funcionLog(wlog);
				exit(EXIT_FAILURE);
			}

			// Cerrar la cadena
			//buffer[bytes_read] = '\0';

			printf("Recibido el mensaje: %s\n", buffer);
			sprintf(wlog,"Recibido el mensaje: %s",buffer);
			funcionLog(wlog);
			//Si recibo un exit del servidor es que ha habido fallo en el marching.
			if(strncmp(buffer, MSG_STOP, strlen(MSG_STOP))==0)
				must_stop=1;
		}
		// Iterar hasta escribir el código de salida
	}while (!must_stop);

	finPrograma(-1);
	exit(EXIT_SUCCESS);
}




void finPrograma(int value)
{
   //char wlog[100];

	if(mq_client!=-1)
	{
		// Cerrar la cola del servidor
		if(mq_close(mq_client) == (mqd_t)-1)
		{
			perror("Error al cerrar la cola del cliente");
			sprintf(wlog,"Error al cerrar la cola del cliente");
			funcionLog(wlog);
			exit(EXIT_FAILURE);
		}
	}

	if(mq_server!=-1)
	{
		// Buffer para intercambiar mensajes
		char buffer[MAX_SIZE];

		//Finalizar el programa (exit). Se lo enviamos al servidor
		//sprintf(buffer,"%s",MSG_STOP);
		strcpy(buffer,MSG_STOP);

		// Enviar y comprobar si el mensaje se manda
		if(mq_send(mq_server, buffer, MAX_SIZE, 0) != 0)
		{
			perror("Error al enviar el mensaje");
			sprintf(wlog,"Error al enviar el mensaje");
			funcionLog(wlog);
			exit(EXIT_FAILURE);
		}

		// Cerrar la cola del servidor
		if(mq_close(mq_server) == (mqd_t)-1)
		{
			perror("Error al cerrar la cola del servidor");
			sprintf(wlog,"Error al cerrar la cola del servidor");
			funcionLog(wlog);
			exit(EXIT_FAILURE);
		}
	}

	exit(EXIT_SUCCESS);
}
void funcionLog(char *mensaje)
{
	int resultado;
	char nombreFichero[100];
	char mensajeAEscribir[300];
	time_t t;

	// Abrir el fichero
	sprintf(nombreFichero,"log-cliente.txt");
	if(fLog==NULL)
	{
		fLog = fopen(nombreFichero,"at");
		if(fLog==NULL)
		{
			perror("Error abriendo el fichero de log");;
			exit(1);
		}
	}

	// Obtener la hora actual
	t = time(NULL);
	struct tm * p = localtime(&t);
	strftime(mensajeAEscribir, 1000, "[%Y-%m-%d, %H:%M:%S]", p);

	// Vamos a incluir la hora y el mensaje que nos pasan
	sprintf(mensajeAEscribir, "%s ==> %s\n", mensajeAEscribir, mensaje);

	// Escribir finalmente en el fichero
	resultado = fputs(mensajeAEscribir,fLog);
	if (resultado < 0){
		perror("Error escribiendo en el fichero de log");
	}
	fclose(fLog);
	fLog=NULL;
}

void manejadorSenales(int signal){
	sprintf(wlog,"Capturada la señal %d",signal);
	funcionLog(wlog);

	sprintf(wlog,"Fin de sesion");
	funcionLog(wlog);

	if(mq_send(mq_server, wlog, 100, 0) != 0)
	{
		perror("Error al enviar el mensaje");
		sprintf(wlog,"Error al enviar el mensaje");
		funcionLog(wlog);
		exit(EXIT_FAILURE);
	}
	finPrograma(-1);
}
