#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>

//Si el ejercicio cambia a destileria o fiesta de las particulas es el mismo ejercicio.

#define HOMBRES  4
#define MUJERES  6


sem_t s_mutex, s_vacio, s_hombres, s_mujeres;
int m=0;


int
main ()
{

  pthread_t hombres[HOMBRES], mujeres[MUJERES];
  void *hombre (void *), *mujer (void *);
  int i,v[HOMBRES+MUJERES];
  extern sem_t s_mutex, s_vacio, s_hombres, s_mujeres;


  /* Iniciar semaforos. */
  sem_init (&s_mutex, 0, 1);

  sem_init (&s_vacio, 0, 1);
  sem_init (&s_hombres, 0, 3); //Solo pueden entrar 3 al lavabo
  sem_init (&s_mujeres, 0 ,3);

  for (i=0; i<HOMBRES; i++)
    {
    v[i] = i;
    if (pthread_create (&hombres[i], NULL, hombre, &v[i]))
      exit (1);
   }

  for (i = HOMBRES; i < HOMBRES + MUJERES; i++)
    {
      v[i] = i;
      if (pthread_create (&mujeres[i-HOMBRES], NULL, mujer, &v[i]))
	exit (1);
    }


  for (i=0; i<HOMBRES; i++)
   pthread_join (hombres[i], NULL);

  for (i=0; i<MUJERES; i++)
   pthread_join (mujeres[i], NULL);
return 0;
}


void * hombre (void *p)
{
  int *index,i;
  extern int h;
  extern sem_t s_hombres, s_vacio , s_mutex;
  index = (int *)p;
 for(i=0;i<10;i++)
 {
   sem_wait (&s_hombres); //Dejan pillado al 4º en esta linea. El que inicialicemos en el semaforo. Solo deja pasar a 3 hombres.
   sem_wait (&s_mutex); //significa que quiero pasar por la puerta.
      h++;
	if(h==1) //Primer hombre que entra
		sem_wait (&s_vacio);
     sem_post (&s_mutex);
      printf ("Hombre al lavabo: %d \n", *index);
     sleep(1);
      sem_wait (&s_mutex);
      h--;
	if(h==0)
		sem_post (&s_vacio);
      sem_post (&s_mutex);
      sem_post (&s_hombres);
 }
}

void * mujer (void *p)
{
  int *index,i;
  extern int m;
  extern sem_t s_mujeres, s_vacio , s_mutex;
  index = (int *)p;
 for(i=0;i<10;i++)
 {
   sem_wait (&s_mujeres); //Este se quitaria si pueden entrar todas las mujeres/hombres al cuarto de baño.
   sem_wait (&s_mutex);
      m++;
	if(m==1)
		sem_wait (&s_vacio);
     sem_post (&s_mutex);
      printf ("Mujer al lavabo: %d \n", *index);
     sleep(15);
      sem_wait (&s_mutex);
      m--;
	if(m==0)
		sem_post (&s_vacio);
   sem_post (&s_mutex);
   sem_post (&s_mujeres);//Este se quitaria si pueden entrar todas las mujeres/hombres al cuarto de baño.
 }
}
