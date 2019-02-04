#include <sys/types.h>
#include <wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void main()
{
int numero, i, status;
pid_t pid;

printf("\nIndique numero de procesos a crear: ");
scanf("%d",&numero);

  for(i=0;i<numero;i++)
  {
  pid = fork();
  if (pid==-1)
    {
    perror("fork error");
    printf("errno value= %d\n", errno);
    exit(-1);
    }

  if(pid==0)
  	{
    printf ("\nSoy el hijo %d, mi PID es %d \n",i,getpid());   
  	sleep(1*(i+1));
  	exit(0);
    }
  else
    {
    printf("\nSoy el padre, mi PID es %d. He creado el hijo %d\n",getpid(),i);

    while(wait(&status)==pid)
      {
      printf("\nEl status del proceso %d terminado es %d\n",i,WEXITSTATUS(status));

      }
    }
  }
printf("\nFin del programa...\n\n");

}