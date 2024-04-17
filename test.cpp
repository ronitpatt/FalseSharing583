#include <stdio.h>
#include <unistd.h>

struct c {
  int a[4];
  int b[4];
  int c[4];
};
c obj;

// struct c_elem {
//   int a;
//   int a;
//   int b;
//   int c;
// };
// c_elem arr[4];

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
  obj.a[0] = 1;
  obj.a[1] = 2;
  obj.a[2] = 3;
  obj.a[3] = 4;
  obj.b[0] = 5;
  obj.b[1] = 6;
  obj.b[2] = 7;
  obj.b[3] = 8;
  obj.c[0] = 5;
  obj.c[1] = 6;
  obj.c[2] = 7;
  obj.c[3] = 8;
  printf("%p %p %p\n", &obj.a[0], &obj.a[1], &obj.c[0]);
  /*
  0 1 0
  0 1 0
  0 1 0
  0 1 0
  */
  int* ptr = (int*)(&obj);
  for(int i = 0; i < 4; ++i) {
    printf("%d %d %d \n", ptr[0], ptr[1], ptr[2]);
    ptr+=3;
  }
  

  return 1;
}