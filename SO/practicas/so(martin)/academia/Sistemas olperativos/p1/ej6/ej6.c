#include <sys/types.h>
#include <wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void main(int argc,char *argv[])
{
int i, status, registro;
pid_t pid;

printf("\n");

for(i=0;i<2;i++)
  {
  pid = fork();
  if (pid==-1)
    {
    perror("fork error");
    printf("errno value= %d\n", errno);
    exit(-1);
    }

  if(pid==0)  //hijo vuelta 1
   {  
    if(i==0) 
    {
    printf ("\nSoy el hijo %d, mi PID es %d, hago el 1\n",i,getpid());
    execlp(argv[1],argv[1],0,NULL);
    registro=getpid();
    sleep(2);
    exit(-1);
    }
    if(i==1&&(getpid()!=registro))  //hijo vuelta 2
    {   
    printf ("\nSoy el hijo %d, mi PID es %d, hago el 2\n",i,getpid());
    execvp(argv[2],&argv[2]);
    sleep(2);
    exit(-1);
    }
   }
  else  //padre
    {
    wait(&status);
    wait(&status);
    //exit(-1);
    }
  }

printf("Fin del programa...\n\n");

}
