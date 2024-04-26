#include <stdio.h>
#include <unistd.h>


int main() {
  
  int a;
  printf("ptr: %p\n", &a); 
}
// #include <thread>
// #include <cstatomic>
// #include <pthread.h>
// #include <atomic>

// struct c {
//     std::atomic<int> front;
//     //char pad[60];
//     std::atomic<int> back;
//   }; // is it ok to pad this inside struct

// int elements_per_thread = 10000000;

// void* work (void* obj) {
//   for (int i =0; i<elements_per_thread; i++){
//     //printf("inside thread\n");
//     c* ptr = (c*)obj;
//     ptr->front++;
//     // printf("%d\n", ptr->front);
//   }
//   return nullptr;
// }

// void* work2 (void* obj) {
//   for (int i =0; i<elements_per_thread; i++){
//     // printf("inside thread\n");
//     c* ptr = (c*)obj;
//     ptr->back++;
//     // printf("%d\n", ptr->front);
//   }
//   return nullptr;
// }


// int main()
// {
//   printf("hi n\n");
//   int base;
//   c obj;
//   int c;
//   printf("ptr: %p\n", &obj);
//   printf("ptr: %p\n", &obj.front);
//   printf("ptr: %p\n", &obj.back);
//   printf("ptr: %p\n", &c);
//   printf("diff: %li\n", (int *)(&obj) - (int *)(&base));
//   printf("diff: %li\n", (char *)(&c) - (char *)(&obj));
//   obj.front = 0;
//   obj.back = 0;
  
//   // std::jthread t1(work, 1);
//   // std::jthread t2(work1, 2);
//   pthread_t ptid1, ptid2; 
//   pthread_create(&ptid1, NULL, &work, (void*) &obj); 
//   pthread_create(&ptid2, NULL, &work2, (void*) &obj); 

//   pthread_join(ptid1, NULL);
//   pthread_join(ptid2, NULL);
//   //printf("front: %d\n", obj.front);
//   //printf("back: %d\n", obj.back);
//   // pthread_exit(NULL);
//   return 0;
// }
