#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
void abrirGedit(char **argw);
int main(int argc, char **argv)
{
	pid_t pid;
	int i, status, opc=atoi(argv[2]);
	int suma=1, j;
	int num=atoi(argv[1]);

	

	for(i=0;i<2;i++)
	{
		pid=fork();
		switch(pid)
		{
			case -1:
					perror("fork error");
					exit(EXIT_FAILURE);

			case 0:
					if(i==0)
					{
						for(j=1;j<=num;j++)
						{
							suma=suma*j;
						}
						printf("El factorial de %d es %d\n", num, suma);
						exit(EXIT_SUCCESS);
					}
					if(i==1)
					{
						if(opc==1)
						{
							abrirGedit(&argv[3]);
							exit(EXIT_SUCCESS);
						}

						if(opc==2)
						{
							execlp("ls", "ls", "-l", NULL);
							exit(EXIT_SUCCESS);
						}
					}		
		}
	}
	while(wait(&status)>0 )
	{
		puts("Esperando a los hijos...");
	}

}

void abrirGedit(char **argw)
{
	execvp(*argw,argw);
}