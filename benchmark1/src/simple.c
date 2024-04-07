#include <stdio.h>
#define SIZE 200


void never_executed(){
    printf("Should Not Be Printed!\n");
}

int iAdd(int a, int b){
    return a + b;
}

float fAdd(float a, float b){
    return a + b;
}


int main(){

int A[SIZE] = {0};
int B[SIZE] = {1};
float C[SIZE] = {0.1};
float D[SIZE] = {3.2};


int test_size = 5;

int test[test_size];

for(int i = 0; i < test_size; i++){
    test[i] = i;
}

    // Print the elements of the array
printf("Elements of the array:\n");
for (int i = 0; i < test_size; i++) {
    printf("%d\n", test[i]);
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