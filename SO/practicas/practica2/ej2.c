#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

typedef unsigned char BOOLEAN;
#define ITER	10
#define NHILOS	4
#define TRUE 1
#define FALSE 0

double counter = 0;
BOOLEAN eligiendo[NHILOS];
int ticket[NHILOS];

int main()
{
    pthread_t hilos[NHILOS];
    int status, i;
    extern BOOLEAN eligiendo[NHILOS];
    extern int ticket[NHILOS];
    int v[NHILOS];
    extern double counter;
    void * adder(void * p);
    double *r_value;

    for(i=0;i<NHILOS;i++){
        eligiendo[i]=TRUE;
        ticket[i]=FALSE;}

    for(i=0;i<NHILOS;i++){
	    v[i]=i;
	    if ((status = pthread_create(&hilos[i], NULL, &adder, (void *) &v[i])))
	        exit(status);
    }

    for (i = 0; i < NHILOS; i++) {
      pthread_join(hilos[i], (void **) &r_value);
      printf("Value returned by %lu thread: %lf\n", hilos[i], *r_value);
    }

    fprintf(stdout, "%f\n", counter);

    return 0;
}



int maximo(int * ticket, int nelementos){
    int mayor=-1;
    for(int i=0;i<nelementos;i++){
        if(mayor<ticket[i])
            mayor=ticket[i];
    }
    return mayor;
}

int comparar(int ticket1, int ticket2, int Miturno, int SuTurno){
    if(ticket1>ticket2)
        return 1;
    else
        return 0;

    if(ticket1==ticket2)
        if(SuTurno<Miturno)
            return 1;
        else
            return 0;
}
void *adder(void *p){
    double l, *to_return;
    extern double counter;
    to_return =malloc(sizeof(double));
    int *id;
    id=(int *)p;
    extern BOOLEAN eligiendo[NHILOS];
    extern int ticket[NHILOS];

    for(int i=0;i<ITER;i++){
        eligiendo[*id]=TRUE;
        ticket[*id]=maximo(ticket, NHILOS)+1;
        eligiendo[*id]=FALSE;
        for(int j=0;j<NHILOS;j++){
            while(eligiendo[j]);
            while((ticket[j]!=0)&&(comparar(ticket[*id],ticket[j], *id, j)));
        }
        l = counter;
        fprintf(stdout, "Hilo %d: %f\n", *id, counter);
        l++;
        counter = l;
        *to_return = counter;
        ticket[*id]=0;
    }
    pthread_exit((void *) to_return);

}
