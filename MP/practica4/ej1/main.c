#include "funciones.h"

int main(int argc, char const *argv[]) {
  void (*func)(float);
  float n;
  int option;
  printf("1.- f(x) = 3 * e^x – 2x\n");
  printf("2.- g(x) = -x * sin(x) + 1.5\n");
  printf("3.- z(x) = x^3 - 2x + 1\n");
  scanf("%d",&option );
  switch (option) {
    case 1:
      func=&f;
    break;
    case 2:
      func=&g;
    break;
    case 3:
      func=&z;
    break;
  }
  printf("Introduzca valor maximo\n");
  scanf("%f",&n);
  func(n);
  return 0;
}
