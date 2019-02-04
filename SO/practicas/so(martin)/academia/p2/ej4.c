#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
void * funcion(void *arg);
int main(int argc, char **argv)
{
	pthread_t thd1, thd2;
	int i, error=0;


	pthread_create(&thd1, NULL, (void *) funcion, (void *) argv[1]);
	pthread_create(&thd2, NULL, (void *) funcion, (void *) argv[2]);

	pthread_join(thd1, NULL);
	pthread_join(thd2, NULL);




}

void * funcion(void *arg)
{
	char *archivo=(char *)arg;

	system("ffmpeg -i archivo -f mp3 -ab 192000 -ar 48000 -vn ficheroNuevoMP3.mp3");
	pthread_exit(NULL);
}