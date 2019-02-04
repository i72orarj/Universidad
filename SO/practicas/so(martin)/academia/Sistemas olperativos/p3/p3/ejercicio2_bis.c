#include  <pthread.h>
#include  <stdlib.h>
#include  <unistd.h>
#include  <stdio.h>

pthread_mutex_t ptmutex1;

void *thread_function(void *arg) 
{
	int i;
	char * c = (char *)arg;

	//

	if (pthread_mutex_lock(&ptmutex1)) 
	{
		printf("Error en pthread_mutex_lock...\n");
		pthread_exit(NULL);
	}
	printf("\nThread %ld running...\n", (unsigned long) pthread_self());
	for (i=0; i<5; i++) 
	{
		printf("%c",*c);
		fflush(stdout);
		sleep(1);
	}

	if (pthread_mutex_unlock(&ptmutex1)) 
	{
		printf("Error en pthread_mutex_unlock...\n");
		pthread_exit(NULL);
	}

	pthread_exit(NULL);
}

int main(void) {
	pthread_t thread[3];
	int i;
	char character[3]={'a','b','c'};

	for(i=0;i<3;i++)
		if (pthread_create( &thread[i], NULL, thread_function,(void *) &character[i]) ) 
		{
			printf("Error creando el hilo.");
			exit(EXIT_FAILURE);
		}

	if (pthread_mutex_lock(&ptmutex1)) {
		printf("Error en pthread_mutex_lock...\n");
		exit(EXIT_FAILURE);
	}
   printf("\nMain() %ld running...\n", (unsigned long) pthread_self());
	for (i=0; i<5; i++) 
	{
		printf("x");
		fflush(stdout);
		sleep(1);
	}

	if (pthread_mutex_unlock(&ptmutex1)) {
		printf("Error en pthread_mutex_unlock...\n");
		exit(EXIT_FAILURE);
	}

	for(i=0;i<3;i++)
		if (pthread_join(thread[i], NULL)) 
		{
			printf("Error union hilo %d\n",i);
			exit(EXIT_FAILURE);
		}
exit(EXIT_SUCCESS);
}
