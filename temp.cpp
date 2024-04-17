#include <stdio.h>
#include <unistd.h>

// struct c {
//   int a[4];
//   int b[4];
//   int c[4];
// };
// c obj;

struct c_elem {
  int a;
  int b;
  int c;
};
c_elem arr[4];

int main()
{
  /*
  Before
  obj.a[3];
  newobj[3].a;
  */
  //printf("%d\n", obj.a[2]);
  //printf("%d", obj.a[2]);
  // for(int i = 0; i < 4; ++i) {
    
  // }
  arr[0].a = 1;
  arr[1].a = 2;
  arr[2].a = 3;
  arr[3].a = 4;
  arr[0].b = 5;
  arr[1].b = 6;
  arr[2].b = 7;
  arr[3].b = 8;
  arr[0].c = 9;
  arr[1].c = 10;
  arr[2].c = 11;
  arr[3].c = 12;
  // obj.b[1] = 6;
  // obj.b[2] = 7;
  // obj.b[3] = 8;
  //printf("%p %p %p\n", &arr.a[0], &obj.a[1], &obj.c[0]);
  /*
  0 1 0
  0 1 0
  0 1 0
  0 1 0
  */
  int* ptr = (int*)(&arr);
  for(int i = 0; i < 4; ++i) {
    printf("%d %d %d \n", ptr[0], ptr[1], ptr[2]);
    ptr+=3;
  }
  

  return 1;
}