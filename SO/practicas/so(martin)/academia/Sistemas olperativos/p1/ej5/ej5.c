#include <sys/types.h>
#include <wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void main(int argc,char *argv[])
{
int numero, valor;
pid_t pid;

numero=atoi(argv[1]);
valor=atoi(argv[2]);

printf("\n\nSEGUNDOS: %d  STATUS: %d\n",numero,valor);

  pid = fork();
  if (pid==-1)
    {
    perror("fork error");
    printf("errno value= %d\n", errno);
    exit(-1);
    }

  if(pid==0)
  	{
    printf ("\nSoy el hijo, mi PID es %d y el de mi padre es %d\n",getpid(),getppid());   
    sleep(numero);
    exit(valor);
    }
  if(pid>0)
    {
    sleep(3);
    printf("\nSoy el padre, mi PID es %d.\n",getpid());
    wait(&valor);
    
    if(valor==0)
{
printf("\nEl proceso hijo termino normalmente.");
}
    if(WIFEXITED(valor)!=0&&valor!=0)
{
printf("\nEl proceso hijo termino normalmente con valor %d",WEXITSTATUS(valor));
}
    if(WIFSIGNALED(valor))
{
printf("\nEl proceso hijo termino al recibir la señal: %d\n",WTERMSIG(valor));
}

    printf("\nSTATUS: %d \n",valor);
    printf("\nFin del programa...\n\n");
    exit(-1);   
    }

}

























