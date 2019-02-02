#ifndef DADOS_H
#define DADOS_H

class Dados{
private:
  int d1_;
  int d2_;
  int lanza1_;
  int lanza2_;
  int suma1_;
  int suma2_;
  int v1_[5];
  int v2_[5];
public:
  int getDado1();
  int getDado2();
  bool setDado1(int d1);
  bool setDado2(int d2);
  void lanzamiento();
  int getSuma();
  int getLanzamientos1();
  int getLanzamientos2();
  float getMedia1();
  float getMedia2();
  void anadeUltimo1(int x);
  void anadeUltimo2(int x);
  void getUltimos1(int v1[5]);
  void getUltimos2(int v2[5]);
  int getDiferencia();
  Dados();
};

#endif
