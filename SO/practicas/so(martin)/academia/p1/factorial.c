#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv)
{
	int num, suma=1, i;
	if(argc!=2)
	{
		puts("Error en la línea de órdenes.");
		exit(-1);
	}
	num=atoi(argv[1]);
	for(i=1;i<=num;i++)
	{
		suma=suma*i;
	}
	printf("El factorial de {%d} es [%d]\n", num, suma);
}