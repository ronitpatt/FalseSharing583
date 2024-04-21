#include <stdio.h>
#define SIZE 5


void never_executed(){
    printf("Should Not Be Printed!\n");
}

int iAdd(int a, int b){
    return a + b;
}

float fAdd(float a, float b){
    return a + b;
}


// Before: 
// int [2][4]
// After: 
// int [4][2]


// Before: int A[4], int B[4]
// After: int [A0, B0, A1, B1 ...]


int main(){

// int A[SIZE] = {0};
// int B[SIZE] = {1};


int test_size = 5;

int test[SIZE] = {0};

int testa[SIZE] = {0};


int *buff = (int*)&test;

for(int i = 0; i < test_size; i++){
    test[i] = i;
    testa[i] = i * 2;
}

printf("Memory addresses of each element in the 'test' array:\n");

for (int i = 0; i < test_size; i++) {
    printf("test[%d]: %p\n", i, (void*)&test[i]);
}

for (int i = 0; i < test_size; i++) {
    printf("testa[%d]: %p\n", i, (void*)&testa[i]);
}

    // Print the elements of the array
printf("Elements of the array:\n");
for (int i = 0; i < test_size; i++) {
    printf("%d\n", test[i]);
}

for (int i = 0; i < test_size; i++) {
    printf("%d\n", testa[i]);
}


// for(int i = 0; i < SIZE; i++){
//     if (i < SIZE*0.8){
//         D[i] = fAdd(C[i], D[i]);
//     }

//     if( i < SIZE*0.3){
//         B[i] = iAdd(A[i], B[i]);
//     }
// }

printf("Should Be Printed!\n");

return 0;

}

// #include <stdio.h>
// #include <unistd.h>

// struct c {
//     int front;
//   }; // is it ok to pad this inside struct


// int main()
// {
//   c arr[4];

//   for (int i = 0; i<12; i++){
//     arr[i].front = 888;
//   }
//   // c a;
//   // arr[0].front = 0;
  
//   bool even = (fork() == 0);


//   for (int i = 0; i<6; i++){
//     if (even) {
//       printf("%d", arr[i*2].front);
//     } else {
//       printf("%d", arr[i*2+1].front);
//     }
//   }

//   // for (int i = 0; i < 4; i+=1) {
//   //   printf("%d %d %d\n", arr[i].front, arr[i].c1, arr[i].array[1]);
//   // }
//   //c* a= &(arr[0]);

//   int *buff = (int*)&arr;
  
//   for (int i = 0; i < 64*4; i+=1) {
//     if (i*4 %64 == 0) {
//       printf("-----------------------\n");
//     }
//     printf("%d %d \n", i, buff[i]);
//   }

//   return 1;
// }