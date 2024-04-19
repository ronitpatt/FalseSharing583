#include <pthread.h> 
#include <stdio.h>

#define MAX 1024 
#define MAX_THREAD 256

using namespace std; 

int a[MAX]; 
int totals[MAX_THREAD*16];
int part_size = MAX/MAX_THREAD;
 
void* sum_array(void* arg) { 
    unsigned long long thread_part = (unsigned long long) arg; 
    printf("Thread %d\n", thread_part);
    
    int extend = 0;
    
    if (MAX % MAX_THREAD != 0 && thread_part == MAX_THREAD - 1) {
        extend = MAX % MAX_THREAD;
    }

    for (int i = 0; i < 100000; i++){
        totals[thread_part] += a[i%MAX];
    }
    return nullptr;
} 
 
int main() 
{ 
    for (int i = 0; i < MAX; i++){
        a[i] = i + 1; 
    }

    pthread_t threads[MAX_THREAD]; 
 
    for (unsigned long long i = 0; i < MAX_THREAD; i++){
        pthread_create(&threads[i], NULL, sum_array, (void*)i); 
    }

    for (int i = 0; i < MAX_THREAD; i++) {
        pthread_join(threads[i], NULL); 
    }
    
    // int total_sum = 0; 
    // for (int i = 0; i < MAX_THREAD; i++){
    //     total_sum += a[i*part_size]; 
    // }
    // printf("Sum of array is %d\n", total_sum);
    // printf("Expected sum is %d\n", (MAX * (MAX + 1)) / 2);
    return 0; 
} 