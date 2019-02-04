/*
Name        :   Dining Philosophers Problem
Author      :   jishnu7
Web         :   http://thecodecracker.com
Date        :   26-Sep-2010
Description :   C Program to solve Dining philosophers problem
License     :   GNU GPL License
*/
 
#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
 
#define N 5
#define THINKING 0
#define HUNGRY 1
#define EATING 2
#define LEFT (	ph_num+4)%N  //(ph_num-1)%N
#define RIGHT (ph_num+1)%N  //(ph_num+1)%N
/* Alternativa
typedef enum {
    PENSANDO, HAMBRIENTO, COMIENDO
} status;
status state[N];
 */
sem_t mutex; //sirve para que solo un filosofo compruebe que puede coger tenedores
sem_t S[N]; //sirve para bloquearse si el de izq o der no hay tenedor
 
int state[N]; //vector de estados
int phil_num[N]={0,1,2,3,4}; 

void * philospher(void *num);
void take_fork(int);
void put_fork(int);
void test(int);
 
int main()
{
    int i;
    pthread_t thread_id[N];
    sem_init(&mutex,0,1);
    for(i=0;i<N;i++)
        sem_init(&S[i],0,0); //el semaforo se inicializa a 0 por que empieza ya bloqueado (luego en el test se desbloqueara)
    for(i=0;i<N;i++)
    {
        pthread_create(&thread_id[i],NULL,philospher,&phil_num[i]);
        printf("Philosopher %d is thinking\n",i+1);
    }
    for(i=0;i<N;i++)
        pthread_join(thread_id[i],NULL);
}
 
void *philospher(void *num)
{
    while(1)
    {
        int *i = num;
        //sleep(1);
        usleep(random()%2000000);
        take_fork(*i);
        //sleep(0);        
        usleep(random()%2000000);
        put_fork(*i);
    }
}
 
void take_fork(int ph_num)
{
    sem_wait(&mutex);
    state[ph_num] = HUNGRY;
    printf("Philosopher %d is Hungry\n",ph_num+1);
    test(ph_num);
    sem_post(&mutex);
    sem_wait(&S[ph_num]);
    //sleep(1);
    usleep(random()%2000000);
}
 
void test(int ph_num)
{
    if (state[ph_num] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING)
    {
        state[ph_num] = EATING;
        //sleep(2);
	     usleep(random()%2000000);        
        printf("Philosopher %d takes fork %d and %d\n",ph_num+1,LEFT+1,ph_num+1);
        printf("Philosopher %d is Eating\n",ph_num+1);
        sem_post(&S[ph_num]);//me sumo 1 para no quedarme bloqueado en la 74, si no hubiese entrado en el if me quedo bloqueado en la 74 hasta que me despierte el de la izq o der
    }
}
 
void put_fork(int ph_num)
{
    sem_wait(&mutex);
    state[ph_num] = THINKING;
    printf("Philosopher %d putting fork %d and %d down\n",ph_num+1,LEFT+1,ph_num+1);
    printf("Philosopher %d is thinking\n",ph_num+1);
    test(LEFT);
    test(RIGHT);
    sem_post(&mutex);
}
