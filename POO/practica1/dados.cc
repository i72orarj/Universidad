#include "dados.h"
#include <cstdlib>
#include <ctime>

int Dados::getDado1(){
  return d1_;
}
int Dados::getDado2(){
  return d2_;
}
bool Dados::setDado1(int d1){
  if((d1>=1) &&(d1<=6)){
    d1_=d1;
    suma1_=suma1_+d1;
    lanza1_++;
    anadeUltimo1(d1);
    return true;
  }
  else{
    return false;
  }
}
bool Dados::setDado2(int d2){
  if((d2>=1) &&(d2<=6)){
    d2_=d2;
    suma2_=suma2_+d2;
    lanza2_++;
    anadeUltimo2(d2);
    return true;
  }
  else{
    return false;
  }
}
int Dados::getSuma(){
  return d1_+d2_;
}
void Dados::lanzamiento(){
  d1_=(rand()%6)+1;
  lanza1_++;
  suma1_=suma1_+d1_;
  anadeUltimo1(d1_);
  d2_=(rand()%6)+1;
  lanza2_++;
  suma2_=suma2_+d2_;
  anadeUltimo2(d2_);
}
int Dados::getLanzamientos1(){
  return lanza1_;
}
int Dados::getLanzamientos2(){
  return lanza2_;
}
float Dados::getMedia1(){
  return suma1_/lanza1_;
}
float Dados::getMedia2(){
  return suma2_/lanza2_;
}
void Dados::anadeUltimo1(int x1){
  v1_[4]=v1_[3];
  v1_[3]=v1_[2];
  v1_[2]=v1_[1];
  v1_[1]=v1_[0];
  v1_[0]=x1;
}
void Dados::anadeUltimo2(int x2){
  v2_[4]=v2_[3];
  v2_[3]=v2_[2];
  v2_[2]=v2_[1];
  v2_[1]=v2_[0];
  v2_[0]=x2;
}
void Dados::getUltimos1(int v1[5]){
  v1[0]=v1_[0];
  v1[1]=v1_[1];
  v1[2]=v1_[2];
  v1[3]=v1_[3];
  v1[4]=v1_[4];
}
void Dados::getUltimos2(int v2[5]){
  v2[0]=v2_[0];
  v2[1]=v2_[1];
  v2[2]=v2_[2];
  v2[3]=v2_[3];
  v2[4]=v2_[4];
}
int Dados::getDiferencia(){
  if(d1_>=d2_){
    return d1_-d2_;
  }
  else{
    return d2_-d1_;
  }
}
Dados::Dados(){
  srand(time(NULL));
  setDado1(1);
  setDado2(1);
  lanza1_=0;
  lanza2_=0;
  suma1_=0;
  suma2_=0;
//  v1_[]={0,0,0,0,0};
//  v2_[]={0,0,0,0,0};
  for(int i=0;i<5;i++){
    v1_[i]=0;
    v2_[i]=0;
  }
}
