#include <stdio.h>
#include <unistd.h>
#include "pthread.h"

// struct c {
//   int a[16];
//   int b[16];
//   int c[16];
// };
// c obj;

struct c {
  int a;
  int b;
  int c;
};

c arr[16];

void* work1(void* arg) {
  int a = *((int *) arg);
  printf("a = %d\n", a);
  for (int i = 0; i < 1000000; i++){
    arr[a].a++;
    arr[a].b++;
    arr[a].c++;
  }
  return nullptr;
}


int main()
{
  pthread_t ptid1, ptid2, ptid3; 
  int a = 0, b = 1, c = 2;

  pthread_create(&ptid1, NULL, work1, (void *) &a);
  pthread_create(&ptid2, NULL, work1, (void *) &b);
  pthread_create(&ptid3, NULL, work1, (void *) &c);

  pthread_join(ptid1, NULL);
  pthread_join(ptid2, NULL);
  pthread_join(ptid3, NULL);
}