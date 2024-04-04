#include <stdio.h>

struct c {
  int a1;
  int b2;
}; // is it ok to pad this inside struct

struct c d;
int a = 0;

int b = 1;

int main()
{
  b = a + 1;
  printf("%d", 4);
  return 1;
}