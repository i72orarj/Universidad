#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>

main()
{
	pid_t p1, p2, p3;
	int status, suma=0, digito;

	printf("Soy el padre y mi pid es %d\n", getpid());

	p1=fork();
	if(p1==0)
	{
		printf("Soy el primer hijo y mi pid es %d\n", getpid());
		digito= getpid()%10;
		exit(digito);
	}

	p2=fork();
	if(p2==0)
	{
		printf("Soy el segundo hijo y mi pid es %d\n", getpid());
		digito=getpid()%10;

		p3=fork();
		if(p3==0)
		{
			printf("Soy el nieto y mi pid es %d\n", getpid());
			digito=getpid()%10;
			exit(digito);
		}

		while(wait(&status) >0)
		{
			suma+=WEXITSTATUS(status);
		}
		digito = getpid() % 10;
		exit(digito + suma);
	}

	while(wait(&status) >0)
	{
		suma += WEXITSTATUS(status);
	}
	suma+=getpid()%10;

	printf("El valor de la suma %d\n", suma);
}