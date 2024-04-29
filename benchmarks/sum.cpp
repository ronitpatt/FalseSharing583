#include <pthread.h> 
#include <stdio.h>

#define MAX 256 
#define MAX_THREAD 16

using namespace std; 
 
int a[MAX]; 
int part_size = MAX/MAX_THREAD;
 
void* sum_array(void* arg) { 
    unsigned long long thread_part = (unsigned long long) arg; 
    int extend = 0;
    
    if (MAX % MAX_THREAD != 0 && thread_part == MAX_THREAD - 1) {
        extend = MAX % MAX_THREAD;
    }

    for (int i = thread_part * part_size + 1; i < (thread_part + 1) * part_size + extend; i++){
        if (i < sizeof(a)/sizeof(int)) {
            a[thread_part * part_size] += a[i];
        }
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
    
    int total_sum = 0; 
    for (int i = 0; i < MAX_THREAD; i++){
        total_sum += a[i*part_size]; 
    }
    printf("Sum of array is %d\n", total_sum);
    printf("Expected sum is %d\n", (MAX * (MAX + 1)) / 2);
    return 0; 
} 