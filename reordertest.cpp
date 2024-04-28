#include <stdio.h>
#include <unistd.h>
// #include <thread>
// #include <atomic>
#include <pthread.h>

struct c {
    int front;
    //char pad[60];
    int back;
    short front2;
  }; // is it ok to pad this inside struct

int elements_per_thread = 1000000;

void* work (void* obj) {
  for (int i =0; i<elements_per_thread; i++){
    //printf("inside thread\n");
    c* ptr = (c*)obj;
    ptr->front++;
    ptr->front2++;
    sched_yield()
    // printf("%d\n", ptr->front);
  }
  return nullptr;
}

void* work2 (void* obj) {
  for (int i =0; i<elements_per_thread; i++){
    // printf("inside thread\n");
    c* ptr = (c*)obj;
    ptr->back++;
    sched_yield();
    // printf("%d\n", ptr->front);
  }
  return nullptr;
}

/*
- parallel prefix sum
- parallel merge sort
- parallel quick sort
- parallel matrix multiplication
*/

int main()
{
  c obj;
  obj.front = 0;
  obj.back = 0;
  printf("%p\n",&obj.front );
  printf("%p\n",&obj.back );
  // std::jthread t1(work, 1);
  // std::jthread t2(work1, 2);
  pthread_t ptid1, ptid2; 
  pthread_create(&ptid1, NULL, &work, (void*) &obj); 
  pthread_create(&ptid2, NULL, &work2, (void*) &obj); 

  pthread_join(ptid1, NULL);
  pthread_join(ptid2, NULL);
  printf("front: %d\n", obj.front);
  printf("back: %d\n", obj.back);
  // pthread_exit(NULL);
  return 0;
}
