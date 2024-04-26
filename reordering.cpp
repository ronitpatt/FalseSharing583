#include <stdio.h>
#include <unistd.h>
#include "pthread.h"

struct c {
  char padding[56];
  int a;
  int b;
  int c;
  int d;
};
c obj;


void* work1(void* arg) {
  for (int i = 0; i < 1000000; i++){
    obj.a++;
    obj.c++;
  }
  return nullptr;
}

void* work2(void* arg) {
  for (int i = 0; i < 1000000; i++){
    obj.b++;
    obj.d++;
  }
  return nullptr;
}


int main() {
  pthread_t ptid1, ptid2;
  int a = 0, b = 1;

  pthread_create(&ptid1, NULL, work1, (void *) &a);
  pthread_create(&ptid2, NULL, work2, (void *) &b);

  pthread_join(ptid1, NULL);
  pthread_join(ptid2, NULL);
}