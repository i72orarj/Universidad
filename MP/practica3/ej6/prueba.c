#include <stdio.h>

int main(int argc, char const *argv[]) {
  char cadena1[30];
  scanf("%s",cadena1 );
  char final[60];
  sscanf("%smayusculas",final,cadena1);
  printf("%s\n",final );
  return 0;
}
