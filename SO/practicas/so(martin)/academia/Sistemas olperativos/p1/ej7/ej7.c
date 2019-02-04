#include <sys/types.h>
#include <wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void main(int argc,char *argv[])
{
FILE* f;
pid_t pid;
int status;

if((f=fopen(argv[1],"a"))==NULL)
{
printf("\nError, no se pudo crear el fichero %s\n",argv[1]);
exit(-1);
}
else
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
    printf ("\nSoy el hijo, mi PID es %d\n",getpid());
    sleep(1);
fprintf(f,"-----\n");
    sleep(1);
fprintf(f,"-----\n");
    exit(-1);
    }
      
  if(pid!=0)
    {
    printf ("\nSoy el padre, mi PID es %d\n",getpid());
fprintf(f,"+++++\n");
    sleep(1);
fprintf(f,"xxxxx\n");
    wait(&status);
    }

fclose(f);

printf("Fin del programa...\n\n");
}
}
