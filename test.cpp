#include <stdio.h>
#include <unistd.h>

struct c {
    int front;
    char padding[60];
}; // is it ok to pad this inside struct


int main()
{
  c arr[4];
  // c a;
  arr[0].front = 0;
  
  

  // for (int i = 0; i < 4; i+=1) {
  //   //printf("%d %d %d\n", arr[i].front, arr[i].c1, arr[i].array[1]);
  // }
  //c* a= &(arr[0]);
  // int *buff = (int*)&arr;

  // for (int i = 0; i<4; i++){
  //   arr[i].front = 888;
  // }
  
  // for (int i = 0; i < 64*4; i+=1) {
  //   if (i*4 %64 == 0) {
  //     printf("-----------------------\n");
  //   }
  //   printf("%d %d \n", i, buff[i]);
  // }

  return 1;
}