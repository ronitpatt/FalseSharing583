#include <stdio.h>
#include <unistd.h>

struct c {
    int front;
  }; // is it ok to pad this inside struct


int main()
{
  c arr[4];

  for (int i = 0; i<12; i++){
    arr[i].front = 888;
  }
  // c a;
  // arr[0].front = 0;
  
  bool even = (fork() == 0);


  for (int i = 0; i<6; i++){
    if (even) {
      printf("%d", arr[i*2].front);
    } else {
      printf("%d", arr[i*2+1].front);
    }
  }

  // for (int i = 0; i < 4; i+=1) {
  //   printf("%d %d %d\n", arr[i].front, arr[i].c1, arr[i].array[1]);
  // }
  //c* a= &(arr[0]);

  int *buff = (int*)&arr;
  
  for (int i = 0; i < 64*4; i+=1) {
    if (i*4 %64 == 0) {
      printf("-----------------------\n");
    }
    printf("%d %d \n", i, buff[i]);
  }

  return 1;
}