#include <stdlib.h>
#include <stdio.h>

long int factorial (int n)
{
long int resultado= 1;
int num;

for (num= 2; num<= n; num++)
{
	resultado= resultado*num;
	printf ("Factorial de %d, resultado parcial %ld\n", n, resultado);
	sleep (1);
}
return resultado;
}

int main (int argc, char *argv[])
{
	if (argc== 2)
		printf ("El factorial de %s es %ld\n", argv[1], factorial (atoi(argv[1])));
	else
		printf("Use: ./a.out numeroEntero\n");
return 0;
}
