#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int num=atoi(argv[1]);

	int i, suma=0;
	for(i=0;i<=num; i++)
	{
		suma+=i;
	}
	printf("El sumatorio de %d es %d\n", num, suma);
}