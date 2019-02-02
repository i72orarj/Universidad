#include "contador.h"
#include <list>
  
Contador::Contador(int valor,int min,int max){
  setN(0);
  if(valor>max||valor<min){
    setValor(0);
    setMin(0);
    setMax(1000);
    setN(getN()+1);
    valores_.push_back(0);
  }
  else if(max<=min){
    setValor(0);
    setMin(0);
    setMax(1000);
    setN(getN()+1);
    valores_.push_back(0);
  }
  else{
    setValor(valor);
    setMin(min);
    setMax(max);
    setN(getN()+1);
    valores_.push_back(valor);
  }
}

Contador Contador::operator =(Contador c){
  setValor(c.get());
  setMin(c.getMin());
  setMax(c.getMax());
  setN(getN()+1);
  valores_.push_back(c.get());
  return *this;
}

Contador Contador::operator =(int num){
  if(num<getMin()){
    setValor(getMin());
    setN(getN()+1);
    valores_.push_back(getMin());
  }
  else if(num>getMax()){
    setValor(getMax());
    setN(getN()+1);
    valores_.push_back(getMax());
  }
  else{
    setValor(num);
    setN(getN()+1);
    valores_.push_back(num);
  }
  return *this;
}

Contador Contador::operator ++(int){
  Contador aux=*this;
  if(get()<getMax()){
    setValor(get()+1);
    setN(getN()+1);
    valores_.push_back(get());
  }
  return aux;
}

Contador Contador::operator ++(void){
  if(get()<getMax()){
    setValor(get()+1);
    setN(getN()+1);
    valores_.push_back(get());
  }
  return *this;
}

Contador Contador::operator --(int){
  Contador aux=*this;
  if(get()>getMin()){
    setValor(get()-1);
    setN(getN()+1);
    valores_.push_back(get());
  }
  return aux;
}

Contador Contador::operator --(void){
  if(get()>getMin()){
    setValor(get()-1);
    setN(getN()+1);
    valores_.push_back(get());
  }
  return *this;
}

Contador Contador::operator +(int num){
  if(get()+num<getMax()){
    setValor(get()+num);
  }
  else{
    setValor(getMax());
  }
  setN(getN()+1);
  valores_.push_back(get());
  return *this;
}

Contador operator +(int num,Contador c){
  Contador aux(c);
  if(num+aux.get()<aux.getMax()){
    aux.setValor(num+aux.get());;
  }
  else{
    aux.setValor(aux.getMax());
  }
  aux.setN(aux.getN()+1);
  aux.valores_.push_back(aux.get());
  return aux;
}

Contador Contador::operator -(int num){
  if(get()-num>getMin()){
    setValor(get()-num);
  }
  else{
    setValor(getMin());
  }
  setN(getN()+1);
  valores_.push_back(get());
  return *this;
}

Contador operator -(int num,Contador c){
  Contador aux(c);
  if(num-aux.get()>aux.getMin()){
    aux.setValor(num-aux.get());;
  }
  else{
    aux.setValor(aux.getMin());
  }
  aux.setN(aux.getN()+1);
  aux.valores_.push_back(aux.get());
  return aux;
}

bool Contador::undo(int num){
  if(num>getN()-1||num<1){
    return false;
  }
  else{
    int aux;
    for(int i=0;i<num;i++){
      valores_.pop_back();
      aux=valores_.back();
      setN(getN()-1);
    }
    setValor(aux);
    return true;
  }
}
