#include	<signal.h>
#include	<stdio.h>
#include    <stdlib.h>
#include    <unistd.h>

void imprimir();
void sig_alarm(int valor);
int main()
{
	int cont=0;
	pid_t pid;
	while(1){
	signal(SIGALRM, imprimir);
	sig_alarm(5);
	sig_alarm(3);
	sig_alarm(1);
	cont++;
	if(cont==4)
	kill(pid, SIGINT);
}
}

void imprimir()
{
	printf("RING\n");
}

void sig_alarm(int valor)
{
	alarm(valor);
	pause();
}