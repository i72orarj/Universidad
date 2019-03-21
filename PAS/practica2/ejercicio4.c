#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <mqueue.h>
#include <regex.h>
#include <errno.h>
#include <getopt.h>
#include <time.h>
#include <signal.h>
#include <string.h>

#define MSG_STOP "exit"
#define NAME_QUEUE "/nameQueue"

mqd_t queue=-1;

char nameQueue[100];
char wlog[100];
char msgbuf[100];

void imprimir_uso()
{
    printf("Uso del programa: ejercicio4-servidor [opciones]\n");
    printf("Opciones:\n");
    printf("-h, --help\t\t\tImprimir esta ayuda\n");
    printf("-r, --regex=EXPR\t\tExpresión regular a utilizar\n");
}

int main(int argc, char **argv) {
  pid_t flag;
  int status;
  char* regexValue=NULL;
  struct mq_attr attr;
  char buffer[100];
  regex_t regex;
  int reti,c,option_index=0,must_stop;

  attr.mq_maxmsg = 10;
	attr.mq_msgsize = 100;

  static struct option long_options[] =
	{
		{"regex",  required_argument,	   0, 'r'},
		{"help",     no_argument,	   0, 'h'},
		{0, 0, 0, 0}
	};

  sprintf(nameQueue, "%s-%s",NAME_QUEUE, getenv("USER"));

  while ((c = getopt_long (argc, argv, "hr:",long_options, &option_index))!=-1)
		switch (c)
		{
			case 'h':
				imprimir_uso();
				break;
			case 'r':
				regexValue = optarg;
				break;
			case '?':
				if (optopt == 'r')
					fprintf (stderr, "La opción -%c requiere un argumento.\n", optopt);
				else if (isprint (optopt))
					fprintf (stderr, "Opción desconocida `-%c'.\n", optopt);
				else
					fprintf (stderr, "Carácter de opción desconocido `\\x%x'.\n", optopt);
					imprimir_uso();
			default:
				exit(EXIT_SUCCESS);
		}

	//Por si se invoca sin argumentos
	if(regexValue==NULL)
	{
	   imprimir_uso();
	   exit(EXIT_SUCCESS);
	}
  reti = regcomp(&regex, regexValue, 0);
   if(reti!=0)
   {
    fprintf(stderr, "PADRE No pude compilar la expresión regular\n");
    exit(EXIT_FAILURE);
  }

  switch (fork()) {
    case -1:
    break;
    case 0://hijo actuando como cliente
    queue = mq_open(nameQueue, O_RDWR);
  	if( queue == (mqd_t)-1)
  	{
       	perror("HIJO Error al abrir la cola");
        exit(EXIT_FAILURE);
  	}
    do
  	{
  		printf("HIJO > ");

  		// Puede servirnos por si al hacer pruebas hemos cerrado nuestro cliente y servidor
  		// y se han quedado caracteres en los bufferes de entrada/salida estandar
  		fflush(stdout);                  // Limpiar buffer de salida
  		memset(buffer, 0, 100);     // Poner a 0 el buffer

  		/* Leer por teclado. Según la documentación, fgets lo hace de esta manera:
  		It stops when either (n-1) characters are read, the newline character is read,
  		or the end-of-file is reached, whichever comes first.
  		Automáticamente fgets inserta el fin de cadena '\0'
  		*/
  		fgets(buffer, 100, stdin);

  		/* //Descartar el \n del final
  		if(buffer[strlen(buffer)-1] == '\n')
  			buffer[strlen(buffer)-1] = '\0';
  		*/
  		////funcionLog(buffer);
  		// Enviar y comprobar si el mensaje se manda
  		if(mq_send(queue, buffer, 100, 0) != 0)
  		{
  			perror("HIJO Error al enviar el mensaje");
  			//sprintf(wlog,"Error al enviar el mensaje");
  			////funcionLog(wlog);
  			exit(EXIT_FAILURE);
  		}

  		if(strncmp(buffer, MSG_STOP, strlen(MSG_STOP))==0)
  			must_stop=1;
  		else
  		{
  			// Número de bytes leidos
  			ssize_t bytes_read;
  			// Recibir el mensaje
  			bytes_read = mq_receive(queue, buffer, 100, NULL);
  			// Comprar que la recepción es correcto (bytes leidos no son negativos)
  			if(bytes_read < 0)
  			{
  				perror("HIJO Error al recibir el mensaje");
  				//sprintf(wlog,"Error al recibir el mensaje");
  				//funcionLog(wlog);
  				exit(EXIT_FAILURE);
  			}

  			// Cerrar la cadena
  			//buffer[bytes_read] = '\0';

  			printf("HIJO Recibido el mensaje: %s\n", buffer);
  			//sprintf(wlog,"Recibido el mensaje: %s",buffer);
  			//funcionLog(wlog);
  			//Si recibo un exit del servidor es que ha habido fallo en el marching.
  			if(strncmp(buffer, MSG_STOP, strlen(MSG_STOP))==0)
  				must_stop=1;
  		}
  		// Iterar hasta escribir el código de salida
  	}while (!must_stop);

  	//finPrograma(-1);
  	exit(EXIT_SUCCESS);
    break;
    default://padre actuando como servidor
    queue = mq_open(nameQueue, O_CREAT | O_RDWR, 0644, &attr);
  	if(queue == (mqd_t)-1)
  	{
       	perror("PADRE Error al abrir la cola del servidor");;
     	exit(EXIT_FAILURE);
  	}
    do {
  		// Número de bytes leidos
  		ssize_t bytes_read;

  		// Recibir el mensaje
  		bytes_read = mq_receive(queue, buffer, 100, NULL);
  		// Comprar que la recepción es correcto (bytes leidos no son negativos)
  		if(bytes_read < 0)
  		{
  			perror("PADRE Error al recibir el mensaje");
        //sprintf(wlog,"Error al recibir el mensaje");
        //funcionLog(wlog);
  			exit(EXIT_FAILURE);
  		}
  		// Comprobar el fin del bucle si se lee exit
  		if (strncmp(buffer, MSG_STOP, strlen(MSG_STOP))==0||strcmp(buffer,"Fin de sesion")==0)
  		{
  			must_stop = 1;
  		}
  		else
  		{
  			printf("PADRE Recibido el mensaje: %s\n", buffer);
        //sprintf(wlog,"Recibido el mensaje: %s",buffer);
        ////funcionLog(wlog);

  			/* Comprobar la expresión regular sobre la cadena pasada como argumento */
  			reti = regexec(&regex, buffer, 0, NULL, 0);

  			sprintf(msgbuf,"%s", buffer); //Hago una copia por si hay error de matching mostralo.
  		   // Puede servirnos, UNA VEZ COMPROBADA LA EXPRESION, por si al hacer pruebas hemos cerrado nuestro
  		   // cliente y servidor, y se han quedado caracteres en los bufferes de entrada/salida estandar
  		   fflush(stdout);                  // Limpiar buffer de salida
  		   memset(buffer, 0, 100);     // Poner a 0 el buffer

  			if(reti==0)
  			{
  				strcpy(buffer,"Empareja");
          ////funcionLog("Empareja");
  			}
  			else if(reti==REG_NOMATCH)
  			{
  				strcpy(buffer,"No Empareja");
          //funcionLog("No empareja");
  			}
  			else
  			{
  				regerror(reti, &regex, msgbuf, sizeof(msgbuf));
  				fprintf(stderr, "PADRE Falló el matching de la expresión regular: %s\n", msgbuf);
          //sprintf(wlog,"Falló el matching de la expresión regular: %s",msgbuf);
          //funcionLog(wlog);

  				//Finalizar el programa si falla el matching (exit). Se lo enviamos al cliente
  				//sprintf(buffer,"%s",MSG_STOP);
  				strcpy(buffer,MSG_STOP);
  			}

  			// Enviar y comprobar si el mensaje se manda
  			if(mq_send(queue, buffer, 100, 0) != 0)
  			{
  				perror("PADRE Error al enviar el mensaje");
          //sprintf(wlog,"Error al enviar el mensaje");
          //funcionLog(wlog);
  				exit(-1);
  			}

  		}
  	}while (!must_stop); // Iterar hasta que llegue el código de salida exit

  	// Cerrar el programa
  	//finPrograma(-1);

  	/* Liberar la expresión regular utilizada */
  	regfree(&regex);

  	//exit(EXIT_SUCCESS);


    while ( (flag=wait(&status)) > 0 ){
      if (WIFEXITED(status)){
        printf("Proceso Padre, Hijo con PID %ld finalizado, status = %d\n", (long int)flag, WEXITSTATUS(status));
      }
      else if (WIFSIGNALED(status)){
        printf("Proceso Padre, Hijo con PID %ld finalizado al recibir la señal %d\n", (long int)flag, WTERMSIG(status));
      }
      else if (WIFSTOPPED(status)){
        printf("Proceso Padre, Hijo con PID %ld parado al recibir la señal %d\n", (long int)flag,WSTOPSIG(status));
      }
      else if (WIFCONTINUED(status)){
        printf("Proceso Padre, Hijo con PID %ld reanudado\n",(long int) flag);
      }
    }
    if (flag==(pid_t)-1 && errno==ECHILD){
      printf("Proceso Padre, valor de errno = %d, definido como %s, no hay más hijos que esperar!\n", errno, strerror(errno));
    }
    else{
      printf("Error en la invocacion de wait o la llamada ha sido interrumpida por una señal.\n");
      exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
    break;
  }
  return 0;
}
