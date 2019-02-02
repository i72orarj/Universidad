#ifndef   CONTADOR_H
#define CONTADOR_H
#include <list>

class Contador {
private:
int valor_;
int min_;
int max_;
int n_;
std::list<int> valores_;

public:
Contador(int valor=0,int min=0,int max=1000);
Contador operator =(int num);
Contador operator =(Contador c);
Contador operator ++(int);
Contador operator ++(void);
Contador operator --(int);
Contador operator --(void);
Contador operator +(int num);
friend Contador operator +(int num, Contador c);
Contador operator -(int num);
friend Contador operator -(int num, Contador c);
bool undo(int num=1);
inline int get(){return valor_;};
inline void setValor(int num){valor_=num;};
inline int getMin(){return min_;};
inline void setMin(int num){min_=num;};
inline int getMax(){return max_;};
inline void setMax(int num){max_=num;};
inline std::list <int> getValores(){return valores_;};
inline void setValores(std::list <int> valores){valores_=valores;};
inline int getN(){return n_;};
inline void setN(int n){n_=n;};

};


#endif
