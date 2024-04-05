#include <stdio.h>

struct c {
  int a1; 
  int a2; 
}; // is it ok to pad this inside struct

int main()
{
  c f;
  f.a1 = 3;
  f.a2 = 9;
  // allocate 128 bytes for F
  // memcpy temp to F
  
  // printf("%d\n", f.a1);
  // printf("%d\n", f.a2);
  

  char *buff = (char*)&f;

  for (int i = 0; i < 128; i+=4) {
    printf("%u %d \n", i, buff[i]);
 }
  return 1;
}