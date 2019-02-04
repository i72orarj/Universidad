#include "funciones.h"


void f(float n){
  float x;
  float res;
  for(x=0;x<=n;x+=0.2){
    res=3 * pow(M_E,x) - 2*x;
    printf("x=%.1f >> %f\n",x,res );
  }
}

void g(float n){
  float x;
  float res;
  for(x=0;x<=n;x+=0.2){
    res=(-x * sin(x) + 1.5);
    printf("x=%.1f >> %f\n",x,res );
  }
}

void z(float n){
  float x;
  float res;
  for(x=0;x<=n;x+=0.2){
    res=pow(x,3) - 2*x + 1;
    printf("x=%.1f >> %f\n",x,res );
  }
}
