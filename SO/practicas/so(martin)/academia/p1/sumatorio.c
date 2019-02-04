#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int suma=0, i , num;
	num=atoi(argv[1]);

	for(i=0;i<=num;i++)
	{
		suma+=i;
	}
	printf("El sumatorio de {%d} es [%d]\n", num, suma);
}